#include "Rudder_PID.h"

/* this duplicates rudder max angle but it is only used in this test case */
/* I don't want this class to be friends with the rudder class at the mo */
#define RUDDER_MAX_HELM_PORT -40
#define RUDDER_MAX_HELM_STBRD 40
#define INVALID_UNSIGNED_INT  ((unsigned int)~0)

Rudder_PID::Rudder_PID(const Model *model):
	baud(38400),
	test_state(0),
	mSerial0(CS_PIN,0), correct_count(0), direction_multiplier(1),
	proportional(2), integral(5), derivative(1),
	input(0),output(0),setpoint(0),minimum_effort(10),
	correction(&this->input, &this->output, &this->setpoint, this->proportional, this->integral, this->derivative, DIRECT)
{
	/*don't try serial interaction here the board hasn't been set up */
	this->model = model;
}

void Rudder_PID::init()
{
	mSerial0.begin(this->baud);
	correction.SetMode(AUTOMATIC);
	correction.SetOutputLimits(-100, 100 ); /* define aggression */
	correction.SetSampleTime( 100 ); /* we poll the tick every 100 ms */

	pinMode(lvl1Pin, INPUT);		// ADC for reading current
}

Rudder_PID::~Rudder_PID()
{

}

void Rudder_PID::set_input(void)
{
	input = 0;
}

int Rudder_PID::get_current(void)
{
	int adc = analogRead(lvl1Pin);

	return (adc - 512)/25;  //(adc * 20)/512
}

bool Rudder_PID::over_current(void)
{
	int power = abs(output);
	int adc = analogRead(lvl1Pin);
	bool overcurrent = true;
	
	struct adc_table {
		int request;
		int current;
	};
	
	/* current expected against speed */
	const adc_table comparison_table[] = {
		{127, 1100},
		{112, 1000},
		{96, 950},
		{80, 900},
		{64, 850},
		{0, 800}
	};
	
    for (size_t i=0; i<DIM(comparison_table);i++)
	{
		if (power <= comparison_table[i].request) {
			overcurrent = (adc > comparison_table[i].current)?true:false;

			// if (overcurrent)
			// {
			// 	char buffer[124];
			// 	sprintf(buffer, "OVERCURRENT %d, %d, %d\n", power, adc, i);
			// 	Serial.println(buffer);
			// }
			break;
		}
	}

	return overcurrent;
}

signed int Rudder_PID::get_corrected( signed int angle )
{
	/* if the setpoint is 90degrees then input should be of the 
	   range -90 to 270 otherwise 380 will try to turn to starboard */
	
	return ((angle - setpoint) > 180)?angle-360:angle; 
}

void Rudder_PID::set_wanted( signed int angle )
{
	setpoint = (double)(angle % 360);
	correction.SetMode(AUTOMATIC);
	correct_count = 0;
}

void Rudder_PID::set_wanted_relative( signed int angle )
{
	this->set_wanted(setpoint + (double)angle);
	correction.SetMode(AUTOMATIC);
}

void Rudder_PID::set_PID_proportional( unsigned int p )
{
	proportional = p;
	correction.SetTunings(proportional, integral, derivative);
}

void Rudder_PID::set_PID_integral( unsigned int i )
{
	integral = i;
	correction.SetTunings(proportional, integral, derivative);
}

void Rudder_PID::set_PID_derivative( unsigned int d )
{
	derivative = d;
	correction.SetTunings(proportional, integral, derivative);
}

void Rudder_PID::set_disable(void)
{
	correction.SetMode(MANUAL);
}

bool Rudder_PID::get_disabled(void)
{
	return (AUTOMATIC == correction.GetMode())?false:true;
}

void Rudder_PID::tick_event(void)
{

	if (AUTOMATIC == correction.GetMode())
	{
		const RSA_T *rudder = getModel()->get_RSA();

		/* motorspeed is relative 0-255 fast reverse to fast forward 127 being stop */

		/* set the error based on whatever this class is measuring */
		this->set_input();

		/* do that PID magic */
		correction.Compute();

		// {
		// 	char buffer[124];
		// 	sprintf(buffer, "rudder %d, input %f setpoint (%f) output (%f) (%d)", (int)rudder->starboard, input, setpoint, output, correct_count );
		// 	Serial.println( buffer );
		// }
		
		/* correct for minimal effort */
		if (abs(output) < minimum_effort) output = 0;

		/* never instruct the motor to exceed maximum helm positions, stop the motor and wait
		   for the PID algorithm to realise its error, or for the correction to take place */ 
		if (((rudder->starboard < RUDDER_MAX_HELM_PORT) && (output < 0)) ||
			((rudder->starboard > RUDDER_MAX_HELM_STBRD) && (output > 0)) ||
			( over_current() ))
		{
			/* instruct the motor to do nothing */
			mSerial0.write( 127 );
		}
		else
		{
			/* instruct the motor to do something or nothing */
			mSerial0.write( (int)(direction_multiplier * output) + 127 );
		}

		/* if we think we have attained the rudder position stay there until asked again */
		if (0 == output) {
			
			if ((INVALID_UNSIGNED_INT != stable_count) &&
				(stable_count < ++correct_count)) {
				//Serial.println("been good for so long I am giving up");
				correction.SetMode(MANUAL);
			}
		}
		else {

			correct_count = 0;
		}
	}
}

/* make a number of sweeps, lock to lock at different speeds */
/* measure the time it takes to do these */
/* a positive number drives the helm to starboard */
void Rudder_PID::speed_test_event(void)
{
	int speeds[] = { -127, 127, -112, 112, -96, 96, -80, 80, -64, 64, -48, 48 };
	const RSA_T *rudder = model->get_RSA();

	// {
	// 	char buffer[100];

	// 	sprintf(buffer, "r (%f) s (%d)", rudder->starboard, test_state);
	// 	Serial.println(buffer);
	// }

	/* start with the helm to starboard */
	if (0 == test_state)
	{
		if ((rudder->starboard < RUDDER_MAX_HELM_STBRD) &&
			( over_current() ))
		{
			output = 127;
			/* until rudder is hard to starboard */
			mSerial0.write( output + 127 );
			Serial.println("helm to starboard");
		}
		else
		{
			/* start the first test moving the helm to port */
			output = speeds[test_state];
			mSerial0.write( output + 127 );
			test_time = millis();
			test_state++;
			Serial.println("helm to port");
		}
	}
	else
	{
		/*if we have hit the edge, initially test_state = 1 moving helm to port */
		if (((0x01 == (0x01 & test_state)) && ( rudder->starboard < RUDDER_MAX_HELM_PORT)) ||
			((0x00 == (0x01 & test_state)) && ( rudder->starboard > RUDDER_MAX_HELM_STBRD)) ||
			( over_current() ))
		{
			char buffer[100];
				
			sprintf(buffer, "test (%d/%d) time (%d) rudder (%f)", test_state, DIM(speeds), (int)(millis() - test_time), rudder->starboard );
			Serial.println(buffer);
				
			/* if we have done all of the tests */
			if (test_state >= DIM(speeds))
			{
				Serial.println("stop test");
				output = 0;
			}
			else
			{
				output = speeds[test_state];
				test_time = millis();
				test_state++;
			}
			mSerial0.write( output + 127 );
		}
	}
}

Angle_PID::Angle_PID( const Model *model):Rudder_PID(model){
	set_stable_count(10);
};

void Angle_PID::set_input(void)
{
	const RSA_T *rudder = getModel()->get_RSA();

	if (rudder)
	{
		Rudder_PID::set_input(rudder->starboard);
	}
}

void Angle_PID::set_wanted( signed int angle )
{
	double wanted = (double)angle;
	if (wanted < RUDDER_MAX_HELM_PORT) wanted = RUDDER_MAX_HELM_PORT;
	else if (wanted > RUDDER_MAX_HELM_STBRD) wanted = RUDDER_MAX_HELM_STBRD;

	Rudder_PID::set_wanted(wanted);
}

Compass_PID::Compass_PID( const Model *model):Rudder_PID(model){
	set_stable_count(INVALID_UNSIGNED_INT);  /* max for unsigned value */
	set_direction(false);
};

void Compass_PID::set_input(void)
{
	const HDM_T *compass = getModel()->get_HDM();

	if (compass) {
		Rudder_PID::set_input(get_corrected(compass->heading));
	}
}

GPSBearing_PID::GPSBearing_PID( const Model *model):Rudder_PID(model){
	set_stable_count(INVALID_UNSIGNED_INT);  /* max for unsigned value */
	set_direction(false);
};

void GPSBearing_PID::set_input(void)
{
	const RMC_T *gps = getModel()->get_RMC(); /* recommended minimum */

	/* we only change the input if we are going fast enough to trust the COG */
	if (gps && (2 < gps->sog)) {
		Rudder_PID::set_input(get_corrected(gps->dir));
	}
	else
	{
		/* if we are not going fast enough rely on the compass */
		const HDM_T *compass = getModel()->get_HDM();

		Rudder_PID::set_input(get_corrected(compass->heading));
	}
}

#include "Rudder_PID.h"

Rudder_PID::Rudder_PID(const Model *model):
	baud(38400),
	test_state(0),
	mSerial0(CS_PIN,0),correcting(false), correct_count(0),
	input(0),output(0),setpoint(0),minimum_effort(20),
	correction(&this->input, &this->output, &this->setpoint, 2, 5, 1, DIRECT)
{
	/*don't try serial interaction here the board hasn't been set up */
	this->model = model;
}

void Rudder_PID::init()
{
	mSerial0.begin(this->baud);
	correction.SetMode(AUTOMATIC);
	correction.SetOutputLimits( -64, 64 ); /* define aggression */
	correction.SetSampleTime( 100 ); /* we poll the tick every 100 ms */
}

Rudder_PID::~Rudder_PID()
{

}

void Rudder_PID::set_wanted( signed int angle )
{
	setpoint = (double)angle;
	correction.SetMode(AUTOMATIC);

	Serial.print(setpoint);
	Serial.println(" Set Rudder Wanted");
	correcting = true;
}

void Rudder_PID::tick_event(void)
{
	char buffer[124];

	const RSA_T *rudder = model->get_RSA();
	const HDM_T *compass = model->get_HDM();
	const RMC_T *gps = model->get_RMC(); /* recommended minimum */

	if ((rudder) && (correcting))
	{
		/* motorspeed is relative 0-255 fast reverse to fast forward 127 being stop */

		input = rudder->starboard;

		/* do that PID magic */
		correction.Compute();

		sprintf(buffer, "rudder %f wanted (%f) output (%f) compass (%f):%c cog %f cc (%d)", rudder->starboard, setpoint, output,
				compass->heading, compass->magnetic, gps->dir, correct_count);
		
		Serial.println( buffer );

		if (abs(output) < minimum_effort) output = 0;

		if (0 == output) {
			correct_count++;

			if (10 < correct_count)
			{
				correcting = false;
				Serial.println("good enough >>>, stop messing about");
			}
		}
		else {
			correct_count = 0;
		}
		sprintf(buffer, "output (%f) abs(%f) min (%d)", output, abs(output), minimum_effort);
		Serial.println(buffer);

		mSerial0.write( (int)output + 127 );
	}
}

/* this duplicates rudder max angle but it is only used in this test case */
/* I don't want this class to be friends with the rudder class at the mo */
#define RUDDER_MAX_HELM_PORT -35
#define RUDDER_MAX_HELM_STBRD 35

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
		if (rudder->starboard < RUDDER_MAX_HELM_STBRD)
		{
			int speed = 255;
			/* until rudder is hard to starboard */
			mSerial0.write( speed );
			Serial.println("helm to starboard");
		}
		else
		{
			/* start the first test moving the helm to port */
			mSerial0.write( speeds[test_state] + 127 );
			test_time = millis();
			test_state++;
			Serial.println("helm to port");
		}
	}
	else
	{
		/*if we have hit the edge, initially test_state = 1 moving helm to port */
		if (((0x01 == (0x01 & test_state)) && ( rudder->starboard < RUDDER_MAX_HELM_PORT)) ||
			((0x00 == (0x01 & test_state)) && ( rudder->starboard > RUDDER_MAX_HELM_STBRD)))
		{
			char buffer[100];
				
			sprintf(buffer, "test (%d/%d) time (%d) rudder (%f)", test_state, DIM(speeds), (int)(millis() - test_time), rudder->starboard );
			Serial.println(buffer);
				
			/* if we have done all of the tests */
			if (test_state >= DIM(speeds))
			{
				Serial.println("stop test");
				mSerial0.write( 0 + 127 );
			}
			else
			{
				mSerial0.write( speeds[test_state] + 127 );
				test_time = millis();
				test_state++;
			}
		}
	}
}

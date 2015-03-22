#include "Rudder_PID.h"

Rudder_PID::Rudder_PID(const Model *model):
	baud(38400),
	test_state(0),
	mSerial0(CS_PIN,0),
	input(0),output(0),setpoint(0),
	correction(&this->input, &this->output, &this->setpoint, 2, 5, 1, DIRECT)
{
	/*don't try serial interaction here the board hasn't been set up */
	this->model = model;
}

void Rudder_PID::init()
{
	mSerial0.begin(this->baud);
	correction.SetMode(AUTOMATIC);
	correction.SetOutputLimits( -45, 45 );
	correction.SetSampleTime( 500 ); /* we poll the tick every 500 ms */
}

Rudder_PID::~Rudder_PID()
{

}

void Rudder_PID::setDesiredOffset( signed int angle )
{
	setpoint = (double)angle;
	correction.SetMode(AUTOMATIC);
}

void Rudder_PID::tick_event(void)
{
	char buffer[124];

	const RSA_T *rudder = model->get_RSA();
	const HDM_T *compass = model->get_HDM();
	const RMC_T *gps = model->get_RMC(); /* recommended minimum */

	if (rudder)
	{
		/* motorspeed is relative 0-255 fast reverse to fast forward 127 being stop */
		/* Simple maths would be take the current rudder position subtract it from the
		   wanted one apply that scale of that difference to the value we give the 
		   motor controller.  However this PID stuff is supposed to be shit hot and
		   avoid overrun etc.  But it seems to be pwm based and more applicable to 
		   speed controllers */

		uint16_t motor_speed = (compass->heading ) + 127;
		setpoint = compass->heading;
		input = rudder->starboard;

		if (motor_speed > 255) motor_speed = 255;

		correction.Compute();

		sprintf(buffer, "rudder %f compass (%f):%c cog %f speed (%d)", rudder->starboard, compass->heading, compass->magnetic, 
				gps->dir, motor_speed);
		
		Serial.println( buffer );

		//debug output to SyRen before wiring it up
		sprintf(buffer, "speed (%d) offset (%d)", motor_speed, (signed int)motor_speed-127);
		//mSerial0.print(buffer);
		mSerial0.write( motor_speed );
	}
}

/* make a number of sweeps, lock to lock -20 to 20 at different speeds */
/* measure the time it takes to do these */ 
void Rudder_PID::speed_test_event(void)
{
	int speeds[] = { -127, 127, -112, 112, -96, 96, -80, 80, -64, 64, -48, 48 };
	const RSA_T *rudder = model->get_RSA();
	// char buffer[100];

	// sprintf(buffer, "r (%f) s (%d)", rudder->starboard, test_state);
	// Serial.println(buffer);

	/* start right most */
	if (0 == test_state)
	{
		if (rudder->starboard > -22)
		{
			int speed = 255;
			/* reverse until rudder is hard to port */
			mSerial0.write( speed );
		}
		else
		{
			/* start the first test moving the rudder to starboard */
			mSerial0.write( speeds[test_state] + 127 );
			test_time = millis();
			test_state++;
		}
	}
	else
	{
		/*if we have hit the edge, initially test_state = 1 moving to starboard */
		if (((0x01 == (0x01 & test_state)) && ( rudder->starboard > 35)) ||
			((0x00 == (0x01 & test_state)) && ( rudder->starboard < -22)))
		{
			char buffer[100];
				
			sprintf(buffer, "test (%d) time (%d) rudder (%f)", test_state, (int)(millis() - test_time), rudder->starboard );
			Serial.println(buffer);
				
			/* if we have done all of the tests */
			if (test_state > DIM(speeds))
			{
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

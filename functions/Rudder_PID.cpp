#include "Rudder_PID.h"
#include "PID_v1.h"

Rudder_PID::Rudder_PID(const Model *model):baud(38400),mSerial0(CS_PIN,0)
{
	/*don't try serial interaction here the board hasn't been set up */
	this->angle = 0;
	this->model = model;
}

void Rudder_PID::init()
{
	mSerial0.begin(this->baud);
}

Rudder_PID::~Rudder_PID()
{

}

void Rudder_PID::setDesiredOffset( signed int angle )
{
	this->angle = angle;
}

void Rudder_PID::tick_event(void)
{
	char buffer[124];

	const RSA_T *rudder = model->get_RSA();
	const HDM_T *compass = model->get_HDM();

	if (rudder)
	{
		sprintf(buffer, "rudder %f compass %f%c", rudder->starboard, compass->heading, compass->magnetic);
		Serial.println( buffer );
		mSerial0.println("boo!");
	}
}


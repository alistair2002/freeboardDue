#include "Rudder_PID.h"
#include "PID_v1.h"

Rudder_PID::Rudder_PID(const Model *model)
{
	this->angle = 0;
	this->model = model;
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
	char buffer[30];
	const RSA_T *rudder = model->get_RSA();
	if (rudder)
	{
		sprintf(buffer, "rudder %f", rudder->starboard);
		Serial.println( buffer );
	}
}


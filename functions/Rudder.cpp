/*
 * Copyright 2015 Alistair Rodger it is done as part of the freeboard
 * project if you need to get hold of me I am sure Robert can track 
 * me down.
 *
 * This file is part of FreeBoard. (http://www.42.co.nz/freeboard)
 *
 *  FreeBoard is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  FreeBoard is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with FreeBoard.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This is based on a 'KUS' rudder angle guage.  It is a potentiometer
 * which varies its resistance from 0 - 190 Ohms depending on the angle
 * I use a potential divider.  i.e. a 190 Ohm resistor between the 5v
 * and the Level 2 connector, I then run one terminal from the Level 2
 * connector to the rudder guage.  Then another line from the other
 * side of the guage to GND connecter near the Level 2 connector.
 * this then means I get a reading of 0 - 813 depending on position.
 * I need to calibrate this but 512 should be dead centre.
 *
 * I am guestimating about 90 degrees of travel.
 */
 
#include "Rudder.h"

Rudder::Rudder (SentenceQueue *freeQue, SentenceQueue *procQue):
	rudder_angle_min(-35),
	rudder_angle_max(35)
{
	this->free_queue = freeQue;
	this->proc_queue = procQue;

	pinMode(lvl3Pin, INPUT);
}

Rudder::~Rudder()
{

}

/* depending on wiring and resister usage these may change */
/* be mindfull of where the port is, the potentiometer can be wired up differently */
#define RUDDER_ADC_MAX 760
#define RUDDER_ADC_MIN 2

int Rudder::get_max_angle(void)
{
	return rudder_angle_max;
}

int Rudder::get_min_angle(void)
{
	return rudder_angle_min;
}

 /* this should be -1 if you have wired or connected the potentiometer such that port is the higher
	value, port should be negative.  Clockwise and all that... */
#define RUDDER_PORT_NEGATOR 1

void Rudder::tick_event(void)
{
	char *sentence = free_queue->pop();
	if (sentence)
	{
		/* read the ADC, normalise to 0-90 degrees, not so simple */
		/* min 1 (port) max 760 (starboard) distributed over approx 90 degrees */
		int rudder_adc = analogRead(lvl2Pin); /* value between MIN and MAX */
		 /* distribute it to between -45 port to 45 starboard */
		float angle = (((rudder_adc - RUDDER_ADC_MIN) * 90) / (RUDDER_ADC_MAX - RUDDER_ADC_MIN)) - 45;

		/* correct if it is outside this range as it is possible */
		if (rudder_adc < RUDDER_ADC_MIN){ angle = -45; }
		else if (rudder_adc > RUDDER_ADC_MAX) {angle = 45; }

		char crc_string[3] = {};
		int crc = 0;

		/* negative is turn to port, starboard helm */
		sprintf(sentence, "$INRSA,%f,A,0.0,V*", (RUDDER_PORT_NEGATOR * angle));

		crc = getChecksum( sentence );

		sprintf(crc_string, "%2.2x", crc);
		strcat(sentence, crc_string);

		proc_queue->push(sentence);

		// {
		// 	char buffer[100];
		// 	sprintf(buffer, "adc (%d) angle (%d)", (int)analogRead(lvl2Pin), (RUDDER_PORT_NEGATOR * angle) );
		// 	Serial.println(buffer);
		// }
	}
}

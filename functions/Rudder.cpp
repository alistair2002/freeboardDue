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

Rudder::Rudder (SentenceQueue *freeQue, SentenceQueue *procQue)
{
	this->free_queue = freeQue;
	this->proc_queue = procQue;

	pinMode(lvl3Pin, INPUT);
}

Rudder::~Rudder()
{

}

void Rudder::tick_event(void)
{
	char *sentence = free_queue->pop();
	if (sentence)
	{
		/* read the ADC, normalise to 0-90 degrees */
		int angle = (analogRead(lvl2Pin) * 90) / 1024;

		char crc_string[3] = {};
		int crc = 0;

		/* negative is turn to port, starboard helm */
		sprintf(sentence, "$INRSA,%d.0,A,0.0,V*", (90 - angle) - 45);

		crc = getChecksum( sentence );

		sprintf(crc_string, "%2.2x", crc);
		strcat(sentence, crc_string);

		proc_queue->push(sentence);

		// {
		// 	char buffer[100];
		// 	sprintf(buffer, "adc (%d) angle (%d)", (int)analogRead(lvl2Pin), angle );
		// 	Serial.println(buffer);
		// }
	}
}

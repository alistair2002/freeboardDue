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

/* this is a near as dammit implementation of the sparkfun sample code
   but displays the number passed in the tick */

#include "SegDisp.h"
#include "SevSeg.h"

//Create an instance of the object. NB the sneaky use of C data hiding ;-)
SevSeg myDisplay;

SegDisp::SegDisp( )
{
  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode

  //This pinout is for OpenSegment PCB layout
  //Declare what pins are connected to the digits
  int digit1 = 8; //Pin 12 on my 4 digit display
  int digit2 = 32; //Pin 9 on my 4 digit display
  int digit3 = 11; //Pin 8 on my 4 digit display
  int digit4 = 13; //Pin 6 on my 4 digit display

  //Declare what pins are connected to the segments
  int segA = 36; //Pin 11 on my 4 digit display
  int segB = 34; //Pin 7 on my 4 digit display
  int segC = 10; //Pin 4 on my 4 digit display
  int segD = 28; //Pin 2 on my 4 digit display
  int segE = 9; //Pin 1 on my 4 digit display
  int segF = 30; //Pin 10 on my 4 digit display
  int segG = 26; //Pin 5 on my 4 digit display
  int segDP= 12; //Pin 3 on my 4 digit display

  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(100); //Set the display to 100% brightness level
}

SegDisp::~SegDisp( )
{
}

void SegDisp::tick_event(unsigned int val)
{
	char tempString[10]; //Used for sprintf
	sprintf(tempString, "%4d", val%9999); //Convert deciSecond into a string that is right adjusted

	myDisplay.DisplayString(tempString, 0);
}

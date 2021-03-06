/*
 * Copyright 2010,2011,2012,2013 Robert Huitema robert@42.co.nz
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

// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _freeboardDue_H_
#define _freeboardDue_H_
#include "Arduino.h"
//add your includes for the project freeboardDue here

#include "FreeboardConstants.h"
#include <DueTimer.h>
#include <MultiSerial.h>
#include <stream_json_reader.h>
#include "FreeBoardModel.h"
#include "NmeaSerial.h"
#include "Alarm.h"
#include "Wind.h"
#include "Gps.h"
#include "Anchor.h"
#include "NmeaRelay.h"
#include "Autopilot.h"
#include "Seatalk.h"
#include "QueueList.h"
/*
#include <EEPROM.h>


#include <MemoryFree.h>
*/
/*********************************************************************************/
/* message system for reading data off serial ports and sending queueing it for  */
/* parsing by the model */
typedef QueueList<char*> SentenceQueue;

/*********************************************************************************/

typedef unsigned char byte;

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project freeboardDue here



byte getChecksum(char* str);
//Do not add code below this line
#endif /* _freeboardDue_H_ */

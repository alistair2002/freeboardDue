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

#ifndef SEGOUTPUT_H_
#define SEGOUTPUT_H_

#include "freeboardDue.h" /* definition of types */
#include "Rudder_PID.h"   /* so it can determine current AMP draw */
#include "nmea_model.h"
#include "SegDisp.h"

class SegOutput {

public:
	
	typedef enum {
		SEG_OUTPUT_NONE,
		SEG_OUTPUT_MAG,
		SEG_OUTPUT_COG,
		SEG_OUTPUT_AMP,
		SEG_OUTPUT_MAX
	}SegOutput_t;

	SegOutput( Rudder_PID** current_PID );
	virtual ~SegOutput();
	void choose(int output);
	void tick();

private:
	
	const Model *model;		// read only reference to nmea model
	Rudder_PID **current_pid;

	// display
	SegDisp seg_disp;
	SegOutput_t choice;
	
};

#endif /* SEGOUTPUT_H_ */

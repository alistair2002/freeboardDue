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

#ifndef SEGDISP_H_
#define SEGDISP_H_

#include "freeboardDue.h" /* definition of types */

/* Resources: The SegDisp display uses DIO 8-13 and 26,28,30,32,34,36 */

class SegDisp {

public:
	SegDisp( );
	virtual ~SegDisp();

	void tick_event(unsigned int val); /* lets face it, it is a 4 seg disp */

};

#endif /* SEGDISP_H_ */

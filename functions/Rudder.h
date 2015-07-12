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

#ifndef RUDDER_H_
#define RUDDER_H_

#include "freeboardDue.h" /* definition of types */

/* Resources: The rudder sensor uses Level 2, aka lvl2Pin, aka A11 */

class Rudder {

public:
	Rudder(SentenceQueue *freeQue, SentenceQueue *procQue);
	virtual ~Rudder();
	void tick_event(void);
	int get_max_angle(void);
	int get_min_angle(void);

private:

	int rudder_angle_min;
	int rudder_angle_max;

	SentenceQueue *free_queue;
	SentenceQueue *proc_queue;
};

#endif /* RUDDER_H_ */

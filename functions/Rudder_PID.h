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

#ifndef RUDDER_PID_H_
#define RUDDER_PID_H_

#include "freeboardDue.h" /* definition of types */
#include "nmea_model.h"
#include "MultiSerial.h"
#include "PID_v1.h"

/* Resources: the Rudder PID uses MultiSerial port 0 */
#ifndef _NMEA_MODEL_H_
#error nmea not defined
#endif

class Rudder_PID {

public:
	Rudder_PID(const Model *model);
	~Rudder_PID();

	void init(void);		// to start the serial once the hardware is up

	void set_wanted( signed int angle );
	void set_PID_proportional( unsigned int p );
	void set_PID_integral( unsigned int i );
	void set_PID_derivative( unsigned int d );
	void tick_event(void);
	void speed_test_event(void);
	void set_disable(void);
	bool get_disabled(void);

	const Model *getModel(void) { return this->model; }
	void setInput(double input) { this->input = input; }
	
private:

	const Model *model;		// read only reference to nmea model
	const int baud;			// configuration value

	unsigned int test_state;
	unsigned int test_time;

	virtual void set_input(void);
	int	 get_current(void);		// returns an approximation of current
	bool over_current(void);	// returns true of we are consuming too much current for the given speed

	MultiSerial mSerial0;	//autopilot

	unsigned int correct_count;		// count of stability before we give up and say good enough
	int proportional, integral, derivative; // the tuning values for the PID algorithm
	double input, output, setpoint;	// the values tracked by the PID algorithm
	unsigned int minimum_effort;    // don't bother unless it is a reasonable drive to the motor
	PID correction;			// the PID algorithm that does fancy phase lock loop stuff
};

class Angle_PID: public Rudder_PID {
public:
	Angle_PID( const Model *model );

private:
	void set_input(void);
};

class Compass_PID: public Rudder_PID {
public:
	Compass_PID( const Model *model);

private:
	void set_input(void);

};

class GPSBearing_PID: public Rudder_PID {
public:
	GPSBearing_PID( const Model *model);

private:
	void set_input(void);

};
	

#endif

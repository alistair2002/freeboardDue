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
/*
 * SignalkHelper.h
 *
 *Holds all the global model vars
 *
 *  Created on: Mar 28, 2012
 *      Author: robert
 */

#ifndef SIGNALKHELPER_H_
#define SIGNALKHELPER_H_
#define DEBUG true
#include "Arduino.h"


#define TYPE_FLOAT  0
#define TYPE_BOOL  1
#define TYPE_INT  2
#define TYPE_UNSIGNED_LONG  3
#define TYPE_DOUBLE  4 //same as float on mega
#define TYPE_CHAR_ARRAY 5
#define TYPE_CHAR 6
//#include "StreamJsonReader.h"
//#include "FreeboardConstants.h"
#define  NAVIGATION_COURSEOVERGROUNDMAGNETIC 177632231UL
#define  NAVIGATION_COURSEOVERGROUNDTRUE 1495033343UL
#define  NAVIGATION_MAGNETICVARIATION 3733725560UL
#define  NAVIGATION_DESTINATION_LONGITUDE 250998974UL
#define  NAVIGATION_DESTINATION_LATITUDE 2077664687UL
#define  NAVIGATION_DESTINATION_ETA 3951685101UL
#define  NAVIGATION_HEADINGMAGNETIC 390698939UL
#define  NAVIGATION_HEADINGTRUE 1129234387UL
#define  NAVIGATION_POSITION_LONGITUDE 4257320113UL
#define  NAVIGATION_POSITION_LATITUDE 2329218882UL
#define  NAVIGATION_POSITION_ALTITUDE 2999027170UL
#define  NAVIGATION_PITCH 2242652731UL
#define  NAVIGATION_RATEOFTURN 1051834157UL
#define  NAVIGATION_ROLL 588639420UL
#define  NAVIGATION_SPEEDOVERGROUND 3375602335UL
#define  NAVIGATION_SPEEDTHROUGHWATER 2011270296UL
#define  NAVIGATION_STATE 2246585668UL
#define  NAVIGATION_ANCHOR_ALARMRADIUS 3204687649UL
#define  NAVIGATION_ANCHOR_MAXRADIUS 3688841722UL
#define  NAVIGATION_ANCHOR_CURRENTRADIUS 2152304183UL
#define  NAVIGATION_ANCHOR_POSITION_ALTITUDE 3067744843UL
#define  NAVIGATION_ANCHOR_POSITION_LATITUDE 2397936555UL
#define  NAVIGATION_ANCHOR_POSITION_LONGITUDE 2230036026UL

#define  STEERING_AUTOPILOT_STATE 1414591300UL
#define  STEERING_AUTOPILOT_MODE 3296408520UL
#define  STEERING_AUTOPILOT_TARGETHEADINGNORTH 1763947237UL
#define  STEERING_AUTOPILOT_TARGETHEADINGMAGNETIC 542499234UL
#define  STEERING_AUTOPILOT_ALARMHEADINGXTE 2225422449UL
#define  STEERING_AUTOPILOT_HEADINGSOURCE 1161926884UL
#define  STEERING_AUTOPILOT_DEADZONE 3691686605UL
#define  STEERING_AUTOPILOT_BACKLASH 3570446012UL
#define  STEERING_AUTOPILOT_GAIN 3296177826UL
#define  STEERING_AUTOPILOT_MAXDRIVEAMPS 3211458388UL
#define  STEERING_AUTOPILOT_MAXDRIVERATE 3212056367UL
#define  STEERING_AUTOPILOT_PORTLOCK 430477553UL
#define  STEERING_AUTOPILOT_STARBOARDLOCK 4221374702UL
#define  STEERING_RUDDERANGLE 1770208225UL
#define  STEERING_RUDDERANGLETARGET 1589626152UL

#define  ALARMS_ANCHORALARMMETHOD 2783435100UL
#define  ALARMS_ANCHORALARMSTATE 1003034460UL
#define  ALARMS_AUTOPILOTALARMMETHOD 1469117826UL
#define  ALARMS_AUTOPILOTALARMSTATE 3305916098UL
#define  ALARMS_ENGINEALARMMETHOD 3992095383UL
#define  ALARMS_ENGINEALARMSTATE 2991918391UL
#define  ALARMS_FIREALARMMETHOD 133189895UL
#define  ALARMS_FIREALARMSTATE 662422951UL
#define  ALARMS_GASALARMMETHOD 3929525820UL
#define  ALARMS_GASALARMSTATE 3380473916UL
#define  ALARMS_GPSALARMMETHOD 2429115595UL
#define  ALARMS_GPSALARMSTATE 2814404843UL
#define  ALARMS_MAYDAYALARMMETHOD 67311014UL
#define  ALARMS_MAYDAYALARMSTATE 1441329766UL
#define  ALARMS_PANPANALARMMETHOD 1695331519UL
#define  ALARMS_PANPANALARMSTATE 3963523679UL
#define  ALARMS_POWERALARMMETHOD 3887776462UL
#define  ALARMS_POWERALARMSTATE 1296800398UL
#define  ALARMS_SILENTINTERVAL 357415143UL
#define  ALARMS_WINDALARMMETHOD 1899960179UL
#define  ALARMS_WINDALARMSTATE 3449122451UL
#define  ALARMS_GENERICALARMMETHOD 3742841118UL
#define  ALARMS_GENERICALARMSTATE 1422558942UL
#define  ALARMS_RADARALARMMETHOD 1862050059UL
#define  ALARMS_RADARALARMSTATE 2927371563UL
#define  ALARMS_MOBALARMMETHOD 1690466719UL
#define  ALARMS_MOBALARMSTATE 2011118399UL

#define  ENVIRONMENT_WIND_DIRECTIONAPPARENT 3267532580UL
#define  ENVIRONMENT_WIND_DIRECTIONCHANGEALARM 4209206332UL
#define  ENVIRONMENT_WIND_DIRECTIONTRUE 1752542857UL
#define  ENVIRONMENT_WIND_SPEEDALARM 2559123686UL
#define  ENVIRONMENT_WIND_SPEEDTRUE 1900346521UL
#define  ENVIRONMENT_WIND_SPEEDAPPARENT 531262772UL
#define  ENVIRONMENT_AIRPRESSURECHANGERATEALARM 2231147356UL
#define  ENVIRONMENT_AIRPRESSURE 2568414557UL
#define  ENVIRONMENT_WATERTEMP 1380637633UL

#define  _ARDUINO_GPS_MODEL 260479757UL
#define  _ARDUINO_SERIAL_BAUD0 1806063390UL
#define  _ARDUINO_SERIAL_BAUD1 1806063391UL
#define  _ARDUINO_SERIAL_BAUD2 1806063392UL
#define  _ARDUINO_SERIAL_BAUD3 1806063393UL
#define  _ARDUINO_SERIAL_BAUD4 1806063394UL
#define  _ARDUINO_SERIAL_BAUD5 1806063395UL
#define  _ARDUINO_ALARM_LEVEL1_UPPER 2104985698UL
#define  _ARDUINO_ALARM_LEVEL1_LOWER 2094284095UL
#define  _ARDUINO_ALARM_LEVEL2_UPPER 3396453667UL
#define  _ARDUINO_ALARM_LEVEL2_LOWER 3385752064UL
#define  _ARDUINO_ALARM_LEVEL3_UPPER 392954340UL
#define  _ARDUINO_ALARM_LEVEL3_LOWER 382252737UL
#define  _ARDUINO_SEATALK 3540059849UL
#define  _ARDUINO_WIND_ZEROOFFSET 1490126571UL
#define  _ARDUINO_WIND_LASTUPDATE 3391315227UL
#define  _ARDUINO_GPS_LASTFIX 110834493UL
#define  _ARDUINO_GPS_UTC 1376688456UL
#define  _ARDUINO_GPS_STATUS 246548288UL
#define  _ARDUINO_GPS_DECODE 3936761728UL
#define  _ARDUINO_AUTOPILOT_BAUDRATE 2707722171UL
#define  _ARDUINO_AUTOPILOT_OFFCOURSE 3534384255UL
#define  _ARDUINO_AUTOPILOT_RUDDERCOMMAND 210883000UL
#define  _ARDUINO_ALARM_LAST 3882620915UL
#define  _ARDUINO_WIND_AVERAGE 916641727UL
#define  _ARDUINO_WIND_FACTOR 3452243523UL
#define  _ARDUINO_WIND_MAX 891796138UL
#define  _ARDUINO_ALARM_SNOOZE 2215576829UL
#define  _ARDUINO_ANCHOR_RADIUSDEG 439059557UL
#define  _ARDUINO_ANCHOR_NORTH 3020492120UL
#define  _ARDUINO_ANCHOR_SOUTH 3026424992UL
#define  _ARDUINO_ANCHOR_EAST 3214803994UL
#define  _ARDUINO_ANCHOR_WEST 3215455216UL



class SignalkHelper {
public:

	SignalkHelper();

	int findInArray(const char *array[], const char* value);
	int getNumericType(unsigned long key);

	unsigned long hash(const char *str);


	void openMessage(HardwareSerial* serial);;
	void closeMessage(HardwareSerial* serial);;
	void openBranch(HardwareSerial* serial, const char* key);
	void closeBranch(HardwareSerial* serial, bool last);

	void printValue(HardwareSerial* serial, const char* key, const float value, bool last);
		void printValue(HardwareSerial* serial, const char* key, const unsigned long value, bool last);
		void printValue(HardwareSerial* serial, const char* key, const int value, bool last);
		void printValue(HardwareSerial* serial, const char* key, const long value, bool last);
		void printValue(HardwareSerial* serial, const char* key, const bool value, bool last);
		void printValue(HardwareSerial* serial, const char* key,  const char* value, bool last);
		void printValue(HardwareSerial* serial, const char* key,  const char value, bool last);

	byte getChecksum(char* str);

	static const char* j_vessels ;
	static const char* j_self ;
	static const char* j_arduino ;
	static const char* j_airPressure ;
	static const char* j_airPressureChangeRateAlarm ;
	static const char* j_airTemp ;
	static const char* j_alarm ;
	static const char* j_alarmHeadingXte ;
	static const char* j_alarmRadius ;
	static const char* j_alarms ;
	static const char* j_altitude ;
	static const char* j_anchor ;
	static const char* j_anchorAlarmMethod ;
	static const char* j_anchorAlarmState ;
	static const char* j_autopilot ;
	static const char* j_autopilotAlarmMethod ;
	static const char* j_autopilotAlarmState ;
	static const char* j_average ;
	static const char* j_backlash ;
	static const char* j_baud0 ;
	static const char* j_baud1 ;
	static const char* j_baud2 ;
	static const char* j_baud3 ;
	static const char* j_baud4 ;
	static const char* j_baud5 ;
	static const char* j_baudRate ;
	static const char* j_bearingActual ;
	static const char* j_bearingDirect ;
	static const char* j_belowKeel ;
	static const char* j_belowSurface ;
	static const char* j_belowTransducer ;
	static const char* j_status ;
	static const char* j_courseOverGroundMagnetic ;
	static const char* j_courseOverGroundTrue ;
	static const char* j_courseRequired ;
	static const char* j_currentDirection ;
	static const char* j_currentRadius ;
	static const char* j_currentRoute ;
	static const char* j_currentSpeed ;
	static const char* j_deadZone ;
	static const char* j_decode ;
	static const char* j_depth ;
	static const char* j_destination ;
	static const char* j_directionApparent ;
	static const char* j_directionChangeAlarm ;
	static const char* j_directionTrue ;
	static const char* j_drift ;
	static const char* j_east ;
	static const char* j_engineAlarmMethod ;
	static const char* j_engineAlarmState ;
	static const char* j_environment ;
	static const char* j_eta ;
	static const char* j_factor ;
	static const char* j_fireAlarmMethod ;
	static const char* j_fireAlarmState ;
	static const char* j_gain ;
	static const char* j_gasAlarmMethod ;
	static const char* j_gasAlarmState ;
	static const char* j_genericAlarmMethod ;
	static const char* j_genericAlarmState ;
	static const char* j_gps ;
	static const char* j_gpsAlarmMethod ;
	static const char* j_gpsAlarmState ;
	static const char* j_headingMagnetic ;
	static const char* j_headingSource ;
	static const char* j_headingTrue ;
	static const char* j_heightHigh ;
	static const char* j_heightLow ;
	static const char* j_heightNow ;
	static const char* j_humidity ;
	static const char* j_last ;
	static const char* j_lastFix ;
	static const char* j_lastTime ;
	static const char* j_lastUpdate ;
	static const char* j_latitude ;
	static const char* j_level1 ;
	static const char* j_level2 ;
	static const char* j_level3 ;
	static const char* j_upper ;
	static const char* j_lower ;
	static const char* j_longitude ;
	static const char* j_magneticVariation ;
	static const char* j_max ;
	static const char* j_maxDriveAmps ;
	static const char* j_maxDriveRate ;
	static const char* j_maxRadius ;
	static const char* j_maydayAlarmMethod ;
	static const char* j_maydayAlarmState ;
	static const char* j_mobAlarmMethod ;
	static const char* j_mobAlarmState ;
	static const char* j_mode ;
	static const char* j_model ;
	static const char* j_navigation ;
	static const char* j_next ;
	static const char* j_nextEta ;
	static const char* j_north ;
	static const char* j_offcourse ;
	static const char* j_panpanAlarmMethod ;
	static const char* j_panpanAlarmState ;
	static const char* j_pitch ;
	static const char* j_portLock ;
	static const char* j_position ;
	static const char* j_powerAlarmMethod ;
	static const char* j_powerAlarmState ;
	static const char* j_radarAlarmMethod ;
	static const char* j_radarAlarmState ;
	static const char* j_radiusDeg ;
	static const char* j_rateOfTurn ;
	static const char* j_roll ;
	static const char* j_route ;
	static const char* j_rudderAngle ;
	static const char* j_rudderAngleTarget ;
	static const char* j_rudderCommand ;
	static const char* j_salinity ;
	static const char* j_seatalk ;
	static const char* j_serial ;
	static const char* j_set ;
	static const char* j_silentInterval ;
	static const char* j_snooze ;
	static const char* j_south ;
	static const char* j_speedAlarm ;
	static const char* j_speedApparent ;
	static const char* j_speedOverGround ;
	static const char* j_speedThroughWater ;
	static const char* j_speedTrue ;
	static const char* j_starboardLock ;
	static const char* j_startTime ;
	static const char* j_state ;
	static const char* j_steering ;
	static const char* j_surfaceToTransducer ;
	static const char* j_targetHeadingMagnetic ;
	static const char* j_targetHeadingNorth ;
	static const char* j_tide ;
	static const char* j_timeHigh ;
	static const char* j_timeLow ;
	static const char* j_transducerToKeel ;
	static const char* j_utc ;
	static const char* j_waterTemp ;
	static const char* j_waypoint ;
	static const char* j_west ;
	static const char* j_wind ;
	static const char* j_windAlarmMethod ;
	static const char* j_windAlarmState ;
	static const char* j_xte ;
	static const char* j_zeroOffset ;
private:


};


#endif /* SIGNALKHELPER_H_ */
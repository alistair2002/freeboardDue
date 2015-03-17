
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
// Do not remove the include below
#include "freeboardDue.h"
#include "listeners.h"
#include "autogen_nmea.xml.h"
#include "Rudder.h"

#include <stdbool.h>

using namespace stream_json_reader;

volatile boolean execute = false;
volatile int interval = 0;

//freeboard model
FreeBoardModel model;

//NMEA output - The arduino puts out TTL, NMEA is RS232. They are different V and amps. The +-5V levels may need inverting or you get
// garbage.
// See http://forums.parallax.com/forums/default.aspx?f=19&m=50925
// See http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=63469&start=0
//NmeaSerial nmea(&model);

//NMEA ports
NMEA gpsSource(ALL);
NMEARelay talker0(ALL);
NMEARelay talker2(ALL);
NMEARelay talker3(ALL);
NMEARelay talker4(ALL);

/*********************************************************************************/
/* message queue which tales sentences from the serial ports and queues them     */
/* for processing.  Processing updates the model by parsing these sentences      */
/*********************************************************************************/
/* allow a maximum of 10 buffers two for each serial port so worst case
   there is one buffer being processed and one filled for each port */
char sentence_pool[SENTENCE_POOL_SIZE][MAX_SENTENCE_LENGTH];

SentenceQueue free_queue;
SentenceQueue proc_queue;

serialHandler serial_input_0(&free_queue, &proc_queue);
serialHandler serial_input_1(&free_queue, &proc_queue);
serialHandler serial_input_2(&free_queue, &proc_queue);
serialHandler serial_input_3(&free_queue, &proc_queue);
serialHandler serial_input_4(&free_queue, &proc_queue);

//rudder
Rudder rudder( &free_queue, &proc_queue );

//alarm
Alarm alarm(&model);

//wind
Wind wind(&model);

//Gps
Gps gps(&gpsSource, &model);


//MultiSerial mSerial1 = MultiSerial(CS_PIN,1); //NMEA4
//Autopilot

Autopilot autopilot( &model);

//Anchor
Anchor anchor(&model);


//json support
//{"navigation": {"position": {"longitude": "173.2" ,"latitude": "-41.5"}}}
//{"navigation":{ "position":{"longitude":173.5, "latitude":-43.5}}}
//static const char* queries[] = { "navigation.position.latitude", "navigation.position.longitude"};
//StreamJsonReader jsonreader(&Serial, queries, 2);

/*
 * Timer interrupt driven method to do time sensitive calculations
 * The calc flag causes the main loop to execute other less sensitive calls.
 */
void calculate() {
	//we create 100ms pings here
	execute = true;
	//we record the ping count out to 2 secs
	interval++;
	interval = interval % 20;
}


void readWDS() {
	wind.readWindDataSpeed();
}

void readWDD() {
	wind.readWindDataDir();
}

typedef void (*nmea_process_fn)(const char *val, unsigned int checksum);

typedef struct {
	const char *key;
	const bool save;
	const nmea_process_fn fn;
} nmea_process_table;

void proc_ANCHOR_ALARM_STATE( const char *val, unsigned int checksum )
{
	//if (DEBUG) Serial.print("AA Entered..");
	model.setAnchorAlarmOn(atoi(val));
	if (atoi(val) == 1) {
		anchor.setAnchorPoint();
	}
}

void proc_ANCHOR_ALARM_LAT( const char *val, unsigned int checksum )
{
	model.setAnchorLat(atof(val));
}

void proc_ANCHOR_ALARM_LON( const char *val, unsigned int checksum )
{
	model.setAnchorLon(atof(val));
}
void proc_AUTOPILOT_STATE(const char *val, unsigned int checksum)
{					
	//if (DEBUG) Serial.print("AP Entered..");
	//if (DEBUG) Serial.println(val);
	//this is potentailly dangerous, since we dont want the boat diving off on an old target heading.
	//in model we ALWAYS reset to current magnetic or wind heading at this point
	model.setAutopilotOn(atoi(val));
}

void proc_AUTOPILOT_ADJUST(const char *val, unsigned int checksum)
{
	model.setAutopilotTargetHeading(model.getAutopilotTargetHeading() + atol(val));
}

void proc_AUTOPILOT_SOURCE(const char *val, unsigned int checksum)
{
	model.setAutopilotReference(val[0]);
}

void proc_WIND_SPEED_ALARM_STATE(const char *val, unsigned int checksum)
{
	model.setWindAlarmOn(atoi(val));
}

void proc_WIND_ALARM_KNOTS(const char *val, unsigned int checksum)
{
	model.setWindAlarmSpeed(atoi(val));
}

void proc_WIND_ZERO_ADJUST(const char *val, unsigned int checksum) 
{
	model.setWindZeroOffset(atoi(val));
}

void proc_LEVEL1_UPPER_ALARM(const char *val, unsigned int checksum) 
{
	model.setLvl1UpperLimit(atoi(val));
}

void proc_LEVEL1_LOWER_ALARM(const char *val, unsigned int checksum)
{
	model.setLvl1LowerLimit(atoi(val));
}

void proc_LEVEL2_UPPER_ALARM(const char *val, unsigned int checksum)
{
	model.setLvl2UpperLimit(atoi(val));
}

void proc_LEVEL2_LOWER_ALARM(const char *val, unsigned int checksum) 
{
	model.setLvl2LowerLimit(atoi(val));
}

void proc_LEVEL3_UPPER_ALARM(const char *val, unsigned int checksum) 
{
	model.setLvl3UpperLimit(atoi(val));
}
void proc_LEVEL3_LOWER_ALARM(const char *val, unsigned int checksum) 
{
	model.setLvl3LowerLimit(atoi(val));
}

void proc_CONFIG(const char *val, unsigned int checksum) 
{
	//Serial.println("Sending config..");
	model.writeConfig(Serial);
}

void proc_GPS_MODEL(const char *val, unsigned int checksum) 
{
	model.setGpsModel(atoi(val));
}

void proc_SERIAL_BAUD0(const char *val, unsigned int checksum)
{
	model.setSerialBaud(atol(val));
}

void proc_SERIAL_BAUD1(const char *val, unsigned int checksum)
{
	model.setSerialBaud1(atol(val));
}

void proc_SERIAL_BAUD2(const char *val, unsigned int checksum) 
{
	model.setSerialBaud2(atol(val));
}

void proc_SERIAL_BAUD3(const char *val, unsigned int checksum) 
{
	model.setSerialBaud3(atol(val));
}

void proc_SEATALK(const char *val, unsigned int checksum) 
{
	model.setSeaTalk(atoi(val));
}
	
void proc_MGH(const char *val, unsigned int checksum)
{
	model.setMagneticHeading(atof(val));
}

void proc_DECL(const char *val, unsigned int checksum) 
{
	model.setDeclination(atof(val));
}

void proc_WDT(const char *val, unsigned int checksum) 
{
	//char *qual = strtok(NULL, "*");
	char *crc = strtok(NULL, NULL);

	if ((unsigned int)strtol(crc, NULL, 16) == checksum)
	{
		model.setWindTrueDir(atoi(val));
	}
}

nmea_process_table nmea_command_process_table[] = {
	{"#AAX", true, proc_ANCHOR_ALARM_STATE},
	{"#AAN", true, proc_ANCHOR_ALARM_LAT},
	{"#AAE", true, proc_ANCHOR_ALARM_LON},
	{"#APX", false, proc_AUTOPILOT_STATE},
	{"#APJ", false, proc_AUTOPILOT_ADJUST},
	{"#APS", false, proc_AUTOPILOT_SOURCE},
	{"#WSX", true, proc_WIND_SPEED_ALARM_STATE},
	{"#WSK", true, proc_WIND_ALARM_KNOTS},
	{"#WZJ", true, proc_WIND_ZERO_ADJUST},
	{"#LU1", true, proc_LEVEL1_UPPER_ALARM},
	{"#LL1", true, proc_LEVEL1_LOWER_ALARM},
	{"#LU2", true, proc_LEVEL2_UPPER_ALARM},
	{"#LL2", true, proc_LEVEL2_LOWER_ALARM},
	{"#LU3", true, proc_LEVEL3_UPPER_ALARM},
	{"#LL3", true, proc_LEVEL3_LOWER_ALARM},
	{"#LL3", true, proc_CONFIG},
	{"#GPS", true, proc_GPS_MODEL},
	{"#SB0", true, proc_SERIAL_BAUD0},
	{"#SB1", true, proc_SERIAL_BAUD1},
	{"#SB2", true, proc_SERIAL_BAUD2},
	{"#SB3", true, proc_SERIAL_BAUD3},
	{"#STK", true, proc_SEATALK},
};

nmea_process_table nmea_event_process_table[] = {
	{"MGH", true, proc_MGH},
	{"DEC", true, proc_DECL},
	{"WDT", true, proc_WDT},
	{"HCHDM", false, proc_WDT},
};

/* looks up the function and returns if the change event triggers a storage event */
bool callout_process_handler( const char *key, const char *val, unsigned int checksum, 
							  nmea_process_table* table, const size_t table_size )
{
	size_t i = 0;
	bool store = false;

	for(i=0; i< table_size;i++)
	{
		if ( 0 == strcmp( key, table[i].key ))
		{
			table[i].fn(val, checksum);
			break;
		}
	}
	return store;
}

void process(char *s, char parser)
{
	/* calculate the checksum before we start tokenising the string */
	unsigned int checksum = (int)getChecksum( s );


	if (s != NULL && strlen(s) > 3)
	{
		if (*s == '#') 
		{
			bool save = false;

			/* break the string down, nb strtok is not threadsafe but we dont have threads */
			char *key = strtok(s, ",");
			char *val = strtok(NULL, ",");

			save = callout_process_handler( key + 1, val, checksum,
											nmea_command_process_table, DIM(nmea_command_process_table));

			if (save) model.saveConfig();
		} 
		else 
		{
			parse_nmea(s);
			// callout_process_handler( key + 1, val, checksum,
			// 						 nmea_event_process_table, DIM(nmea_event_process_table));
		}
	}
}

void setup()
{
	int i = 0;
	for (i=0;i<SENTENCE_POOL_SIZE;i++)
	{
		free_queue.push(sentence_pool[i]);
	}

// Add your initialization code here
	// initialize  serial ports:
		Serial.begin(model.getSerialBaud());
		if (DEBUG) Serial.println("Initializing..");

		//start gps on serial1, autobaud
		//if (DEBUG) Serial.println(F("Start gps.."));
		//gps.setupGps();

		if (DEBUG) {
			Serial.print("Start GPS Rx - serial1 at ");
			Serial.println(model.getSerialBaud1());
		}

		Serial1.begin(model.getSerialBaud1());
		Serial1.print("#FBO\r\n");

		if (model.getSeaTalk()) {
			if (DEBUG) Serial.println("Start seatalk - serial2 at 4800");
			Serial2.begin(4800, SERIAL_9N1); //Seatalk interface
		} else {
			if (DEBUG) {
				Serial.print("Start nmea Rx - serial2 at ");
				Serial.println(model.getSerialBaud2());
			}
			Serial2.begin(model.getSerialBaud2(), SERIAL_8N1);
		}

		if (DEBUG) {
			Serial.print("Start nmea Rx - serial3 at ");
			Serial.println(model.getSerialBaud3());
		}
		Serial3.begin(model.getSerialBaud3(), SERIAL_8N1); //talker2

		if (DEBUG) Serial.println("Start SPI uarts..");
			delay(1000);
			pinMode(CS_PIN, OUTPUT);
			Serial.println("CS_PIN set to OUTPUT");
			delay(100);
			//Clear Chip Select
			digitalWrite(CS_PIN,HIGH);
			Serial.println("CS_PIN OUTPUT = HIGH");

		if (DEBUG) {
				Serial.print("Start nmea Rx - serial4 at ");
				Serial.println(model.getSerialBaud4());
			}
		//mSerial1.begin(model.getSerialBaud4()); //talker3
		delay(100);
		if (DEBUG) Serial.println("Start nmea Tx..");
			pinMode(nmeaRxPin, INPUT);
			pinMode(nmeaTxPin, OUTPUT);
			if (DEBUG) {
				Serial.print("Start nmea Tx - on pins 46 Tx, 48 Rx at ");
				Serial.println(model.getSerialBaud5());
			}
		//nmea.begin(model.getSerialBaud5());

		autopilot.init();

		//setup interrupts to windPins
		if (DEBUG) Serial.println("Start wind..");
		pinMode(windSpeedPin, INPUT);
		//digitalWrite (windSpeedPin, HIGH) ;
		attachInterrupt(windSpeedInterrupt, readWDS, RISING);
		pinMode(windDirPin, INPUT);
		//digitalWrite (windDirPin, HIGH) ;
		attachInterrupt(windDirInterrupt, readWDD, RISING);

	//	//setup timers
		if (DEBUG) Serial.println("Start timer..");
		Timer.getAvailable().attachInterrupt(calculate).start(100000);


		if (DEBUG) Serial.println("Setup complete..");
}


// The loop function is called in an endless loop
void loop()
{
	/* tickle the process queue */
	if (false == proc_queue.isEmpty())
	{
		char *sentence = proc_queue.pop();
		if (sentence)
		{
			process(sentence, ',');
			free_queue.push(sentence);
		}
	}

//Add your repeated code here
	if (execute) {
			//timer ping
			//do these every 100ms
			autopilot.calcAutoPilot();

			if (interval % 2 == 0) {
				//do every 200ms
				wind.calcWindSpeedAndDir();
			}
			if (interval % 50 == 0) {
				//do every 500ms
				wind.calcWindSpeedAndDir();
				wind.calcWindData();
				//nmea.printWindNmea();
				//fire any alarms
				alarm.checkAlarms();
				model.writeSimple(Serial);
			}
			if (interval % 100 == 0) {

				//Serial.println(freeMemory());
				//do every 1000ms
				anchor.checkAnchor();
				alarm.checkWindAlarm();
				alarm.checkLvlAlarms();
				rudder.tick_event();
				//nmea.printTrueHeading();

			}

			execute = false;
		}
}


byte getChecksum(char* str) 
{
	byte cs = 0; //clear any old checksum

	for (unsigned int n = 1; ((n < strlen(str) - 1) && ('*' != str[n])); n++) 
	{
		cs ^= str[n]; //calculates the checksum
	}
	return cs;
}



/*********************************************************************************/
/* want to move this to a seperate file */
/*********************************************************************************/

/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.

 See http://joost.damad.be/2012/01/arduino-mega-and-multiple-hardware.html
 */
void serialEvent() {
	while (Serial.available()) {
		serial_input_0.queueChar(Serial.read());
	}
}

void serialEvent1() {
	while (Serial1.available()) {
		serial_input_1.queueChar(Serial1.read());
	}
}

void serialEvent2() {
	while (Serial2.available()) {
		serial_input_2.queueChar(Serial2.read());
	}
}

void serialEvent3() {
	while (Serial3.available()) {
		serial_input_3.queueChar(Serial3.read());
	}
}

// //must call manually every loop - 3+ not in core arduino code
// void serialEvent4() {
// 	while (mSerial1.available()) {
// 		byte b = mSerial1.read();
// 		Serial.println(b);
// 		inputSerial4Complete = talker4.decode(b);
// 		if (inputSerial4Complete) {
// 			//if (MUX) nmea.printNmea(talker4.sentence());
// 			Serial.println(talker4.sentence());
// 			//loop every sentence
// 			break;
// 		}
// 	}
// }

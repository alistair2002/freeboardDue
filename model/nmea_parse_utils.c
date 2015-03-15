#include "autogen_nmea.h"
#include "ctype.h"

/* ddmmyy */
bool parse_nmea_date( nmea_date *date, const char *buffer )
{
	/* dd */
	char numeric[3] = {'\0','\0','\0'};

	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}

	date->day = atoi(numeric);

	/* mm */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}

	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}
	date->month = atoi(numeric);

	/* yy */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}

	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}
	date->year = atoi(numeric);

	return true;
}

/* hhmmss.ss */
bool parse_nmea_time( nmea_time *time, const char *buffer )
{
	char numeric[3] = {'\0','\0','\0'};

	/* hh */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}
	time->hours = atoi( numeric );

	/* mm */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}

	time->minutes = atoi( numeric );

	/* ss */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[1] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}
	time->seconds = atoi( numeric );

	if ((*buffer) && ('.' == (*buffer)))
	{
		buffer++;
	}
	else
	{
		return false;
	}

	/* centiseconds */
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++; 
	}
	else
	{
		return false;
	}
	if ((*buffer) && (isdigit(*buffer)))
	{
		numeric[0] = *buffer;
		buffer++;
	}
	else
	{
		return false;
	}
	time->centiseconds = atoi( numeric );
	
	return true;
}

bool parse_nmea_string( nmea_string *time, const char *buffer )
{
	size_t i = 0;
	time->buffer[0] = '\0';

	while ((*buffer) && (isalnum(*buffer)) && ( i < (sizeof(time->buffer)-1)))
	{
		time->buffer[i++] = *buffer++;
		time->buffer[i] = '\0';
	}

	return true;
}

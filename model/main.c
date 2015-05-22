#include <stdio.h>
#include <stdlib.h>
#include "nmea_model.h"

extern void parse_nmea(char *sentence);

Model model;

int main (int argc, char *argv[1])
{
	if (2 == argc)
	{
		printf("calling parse with (%s)\n", argv[1]);
		model.parse_nmea((const char*)argv[1]);
	}
	return 0;
}

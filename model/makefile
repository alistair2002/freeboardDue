all:
	xsltproc nmea_h.xsl nmea.xml > autogen_nmea.h
	xsltproc nmea_c.xsl nmea.xml > autogen_nmea.c
	xsltproc nmea_test.xsl nmea.xml > autogen_test.bash
	gcc -o unit_test -xc++ -std=c++11 *.c

clean:
	rm -rf unit_test* *.o autogen_*

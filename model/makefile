all:
	xsltproc nmea_h.xsl nmea.xml > nmea.h
	xsltproc nmea_c.xsl nmea.xml > nmea.c
	gcc -o unit_test -xc++ *.c

clean:
	rm -rf unit_test *.o

CPP_SRC = autogen_nmea.xml.cpp \
	nmea_parse_utils.cpp \
	main.c 

all:
	xsltproc nmea_h.xsl autogen_nmea.xml > autogen_nmea.xml.h
	xsltproc nmea_c.xsl autogen_nmea.xml > autogen_nmea.xml.cpp
	xsltproc nmea_test.xsl autogen_nmea.xml > autogen_test.bash
	chmod a+x autogen_test.bash
	gcc -o unit_test -xc++ -std=c++11 $(CPP_SRC) -DDEBUG -Wall

clean:
	rm -rf unit_test* *.o autogen_nmea.xml.h autogen_nmea.xml.cpp autogen_test.bash

CPP_SRC = nmea.xml.cpp \
	nmea_parse_utils.cpp \
	main.c 

all:
	xsltproc nmea_h.xsl nmea.xml > nmea.xml.h
	xsltproc nmea_c.xsl nmea.xml > nmea.xml.cpp
	xsltproc nmea_test.xsl nmea.xml > test.bash
	chmod a+x test.bash
	gcc -o unit_test -xc++ -std=c++11 $(CPP_SRC) -DDEBUG -Wall

clean:
	rm -rf unit_test* *.o nmea.xml.h nmea.xml.cpp test.bash

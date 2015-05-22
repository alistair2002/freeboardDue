CPP_SRC = nmea_model.cpp \
	nmea_parse_utils.cpp \
	main.c 

all:
	xsltproc nmea_h.xsl nmea_model.xml > nmea_model.h
	xsltproc nmea_c.xsl nmea_model.xml > nmea_model.cpp
	xsltproc nmea_test.xsl nmea.xml > test.bash
	chmod a+x test.bash
	gcc -o unit_test -xc++ -std=c++11 $(CPP_SRC) -DDEBUG -Wall

clean:
	rm -rf unit_test* *.o nmea.xml.h nmea_model.cpp test.bash

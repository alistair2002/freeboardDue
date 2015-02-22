freeboardDue
============

This is a 'fork' aka clone of Rob's project.

My hope is to keep in sync but I plan on using a different autopilot system.  I might also add a simple display ...

The biggest change at this stage is that I have added a makefile so I don't need to use eclipse to build the project.

I have cloned this repository and the arduino-1.5.8 repository into a dev directory at the root of home drive for a user called jason.

The makefile finds itself in the directory tree but the ARDUINO_ROOT is specified in the makefile.init file, as is the usb port.

I also have 'make upload' working.  Using bossa and the 1200baud reset magic.

I am using the ArduIMU loaded with FreeBoardIMU and calibrated with freeboard-installer.  This is plugged into the GPS port as it uses 3.3v serial but runs, that is the black header near pin 1 of the ribbon cable.
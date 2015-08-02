CPP_SRCS += \
	functions/Rudder_PID.cpp \
	functions/Rudder.cpp \
	functions/SegOutput.cpp \
	functions/SegDisp.cpp \
	functions/Alarm.cpp \
	functions/Anchor.cpp \
	functions/Autopilot.cpp \
	FreeBoardModel.cpp \
	Gps.cpp \
	NmeaRelay.cpp \
	NmeaSerial.cpp \
	Wind.cpp \
	freeboardDue.cpp 

ifneq (,$(findstring seatalk,$(MAKEFLAGS)))
CPP_SRCS += Seatalk.cpp
endif

XML_SRCS += \
	model/nmea_model.xml

XML_TOOLS += \
	model/nmea_h.xsl \
	model/nmea_c.xsl

CPP_SRCS += \
	model/nmea_parse_utils.cpp

CPP_SRCS += \
	lib/SPI/SPI.cpp 

CPP_SRCS += \
	lib/PString/PString.cpp 

CPP_SRCS += \
	lib/PID_v1/PID_v1.cpp 

CPP_SRCS += \
	lib/NMEA/nmea.cpp 

CPP_SRCS += \
	lib/MultiSerial/MultiSerial.cpp 

CPP_SRCS += \
	lib/Kangaroo/KangarooCRC.cpp \
	lib/Kangaroo/KangarooChannel.cpp \
	lib/Kangaroo/KangarooCommandWriter.cpp \
	lib/Kangaroo/KangarooMonitor.cpp \
	lib/Kangaroo/KangarooReplyReader.cpp \
	lib/Kangaroo/KangarooReplyReceiver.cpp \
	lib/Kangaroo/KangarooSerial.cpp \
	lib/Kangaroo/KangarooStatus.cpp \
	lib/Kangaroo/KangarooTimeout.cpp

CPP_SRCS += \
	lib/SevSeg/SevSeg.cpp

CPP_SRCS += \
	lib/JsonStream/stream_json_reader.cpp 

CPP_SRCS += \
	lib/DueTimer/DueTimer.cpp 

ARDUINO_CPP_SRCS += \
	$(ARDUINO_ROOT)/hardware/arduino/sam/variants/arduino_due_x/variant.cpp 

ARDUINO_C_SRCS += \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/avr/dtostrf.c 

ARDUINO_CPP_SRCS += \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/USB/CDC.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/USB/HID.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/USB/USBCore.cpp 

ARDUINO_CPP_SRCS += \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/IPAddress.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/Print.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/Reset.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/RingBuffer.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/Stream.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/UARTClass.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/USARTClass.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/WMath.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/WString.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/abi.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/main.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/new.cpp \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/wiring_pulse.cpp 

ARDUINO_C_SRCS += \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/WInterrupts.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/cortex_handlers.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/hooks.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/iar_calls_sam3.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/itoa.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/syscalls_sam3.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/wiring.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/wiring_analog.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/wiring_digital.c \
	$(ARDUINO_ROOT)/hardware/arduino/sam/cores/arduino/wiring_shift.c 

ARDUINO_CPP_SRCS += \
	$(ARDUINO_ROOT)/libraries/DueFlashStorage/DueFlashStorage.cpp \
	$(ARDUINO_ROOT)/libraries/DueFlashStorage/flash_efc.cpp \
	$(ARDUINO_ROOT)/libraries/DueFlashStorage/efc.cpp

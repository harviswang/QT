QT += widgets serialport

TARGET = blockingslave.exe
TEMPLATE = app

HEADERS += \
	dialog.h \
	slavethread.h
	
SOURCES += \
	main.cpp \
	dialog.cpp \
	slavethread.cpp
	
QMAKE_CXXFLAGS += -Werror -Wall

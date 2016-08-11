QT += widgets serialport

TARGET = terminal.exe
TEMPLATE = app

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	settingsdialog.cpp \
	console.cpp
	
HEADERS += \
	mainwindow.h \
	settingsdialog.h \
	console.h
	
FORMS += \
	mainwindow.ui \
	settingsdialog.ui

RESOURCES += \
	terminal.qrc

QMAKE_CXXFLAGS += \
    -Werror \
    -Wall
	
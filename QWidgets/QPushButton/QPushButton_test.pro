QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPushButton_test.exe
TEMPLATE = app

HEADERS += \
	QPushButton_test.h

SOURCES += \
	QPushButton_test.cpp \
	main.cpp

QMAKE_CXXFLAGS += \
	-Werror \
	-Wall

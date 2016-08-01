QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blockingmaster.exe
TEMPLATE = app


SOURCES += \
    main.cpp\
    dialog.cpp \
    masterthread.cpp

HEADERS  += \
    dialog.h \
    masterthread.h

QMAKE_CXXFLAGS += \
    -Werror \
    -Wall

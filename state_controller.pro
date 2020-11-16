TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += network

SOURCES += \
        main.cpp \
    networkworker.cpp

HEADERS += \
    networkworker.h

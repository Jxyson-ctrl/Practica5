QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = simulacion

SOURCES += \
    main.cpp \
    particula.cpp \
    obstaculo.cpp \
    simulacion.cpp

HEADERS += \
    particula.h \
    obstaculo.h \
    simulacion.h
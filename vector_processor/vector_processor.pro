TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    register.cpp \
    arithmetic_logic_unit.cpp \
    register_file.cpp

HEADERS += \
    hardware_base.h \
    register.h \
    arithmetic_logic_unit.h \
    register_file.h

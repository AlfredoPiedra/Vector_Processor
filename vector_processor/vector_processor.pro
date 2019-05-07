TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    register.cpp \
    arithmetic_logic_unit.cpp \
    register_file.cpp \
    adder_32_bits.cpp \
    multiplexer_4x1.cpp \
    instruction_memory.cpp \
    data_memory.cpp \
    memory_bank.cpp \
    barrel_shifter.cpp \
    zero_extend.cpp

HEADERS += \
    hardware_base.h \
    register.h \
    arithmetic_logic_unit.h \
    register_file.h \
    adder_32_bits.h \
    multiplexer_4x1.h \
    instruction_memory.h \
    data_memory.h \
    memory_bank.h \
    barrel_shifter.h \
    zero_extend.h

CONFIG += link_pkgconfig
PKGCONFIG += opencv

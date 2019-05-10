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
    fetch.cpp \
    type_adapter.cpp \
    execute.cpp \
    decode.cpp \
    control_unit.cpp \
    multiplexer_2x1.cpp \
    memory.cpp \
    write_back.cpp \
    vectorial_processor.cpp

HEADERS += \
    register.h \
    arithmetic_logic_unit.h \
    register_file.h \
    adder_32_bits.h \
    multiplexer_4x1.h \
    instruction_memory.h \
    data_memory.h \
    memory_bank.h \
    barrel_shifter.h \
    fetch.h \
    type_adapter.h \
    execute.h \
    decode.h \
    control_unit.h \
    multiplexer_2x1.h \
    memory.h \
    write_back.h \
    vectorial_processor.h

CONFIG += link_pkgconfig
PKGCONFIG += opencv

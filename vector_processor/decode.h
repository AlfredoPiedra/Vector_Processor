#ifndef DECODE_H
#define DECODE_H

#include <vector>

#include "register_file.h"
#include "control_unit.h"
#include "multiplexer_2x1.h"
#include "type_adapter.h"

class Decode{

private:

    // ############### Input ##################
    std::vector<unsigned char> decode_instruction;
    // ############### Input ##################

    // ############### Output ##################
    Register *decode_execute;
    // ############### Output ##################

    ControlUnit *control_unit;

    Multiplexer2x1<unsigned char>* operand_a_source;

    unsigned char vector_write_enable;
    unsigned char scalar_write_enable;

    unsigned char vector_write_register;
    unsigned char scalar_write_register;

    std::vector<unsigned char> vector_write_data;
    std::vector<unsigned char> scalar_write_data;

    void OrganizeOutput(unsigned char vector_d,
                        unsigned char register_d,
                        unsigned char register_a,
                        unsigned char register_b,
                        unsigned char vector_a,
                        unsigned char vector_b,
                        unsigned char f_immediate,
                        unsigned int m_immediate,
                        unsigned int i_immediate);

    void DoNegativeEdgeAction();

    void DoPositiveEdgeAction();

    unsigned char flush_execute;

public:

    Decode();

    RegisterFile *scalar_registers;
    RegisterFile *vector_registers;

    void ConfigureInput(std::vector<unsigned char> set_decode_instruction);

    void DoAction(unsigned char clock);

    void ConfigureWrite(unsigned char set_vector_write_enable,
                        unsigned char set_vector_d,
                        unsigned char set_register_write_enable,
                        unsigned char set_register_d,
                        std::vector<unsigned char> set_vector_write_data,
                        std::vector<unsigned char> set_register_write_data);


    void DoFlush(unsigned char stall);

    std::vector<unsigned char> GetHazardUnitInput();

    std::vector<unsigned char> GetOutput();

    void PrintContent();
};

#endif // DECODE_H

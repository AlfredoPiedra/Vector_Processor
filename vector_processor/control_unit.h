#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <vector>
#include <stdexcept>

class ControlUnit{

private:

    // ############### Inputs ##################
    unsigned char operational_code;
    unsigned char i_or_p_bit;
    // ############### Inputs ##################

    // ############### Outputs ##################
    unsigned char register_write;       // 1 bit
    unsigned char vector_write;         // 1 bit
    unsigned char memory_write;         // 1 bit
    unsigned char write_all;            // 1 bit
    unsigned char register_write_src;   // 1 bit
    unsigned char vector_write_src;     // 1 bit
    unsigned char vector_result;        // 2 bit
    unsigned char immediate_src;        // 1 bit
    unsigned char address_src;          // 2 bits
    unsigned char register_d_src;       // 2 bits
    unsigned char alu_control;          // 3 bits
    unsigned char shifter_control;      // 2 bits

    std::vector<unsigned char> control_bits;
    // ############### Outputs ##################

public:

    ControlUnit();

    void ConfigureInput(unsigned char set_operational_code,
                        unsigned char set_i_or_p_bit);

    void DoAction();

    std::vector<unsigned char> GetOutput();
};

#endif // CONTROLUNIT_H

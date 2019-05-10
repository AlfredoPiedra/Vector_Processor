#ifndef EXECUTE_H
#define EXECUTE_H

#include <vector>

#include "register.h"
#include "arithmetic_logic_unit.h"
#include "barrel_shifter.h"
#include "multiplexer_4x1.h"
#include "multiplexer_2x1.h"
#include "adder_32_bits.h"

#include "type_adapter.h"

class Execute{

private:

    // ############### Input ##################
    std::vector<unsigned char> execute_input;
    // ############### Input ##################

    // ############### Output ##################
    Register* execute_memory;
    // ############### Output ##################

    // ############### Vectorial functional unit ##################
    std::vector<ArithmeticLogicUnit> alus;
    std::vector<BarrelShifter> shifters;
    std::vector<Multiplexer2x1<unsigned char>> vector_operand_source;
    std::vector<Multiplexer4x1<unsigned char>> vector_result_source;
    // ############### Vectorial functional unit ##################

    // ############### Scalar functional unit ##################
    Adder *format_i_adder;
    Multiplexer2x1<unsigned int> *operand_b_source;
    Multiplexer4x1<unsigned int> *register_d_result;
    // ############### Scalar functional unit ##################

    Adder *format_m_adder;
    Adder *address_adder;

    Multiplexer4x1<unsigned int> *address_source;

    void OrganizeOutput();

public:

    Execute();

    void ConfigureInput(std::vector<unsigned char> set_execute_input);

    void DoAction();

    std::vector<unsigned char> GetOutput();
};

#endif // EXECUTE_H

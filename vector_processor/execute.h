#ifndef EXECUTE_H
#define EXECUTE_H

#include <vector>
#include <omp.h>

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
    unsigned char register_a_forward;
    unsigned char register_b_forward;
    unsigned char vector_a_forward;
    unsigned char vector_b_forward;
    unsigned int memory_forward_register_data;
    unsigned int writeback_forward_register_data;
    std::vector<unsigned char> memory_forward_vector_data;
    std::vector<unsigned char> writeback_forward_vector_data;
    // ############### Input ##################

    // ############### Output ##################
    Register* execute_memory;
    // ############### Output ##################

    // ############### Vectorial functional unit ##################
    std::vector<ArithmeticLogicUnit> alus;
    std::vector<BarrelShifter> shifters;
    std::vector<Multiplexer2x1<unsigned char>> vector_operand_source;
    std::vector<Multiplexer4x1<unsigned char>> vector_result_source;
    std::vector<Multiplexer4x1<unsigned char>> vector_a_forward_source;
    std::vector<Multiplexer4x1<unsigned char>> vector_b_forward_source;
    // ############### Vectorial functional unit ##################

    // ############### Scalar functional unit ##################
    Adder *format_i_adder;
    Multiplexer2x1<unsigned int> *operand_b_source;
    Multiplexer4x1<unsigned int> *register_d_result;
    Multiplexer4x1<unsigned int> *register_a_forward_source;
    Multiplexer4x1<unsigned int> *register_b_forward_source;
    // ############### Scalar functional unit ##################


    Multiplexer2x1<unsigned char> *register_d_dir;
    Multiplexer4x1<unsigned int> *address_source;
    Adder *format_m_adder;
    Adder *address_adder;

    unsigned int register_a_output;
    unsigned int register_b_output;
    unsigned int i_immediate;
    unsigned int m_immediate;

    std::vector<unsigned char> execute_flags;

    void OrganizeOutput();

    void DoNegativeEdgeAction();

    void DoPositiveEdgeAction();

public:

    Execute();

    void ConfigureInput(std::vector<unsigned char> set_execute_input);

    void ConfigureForwardInput(unsigned char set_register_a_forward,
                               unsigned char set_register_b_forward,
                               unsigned char set_vector_a_forward,
                               unsigned char set_vector_b_forward,
                               unsigned int set_memory_forward_data,
                               unsigned int set_writeback_forward_data,
                               std::vector<unsigned char> set_memory_forward_vector_data,
                               std::vector<unsigned char> set_writeback_forward_vector_data);

    std::vector<unsigned char> GetHazardUnitInput();

    void DoAction(unsigned char clock);

    std::vector<unsigned char> GetOutput();
};

#endif // EXECUTE_H

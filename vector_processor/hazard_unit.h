#ifndef HAZARDUNIT_H
#define HAZARDUNIT_H

#include <iostream>
#include <vector>

class HazardUnit{

public:

    // ############### Inputs ##################
    unsigned char register_d_execute;
    unsigned char register_d_memory;
    unsigned char register_d_writeback;
    unsigned char register_a_decode;
    unsigned char register_b_decode;
    unsigned char register_a_execute;
    unsigned char register_b_execute;
    unsigned char vector_d_execute;
    unsigned char vector_d_memory;
    unsigned char vector_d_writeback;
    unsigned char vector_a_decode;
    unsigned char vector_b_decode;
    unsigned char vector_a_execute;
    unsigned char vector_b_execute;
    unsigned char register_write_memory;
    unsigned char register_write_writeback;
    unsigned char register_write_src_execute;
    unsigned char vector_write_memory;
    unsigned char vector_write_writeback;
    unsigned char vector_write_src_execute;
    // ############### Inputs ##################

    // ############### Output ##################
    std::vector<unsigned char> hazard_unit_output;
    // ############### Output ##################

    unsigned char MatchRegister(unsigned char operand);
    unsigned char MatchVector(unsigned char operand);

//public:

    HazardUnit();

    void ConfigureDecodeInput(unsigned char set_register_a_decode,
                              unsigned char set_register_b_decode,
                              unsigned char set_vector_a_decode,
                              unsigned char set_vector_b_decode);

    void ConfigureExecuteInput(unsigned char set_register_d_execute,
                               unsigned char set_register_a_execute,
                               unsigned char set_register_b_execute,
                               unsigned char set_vector_d_execute,
                               unsigned char set_vector_a_execute,
                               unsigned char set_vector_b_execute,
                               unsigned char set_register_write_src_execute,
                               unsigned char set_vector_write_src_execute);

    void ConfigureMemoryInput(unsigned char set_register_d_memory,
                              unsigned char set_vector_d_memory,
                              unsigned char set_register_write_memory,
                              unsigned char set_vector_write_memory);

    void ConfigureWritebackInput(unsigned char set_register_d_writeback,
                                 unsigned char set_vector_d_writeback,
                                 unsigned char set_register_write_writeback,
                                 unsigned char set_vector_write_writeback);

    void DoAction();

    std::vector<unsigned char> GetOutput();
};

#endif // HAZARDUNIT_H

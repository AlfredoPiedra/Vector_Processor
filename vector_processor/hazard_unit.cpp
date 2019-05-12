#include "hazard_unit.h"

HazardUnit::HazardUnit(){

    // Initialize all the class attributes

    register_d_execute = 0;
    register_d_memory = 0;
    register_d_writeback = 0;

    register_a_decode = 9;
    register_b_decode = 9;
    register_a_execute = 9;
    register_b_execute = 9;

    vector_d_execute = 0;
    vector_d_memory = 0;
    vector_d_writeback = 0;

    vector_a_decode = 17;
    vector_b_decode = 17;
    vector_a_execute = 17;
    vector_b_execute = 17;

    hazard_unit_output.resize(5);
}

void HazardUnit::ConfigureDecodeInput(unsigned char set_register_a_decode,
                                      unsigned char set_register_b_decode,
                                      unsigned char set_vector_a_decode,
                                      unsigned char set_vector_b_decode){

    register_a_decode = set_register_a_decode;
    register_b_decode = set_register_b_decode;

    vector_a_decode = set_vector_a_decode;
    vector_b_decode = set_vector_b_decode;
}


void HazardUnit::ConfigureExecuteInput(unsigned char set_register_d_execute,
                                       unsigned char set_register_a_execute,
                                       unsigned char set_register_b_execute,
                                       unsigned char set_vector_d_execute,
                                       unsigned char set_vector_a_execute,
                                       unsigned char set_vector_b_execute,
                                       unsigned char set_register_write_src_execute,
                                       unsigned char set_vector_write_src_execute){

    register_d_execute = set_register_d_execute;
    register_a_execute = set_register_a_execute;
    register_b_execute = set_register_b_execute;

    vector_d_execute = set_vector_d_execute;
    vector_a_execute = set_vector_a_execute;
    vector_b_execute = set_vector_b_execute;

    register_write_src_execute = set_register_write_src_execute;
    vector_write_src_execute = set_vector_write_src_execute;
}

void HazardUnit::ConfigureMemoryInput(unsigned char set_register_d_memory,
                                      unsigned char set_vector_d_memory,
                                      unsigned char set_register_write_memory,
                                      unsigned char set_vector_write_memory){

    register_d_memory = set_register_d_memory;
    vector_d_memory = set_vector_d_memory;
    register_write_memory = set_register_write_memory;
    vector_write_memory = set_vector_write_memory;
}

void HazardUnit::ConfigureWritebackInput(unsigned char set_register_d_writeback,
                                         unsigned char set_vector_d_writeback,
                                         unsigned char set_register_write_writeback,
                                         unsigned char set_vector_write_writeback){

    register_d_writeback = set_register_d_writeback;
    vector_d_writeback = set_vector_d_writeback;
    register_write_writeback = set_register_write_writeback;
    vector_write_writeback = set_vector_write_writeback;
}

unsigned char HazardUnit::MatchRegister(unsigned char operand){

    if((operand == register_d_memory) && register_write_memory){

        return 0;

    }else if((operand == register_d_writeback) && register_write_writeback){

        return 1;

    }else{

        return 2;
    }
}

unsigned char HazardUnit::MatchVector(unsigned char operand){

    if((operand == vector_d_memory) && vector_write_memory){

        return 0;

    }else if((operand == vector_d_writeback) && vector_write_writeback){


        return 1;

    }else{

        return 2;
    }
}

void HazardUnit::DoAction(){

    hazard_unit_output[0] = MatchRegister(register_a_execute);
    hazard_unit_output[1] = MatchRegister(register_b_execute);
    hazard_unit_output[2] = MatchVector(vector_a_execute);
    hazard_unit_output[3] = MatchVector(vector_b_execute);

    unsigned char register_stall;
    unsigned char vector_stall;

    if(((register_a_decode == register_d_execute)
       || (register_b_decode == register_d_execute))
       && (register_write_src_execute == 1)){

        register_stall = 0;

    }else{

        register_stall = 1;
    }

    if(((vector_a_decode == vector_d_execute)
       || (vector_b_decode == vector_d_execute))
       && (vector_write_src_execute == 1)){

        vector_stall = 0;

    }else{

        vector_stall = 1;
    }

    hazard_unit_output[4] = register_stall & vector_stall;
}

std::vector<unsigned char> HazardUnit::GetOutput(){

    return hazard_unit_output;
}

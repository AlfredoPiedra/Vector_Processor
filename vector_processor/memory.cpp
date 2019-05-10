#include "memory.h"

Memory::Memory(){

    // Initialize all the class attributes
    memory_input.reserve(1);
    memory_input.push_back(0);

    memory_writeback = new Register(27);

    memory_bank = new MemoryBank();

    write_data_source = new Multiplexer2x1<unsigned int>();
}

void Memory::ConfigureInput(std::vector<unsigned char> set_memory_input){

    memory_input = set_memory_input;

}

void Memory::OrganizeOutput(){

    std::vector<unsigned char> memory_output;
    std::vector<unsigned char> read_dataA = adapter::IntegerToBytes(memory_bank->GetOutputA());
    std::vector<unsigned char> read_dataB = adapter::IntegerToBytes(memory_bank->GetOutputB());

    memory_output.resize(27);

    memory_output[0]  = memory_input[0]; // Vd MSB
    memory_output[1]  = memory_input[1];
    memory_output[2]  = memory_input[2];
    memory_output[3]  = memory_input[3];
    memory_output[4]  = memory_input[4];
    memory_output[5]  = memory_input[5];
    memory_output[6]  = memory_input[6];
    memory_output[7]  = memory_input[7];

    memory_output[8]  = memory_input[8]; // Rd MSB
    memory_output[9]  = memory_input[9];
    memory_output[10] = memory_input[10];
    memory_output[11] = memory_input[11];

    memory_output[12] = read_dataA[0]; // RD_A MSB
    memory_output[13] = read_dataA[1];
    memory_output[14] = read_dataA[2];
    memory_output[15] = read_dataA[3];

    memory_output[16] = read_dataB[0]; // RD_B MSB
    memory_output[17] = read_dataB[1];
    memory_output[18] = read_dataB[2];
    memory_output[19] = read_dataB[3];

    memory_output[20] = memory_bank->GetOutputFlag(); // read source
    memory_output[21] = memory_input[24]; // register write source
    memory_output[22] = memory_input[25]; // vector write source
    memory_output[23] = memory_input[22]; // Vd
    memory_output[24] = memory_input[23]; // Rd
    memory_output[25] = memory_input[26]; // register write
    memory_output[26] = memory_input[27]; // vector write

    memory_writeback->ConfigureInput(memory_output);
    memory_writeback->DoAction();
}

void Memory::DoAction(){

    std::vector<unsigned char> buffer;

    buffer.push_back(memory_input[0]);
    buffer.push_back(memory_input[1]);
    buffer.push_back(memory_input[2]);
    buffer.push_back(memory_input[3]);

    unsigned int vector_d_output_msb = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[4];
    buffer[1] = memory_input[5];
    buffer[2] = memory_input[6];
    buffer[3] = memory_input[7];

    unsigned int vector_d__output_lsb = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[8];
    buffer[1] = memory_input[9];
    buffer[2] = memory_input[10];
    buffer[3] = memory_input[11];

    unsigned int register_d_output = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[12];
    buffer[1] = memory_input[13];
    buffer[2] = memory_input[14];
    buffer[3] = memory_input[15];

    unsigned int address = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[16];
    buffer[1] = memory_input[17];
    buffer[2] = memory_input[18];
    buffer[3] = memory_input[19];

    unsigned int address_plus_4 = adapter::BytesToInteger(buffer);

    unsigned char write_enable = memory_input[20];
    unsigned char write_all    = memory_input[21];

    unsigned char vector_d   = memory_input[22];
    unsigned char register_d = memory_input[23];

    write_data_source->ConfigureInput(register_d_output,
                                      vector_d_output_msb,
                                      write_all);

    write_data_source->DoAction();

    memory_bank->ConfigureInput(address,
                                address_plus_4,
                                write_data_source->GetOutput(),
                                vector_d__output_lsb,
                                write_enable,
                                write_all);
    memory_bank->DoAction();

    OrganizeOutput();
}

std::vector<unsigned char> Memory::GetOutput(){

    return memory_writeback->GetOutput();
}

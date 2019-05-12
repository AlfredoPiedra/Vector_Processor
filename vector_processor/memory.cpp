#include "memory.h"

Memory::Memory(){

    // Initialize all the class attributes
    memory_input.reserve(1);
    memory_input.push_back(0);

    memory_writeback = new Register(27);

    memory_bank = new MemoryBank();

    address = 0;
    address_plus_4 = 4;
    vector_d_output_lsb = 0;

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
}

void Memory::DoNegativeEdgeAction(){

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

    vector_d_output_lsb = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[8];
    buffer[1] = memory_input[9];
    buffer[2] = memory_input[10];
    buffer[3] = memory_input[11];

    unsigned int register_d_output = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[12];
    buffer[1] = memory_input[13];
    buffer[2] = memory_input[14];
    buffer[3] = memory_input[15];

    address = adapter::BytesToInteger(buffer);

    buffer[0] = memory_input[16];
    buffer[1] = memory_input[17];
    buffer[2] = memory_input[18];
    buffer[3] = memory_input[19];

    address_plus_4 = adapter::BytesToInteger(buffer);

    write_data_source->ConfigureInput(register_d_output,
                                      vector_d_output_msb,
                                      memory_input[21]); // write all

    write_data_source->DoAction();

    memory_bank->ConfigureReadInput(address,
                                    address_plus_4);

    memory_bank->DoReadAction();

    OrganizeOutput();
}


void Memory::DoPositiveEdgeAction(){

    memory_bank->ConfigureWriteInput(address,
                                     address_plus_4,
                                     write_data_source->GetOutput(),
                                     vector_d_output_lsb,
                                     memory_input[20],  // write enable
                                     memory_input[21]); // write all

    memory_bank->DoWriteAction();

    memory_writeback->DoAction();

}

void Memory::DoAction(unsigned char clock){

    // Write in the registers on posedge
    if(clock){

        DoPositiveEdgeAction();

    // Read the registers values on negedge
    }else{

        DoNegativeEdgeAction();
    }
}

std::vector<unsigned char> Memory::GetHazardUnitInput(){

    std::vector<unsigned char> hazard_input;
    hazard_input.resize(16);

    hazard_input[0] = memory_input[23];
    hazard_input[1] = memory_input[22];
    hazard_input[2] = memory_input[26];
    hazard_input[3] = memory_input[27];
    hazard_input[4] = memory_input[8];
    hazard_input[5] = memory_input[9];
    hazard_input[6] = memory_input[10];
    hazard_input[7] = memory_input[11];

    hazard_input[8]  = memory_input[0];
    hazard_input[9]  = memory_input[1];
    hazard_input[10] = memory_input[2];
    hazard_input[11] = memory_input[3];
    hazard_input[12] = memory_input[4];
    hazard_input[13] = memory_input[5];
    hazard_input[14] = memory_input[6];
    hazard_input[15] = memory_input[7];

    return hazard_input;
}

std::vector<unsigned char> Memory::GetOutput(){

    return memory_writeback->GetOutput();
}

MemoryBank Memory::GetMemoryBank(){

    return *memory_bank;
}

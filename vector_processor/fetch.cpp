#include "fetch.h"

Fetch::Fetch(){

    // Instance a 4 bytes (32 bits) register to be the PC
    pc = new Register(4);

    // Instance a 4 bytes (32 bits) register to be the inter-stage (Fetch-Decode) register
    fetch_decode = new Register(4);

    // Adder use to calculate PC + 4
    pc_plus_4 = new Adder();

    // Instance a memory for the instructions
    instruction_memory = new InstructionMemory();
}

void Fetch::DoAction(){

    std::vector<unsigned char> pc_bytes = pc->GetOutput();

    unsigned int pc_value = adapter::BytesToInteger(pc_bytes);

    instruction_memory->ConfigureInput(pc_value);

    instruction_memory->DoAction();

    pc_plus_4->ConfigureInput(pc_value,4);

    pc_plus_4->DoAction();

    pc_bytes = adapter::IntegerToBytes(pc_plus_4->GetOutput());

    pc->ConfigureInput(pc_bytes);

    pc->DoAction();

    unsigned int read_instruction = instruction_memory->GetOutput();

    std::cout << (int) read_instruction << std::endl;

    fetch_decode->ConfigureInput(adapter::IntegerToBytes(read_instruction));

    fetch_decode->DoAction();
}

std::vector<unsigned char> Fetch::GetOutput(){

    return fetch_decode->GetOutput();

}

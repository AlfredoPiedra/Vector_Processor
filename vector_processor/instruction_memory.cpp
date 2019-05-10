#include "instruction_memory.h"

InstructionMemory::InstructionMemory()
{
    // Initialize all the class attributes
    input_address = 0;
    output_data = 0;

    // Set a default value of 1024 words = 4kB
    memory_size = 1024;

    // Allocate the memory
    memory_data.resize(memory_size);

    WriteInstructions();

}

InstructionMemory::InstructionMemory(unsigned int in_memory_size){

    // Initialize all the class attributes
    input_address = 0;
    output_data = 0;

    // Set the specified memory size
    memory_size = in_memory_size;

    // Allocate the memory
    memory_data.resize(memory_size);

    WriteInstructions();

}

void InstructionMemory::WriteInstructions(){

    unsigned int memory_pos = 0;

    std::string instruction;

    std::ifstream instruction_file("/home/alfredo/VectorProcessor/app.txt");

    if(instruction_file.is_open()){

        while( getline(instruction_file, instruction)){

            if(memory_pos >= memory_size){

                throw std::runtime_error("[WriteInstructions]: source code don't fit in the instruction memory");
            }

            memory_data[memory_pos] = (unsigned int) strtol(instruction.c_str(),0,16);

            ++memory_pos;

        }

        instruction_file.close();

    }else{

        throw std::runtime_error("[WriteInstructions]: can't open the instruction source file");
    }

}

void InstructionMemory::ConfigureInput(unsigned int input_memory_address){

    // The memory address must be 4 byte aligned
    input_address = input_memory_address >> 2;
}

void InstructionMemory::DoAction(){

    output_data = memory_data[input_address];
}

unsigned int InstructionMemory::GetOutput(){

    return output_data;
}

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

    instruction_counter = 0;
    source_code_limit = 1;

    WriteInstructions("/home/alfredo/VectorProcessor/app.txt");

}

InstructionMemory::InstructionMemory(unsigned int in_memory_size)
{
    // Initialize all the class attributes
    input_address = 0;
    output_data = 0;

    // Set the specified memory size
    memory_size = in_memory_size;

    // Allocate the memory
    memory_data.resize(memory_size);

    instruction_counter = 0;
    source_code_limit = 1;

    WriteInstructions("/home/alfredo/VectorProcessor/app.txt");

}

InstructionMemory::InstructionMemory(unsigned int in_memory_size,
                                     std::string user_program){

    // Initialize all the class attributes
    input_address = 0;
    output_data = 0;

    // Set the specified memory size
    memory_size = in_memory_size;

    // Allocate the memory
    memory_data.resize(memory_size);

    instruction_counter = 0;
    source_code_limit = 1;

    WriteInstructions(user_program);

}

void InstructionMemory::WriteInstructions(std::string program){

    unsigned int memory_pos = 0;

    std::string instruction;

    std::ifstream instruction_file(program);

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

    number_of_instructions = memory_pos + 7;
}

void InstructionMemory::ConfigureInput(unsigned int input_memory_address){

    // The memory address must be 4 byte aligned
    input_address = input_memory_address >> 2;
}

void InstructionMemory::DoAction(){

    if(instruction_counter >= number_of_instructions){

        source_code_limit = 0;
        output_data = 0;

    }else{

        output_data = memory_data[input_address];
        instruction_counter = input_address;
    }
}

unsigned int InstructionMemory::GetOutput(){

    return output_data;
}

unsigned char InstructionMemory::GetSourceCodeLimit(){

    return source_code_limit;
}

unsigned int InstructionMemory::GetMemorySize(){

    return memory_size;
}

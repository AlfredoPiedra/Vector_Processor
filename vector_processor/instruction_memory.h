#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class InstructionMemory
{

private:

    unsigned int memory_size;

    std::vector<unsigned int>  memory_data;

    // ############### Input ##################

    unsigned int input_address;

    // ############### Input ##################

    // ############### Output ##################

    unsigned int output_data;

    // ############### Output ##################


    unsigned char source_code_limit;
    unsigned int instruction_counter;
    unsigned int number_of_instructions;

public:

    InstructionMemory();

    InstructionMemory(unsigned int in_memory_size);

    InstructionMemory(unsigned int in_memory_size,
                      std::string user_program);

    // Function used to write the user program
    // instructions in the memory
    void WriteInstructions(std::string program);

    void ConfigureInput(unsigned int input_memory_address);

    void DoAction();

    unsigned int GetOutput();

    unsigned char GetSourceCodeLimit();

    unsigned int GetMemorySize();

};

#endif // INSTRUCTIONMEMORY_H

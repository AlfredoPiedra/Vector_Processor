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


    // Function used to write the user program
    // instructions in the memory
    void WriteInstructions();

public:

    InstructionMemory();

    InstructionMemory(unsigned int in_memory_size);

    void ConfigureInput(unsigned int input_memory_address);

    void DoAction();

    unsigned int GetOutput();

};

#endif // INSTRUCTIONMEMORY_H

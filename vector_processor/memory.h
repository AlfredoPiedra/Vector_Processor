#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "register.h"
#include "memory_bank.h"
#include "multiplexer_2x1.h"

#include "type_adapter.h"

class Memory{

private:

    // ############### Input ##################
    std::vector<unsigned char> memory_input;
    // ############### Input ##################

    // ############### Output ##################
    Register* memory_writeback;
    // ############### Output ##################

    Multiplexer2x1<unsigned int> *write_data_source;

    unsigned int address;
    unsigned int address_plus_4;
    unsigned int vector_d_output_lsb;

    void OrganizeOutput();

    void DoPositiveEdgeAction();

    void DoNegativeEdgeAction();

public:

    MemoryBank *memory_bank;

    Memory();

    void ConfigureInput(std::vector<unsigned char> set_memory_input);

    void DoAction(unsigned char clock);

    std::vector<unsigned char> GetHazardUnitInput();

    std::vector<unsigned char> GetOutput();

    MemoryBank GetMemoryBank();
};

#endif // MEMORY_H

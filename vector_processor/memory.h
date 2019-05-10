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

    MemoryBank *memory_bank;

    Multiplexer2x1<unsigned int> *write_data_source;

    void OrganizeOutput();

public:

    Memory();

    void ConfigureInput(std::vector<unsigned char> set_memory_input);

    void DoAction();

    std::vector<unsigned char> GetOutput();
};

#endif // MEMORY_H

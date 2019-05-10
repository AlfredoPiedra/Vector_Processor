#ifndef FETCH_H
#define FETCH_H

#include "instruction_memory.h"
#include "adder_32_bits.h"
#include "register.h"

#include "type_adapter.h"

class Fetch{

private:

        Register *pc;
        Register *fetch_decode;

        Adder *pc_plus_4;

        InstructionMemory *instruction_memory;

public:

    Fetch();

    void DoAction();

    std::vector<unsigned char> GetOutput();

};

#endif // FETCH_H

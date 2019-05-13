#ifndef FETCH_H
#define FETCH_H

#include <string>

#include "instruction_memory.h"
#include "adder_32_bits.h"
#include "register.h"

#include "type_adapter.h"

class Fetch{

private:

        Register *fetch_decode;

        Adder *pc_plus_4;

        InstructionMemory *instruction_memory;

        void DoNegativeEdgeAction();

        void DoPositiveEdgeAction();

public:

    unsigned char fetch_stall;

    Register *pc;

    Fetch();

    void DoAction(unsigned char clock);

    std::vector<unsigned char> GetOutput();

    void DoStall(unsigned char stall);

    unsigned int GetSourceCodeLimit();

    void LoadUserProgram(std::string path);

    void ResetPC();
};

#endif // FETCH_H

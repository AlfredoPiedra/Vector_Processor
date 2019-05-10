#ifndef VECTORIALPROCESSOR_H
#define VECTORIALPROCESSOR_H

#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memory.h"
#include "write_back.h"


class VectorialProcessor{

private:

    Fetch *fetch_stage;

    Decode *decode_stage;

    Execute *execute_stage;

    Memory *memory_stage;

    WriteBack * writeback_stage;

    void PrintBuffer(std::vector<unsigned char> buffer);

public:

    VectorialProcessor();

    void StartProcessing();

};

#endif // VECTORIALPROCESSOR_H

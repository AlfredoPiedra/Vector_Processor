#ifndef VECTORIALPROCESSOR_H
#define VECTORIALPROCESSOR_H

#include <pthread.h>
#include <unistd.h>
#include <string>

#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memory.h"
#include "write_back.h"
#include "hazard_unit.h"

#define IMAGE_ROWS 120
#define IMAGE_COLS 120

class VectorialProcessor{

private:

    static Fetch fetch_stage;
    static Decode decode_stage;
    static Execute execute_stage;
    static Memory memory_stage;
    static WriteBack writeback_stage;
    static HazardUnit hazard_unit;

    static unsigned char clock;

    static void PrintBuffer(std::vector<unsigned char> buffer);

    static void* StartFetchStage(void *ptr);
    static void* StartDecodeStage(void *ptr);
    static void* StartExecuteStage(void *ptr);
    static void* StartMemoryStage(void *ptr);
    static void* StartWritebackStage(void *ptr);

    void SolveHazards();

public:

    VectorialProcessor();

    void LoadProgram(std::string file_name);

    void ReadAllMemory();

    void CompleteProcessing();

    void CycleProcessing();

};

#endif // VECTORIALPROCESSOR_H

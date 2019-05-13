#ifndef MEMORYBANK_H
#define MEMORYBANK_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "data_memory.h"
#include "type_adapter.h"

class MemoryBank
{

private:

    // ############### Input ##################
    unsigned int input_addressA;
    unsigned int input_addressB;
    unsigned int input_dataA;
    unsigned int input_dataB;
    unsigned char write_enable;
    unsigned char write_all;
    // ############### Input ##################

    // ############### Output ##################
    unsigned int read_dataA;
    unsigned int read_dataB;
    unsigned char read_source;
    // ############### Output ##################

    DataMemory *data_memory_a;
    DataMemory *data_memory_b;

    void WriteImageData(std::string image_full_path);

    void MapWriteMemory(unsigned int address,
                        unsigned int data,
                        unsigned char write_enable);

    void MapReadMemory(unsigned int address);

public:

    MemoryBank();

    MemoryBank(unsigned int memory_size);

    void ConfigureReadInput(unsigned int set_input_addressA,
                            unsigned int set_input_addressB);

    void ConfigureWriteInput(unsigned int set_input_addressA,
                             unsigned int set_input_addressB,
                             unsigned int set_input_dataA,
                             unsigned int set_input_dataB,
                             unsigned char set_write_enable,
                             unsigned char set_write_all);

    void DoReadAction();
    void DoWriteAction();

    void LoadImage(std::string file_name);

    unsigned int GetOutputA();
    unsigned int GetOutputB();
    unsigned char GetOutputFlag();
};

#endif // MEMORYBANK_H

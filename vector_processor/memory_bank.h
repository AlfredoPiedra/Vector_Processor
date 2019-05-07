#ifndef MEMORYBANK_H
#define MEMORYBANK_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "data_memory.h"

class MemoryBank
{

private:

    DataMemory* data_memory_a;
    DataMemory* data_memory_b;

    // ############### Input ##################

    unsigned int input_address;

    // ############### Input ##################

    // ############### Output ##################

    unsigned int read_data;

    // ############### Output ##################

    void WriteImageData();

public:

    MemoryBank();

    MemoryBank(unsigned int memory_size);

    void ConfigureInput(unsigned int set_input_address,
                        unsigned char set_write_enable,
                        unsigned int set_write_data);

    void DoAction();

    unsigned int GetOutput();

};

#endif // MEMORYBANK_H

#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <iostream>
#include <vector>

class DataMemory
{

private:

    unsigned int memory_size;

    std::vector<unsigned int>  memory_data;

    // ############### Inputs ##################

    unsigned int input_address;

    unsigned char write_enable;

    unsigned int write_data;

    // ############### Inputs ##################

    // ############### Output ##################

    unsigned int read_data;

    // ############### Output ##################

public:

    DataMemory();

    DataMemory(unsigned int set_memory_size);

    void ConfigureInput(unsigned int set_input_address,
                        unsigned char set_write_enable,
                        unsigned int set_write_data);

    void DoAction();

    unsigned int GetOutput();

};

#endif // DATAMEMORY_H

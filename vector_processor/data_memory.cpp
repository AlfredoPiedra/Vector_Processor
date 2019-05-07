#include "data_memory.h"

DataMemory::DataMemory(){

    // Initialize all the class attributes

    write_enable = 0;
    write_data = 0;
    input_address = 0;
    read_data = 0;

    // Set a default value of 1024 words = 4kB
    memory_size = 1024;

    memory_data.reserve(memory_size);

    unsigned int word;

    for(word = 0; word < memory_size; ++word){

        memory_data[word] = 0;
    }
}

DataMemory::DataMemory(unsigned int set_memory_size){

    // Initialize all the class attributes

    write_enable = 0;
    write_data = 0;
    input_address = 0;
    read_data = 0;

    memory_size = set_memory_size;

    memory_data.reserve(memory_size);

    unsigned int word;

    for(word = 0; word < memory_size; ++word){

        memory_data[word] = 0;
    }
}

void DataMemory::ConfigureInput(unsigned int set_input_address,
                                unsigned char set_write_enable,
                                unsigned int set_write_data){

    // The memory address must be 4 byte aligned
    input_address = set_input_address >> 2;

    write_enable = set_write_enable;

    write_data = set_write_data;

}

void DataMemory::DoAction(){

    read_data = memory_data[input_address];

    if(write_enable){

        memory_data[input_address] = write_data;
    }

}

unsigned int DataMemory::GetOutput(){


    return read_data;
}

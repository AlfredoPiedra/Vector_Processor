#include "data_memory.h"

DataMemory::DataMemory(){

    // Initialize all the class attributes

    write_enable = 0;
    write_data = 0;
    input_address = 0;
    read_data = 0;

    // Set a default value of 1024 words = 4kB
    memory_size = 1024;

    memory_data.resize(memory_size);
}

DataMemory::DataMemory(unsigned int set_memory_size){

    // Initialize all the class attributes

    write_enable = 0;
    write_data = 0;
    input_address = 0;
    read_data = 0;

    memory_size = set_memory_size;

    memory_data.resize(memory_size);

}

void DataMemory::ConfigureReadInput(unsigned int set_input_address){

    // The memory address must be 4 byte aligned
    input_address = set_input_address >> 2;
}

void DataMemory::ConfigureWriteInput(unsigned int set_input_address,
                                     unsigned char set_write_enable,
                                     unsigned int set_write_data){

    // The memory address must be 4 byte aligned
    input_address = set_input_address >> 2;

    write_enable = set_write_enable;

    write_data = set_write_data;

}

void DataMemory::DoReadAction(){

    if(input_address >= memory_size){

        read_data = 0;
        //throw std::runtime_error("[DoReadAction]: memory  address out of bounds");

    }else{

        read_data = memory_data[input_address];

    }
}

void DataMemory::DoWriteAction(){

    if(write_enable){

        if(input_address >= memory_size){

            throw std::runtime_error("[DoWriteAction]: memory  address out of bounds");

        }

        memory_data[input_address] = write_data;
    }

}

unsigned int DataMemory::GetOutput(){

    return read_data;
}

unsigned int DataMemory::GetMemorySize(){

    return memory_size;
}

void DataMemory::PrintContent(){

    int i;

    for(i = 0; i < (int) memory_size; ++i){

        std::cout << "Pos " << i << ": " << (int) memory_data[i] << std::endl;

    }
}

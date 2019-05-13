#include "memory_bank.h"

MemoryBank::MemoryBank(){

    input_addressA = 0;
    input_addressB = 0;

    input_dataA = 0;
    input_dataB = 0;

    read_dataA = 0;
    read_dataB = 0;

    write_enable = 0;
    write_all = 0;

    data_memory_a = new DataMemory(16384);
    data_memory_b = new DataMemory(16384);

    WriteImageData("/home/alfredo/VectorProcessor/images/image.png");

}

MemoryBank::MemoryBank(unsigned int memory_size){

    input_addressA = 0;
    input_addressB = 0;

    input_dataA = 0;
    input_dataB = 0;

    read_dataA = 0;
    read_dataB = 0;

    write_enable = 0;
    write_all = 0;

    data_memory_a = new DataMemory(memory_size);
    data_memory_b = new DataMemory(memory_size);

    WriteImageData("/home/alfredo/VectorProcessor/images/image.png");
}

void MemoryBank::WriteImageData(std::string image_full_path){

    cv::Mat_<unsigned char> image_data;

    image_data = cv::imread(image_full_path,cv::IMREAD_GRAYSCALE);

    if(!image_data.data) throw std::runtime_error("[WriteImageData]: could not find image");

    int row,column;

    unsigned int pixels = 0;

    unsigned int bank_address = 0;

    unsigned int memory_address;

    for(row = 0; row < image_data.rows; ++row){

        for(column = 0; column < image_data.cols; column+=4){

            pixels = image_data(row,column);

            pixels = pixels << 8;

            pixels = pixels | image_data(row, column + 1);

            pixels = pixels << 8;

            pixels = pixels | image_data(row, column + 2);

            pixels = pixels << 8;

            pixels = pixels | image_data(row, column + 3);

            if(bank_address % 2 == 0){

                memory_address = (bank_address / 2) << 2;

                data_memory_a->ConfigureWriteInput(memory_address,
                                                    1,
                                                    pixels);
                data_memory_a->DoWriteAction();

            }else{

                memory_address = ((bank_address - 1) / 2) << 2;

                data_memory_b->ConfigureWriteInput(memory_address,
                                                   1,
                                                    pixels);
                data_memory_b->DoWriteAction();
            }

            pixels = 0;
            ++bank_address;
        }
    }
}

void MemoryBank::ConfigureReadInput(unsigned int set_input_addressA,
                                    unsigned int set_input_addressB){

    input_addressA = set_input_addressA >> 2;
    input_addressB = set_input_addressB >> 2;
}

void MemoryBank::ConfigureWriteInput(unsigned int set_input_addressA,
                                     unsigned int set_input_addressB,
                                     unsigned int set_input_dataA,
                                     unsigned int set_input_dataB,
                                     unsigned char set_write_enable,
                                     unsigned char set_write_all){

    input_addressA = set_input_addressA >> 2;
    input_addressB = set_input_addressB >> 2;

    input_dataA = set_input_dataA;
    input_dataB = set_input_dataB;

    write_enable = set_write_enable;
    write_all = set_write_all;
}


void MemoryBank::MapReadMemory(unsigned int address){

    if(address % 2 == 0){

        address = (address / 2) << 2;

        data_memory_a->ConfigureReadInput(address);

        data_memory_a->DoReadAction();

        read_dataA = data_memory_a->GetOutput();
        read_source = 0;

    }else{

        address = ((address - 1) / 2) << 2;

        data_memory_b->ConfigureReadInput(address);

        data_memory_b->DoReadAction();

        read_dataB = data_memory_b->GetOutput();
        read_source = 1;
    }
}

void MemoryBank::MapWriteMemory(unsigned int address,
                                 unsigned int data,
                                 unsigned char write_enable){
    if(address % 2 == 0){

        address = (address / 2) << 2;

        data_memory_a->ConfigureWriteInput(address,
                                           write_enable,
                                           data);

        data_memory_a->DoWriteAction();

    }else{

        address = ((address - 1) / 2) << 2;

        data_memory_b->ConfigureWriteInput(address,
                                           write_enable,
                                           data);

        data_memory_b->DoWriteAction();
    }
}

void MemoryBank::DoReadAction(){

    MapReadMemory(input_addressA);
    MapReadMemory(input_addressB);
}

void MemoryBank::DoWriteAction(){

    MapWriteMemory(input_addressA,
                   input_dataA,
                   write_enable);

    if(write_all){

        MapWriteMemory(input_addressB,
                       input_dataB,
                       write_enable);
    }
}

unsigned int MemoryBank::GetOutputA(){

    return read_dataA;
}

unsigned int MemoryBank::GetOutputB(){

    return read_dataB;
}

unsigned char MemoryBank::GetOutputFlag(){

    return read_source;
}

void MemoryBank::LoadImage(std::string file_name){

    WriteImageData(file_name);
}

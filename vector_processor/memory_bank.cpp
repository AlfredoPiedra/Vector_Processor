#include "memory_bank.h"

MemoryBank::MemoryBank(){

    input_address = 0;

    read_data = 0;

    data_memory_a = new DataMemory();

    data_memory_b = new DataMemory();

    WriteImageData();

}

MemoryBank::MemoryBank(unsigned int memory_size){

    read_data = 0;

    input_address = 0;

    data_memory_a = new DataMemory(memory_size);

    data_memory_b = new DataMemory(memory_size);

    WriteImageData();
}

void MemoryBank::WriteImageData(){

    cv::Mat_<unsigned char> image_data;

    image_data = cv::imread("/home/alfredo/VectorProcessor/image.png",cv::IMREAD_GRAYSCALE);

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

                data_memory_a->ConfigureInput(memory_address,
                                             1,
                                             pixels);
                data_memory_a->DoAction();

            }else{

                memory_address = ((bank_address - 1) / 2) << 2;

                data_memory_b->ConfigureInput(memory_address,
                                             1,
                                             pixels);
                data_memory_b->DoAction();
            }

            pixels = 0;
            ++bank_address;
        }
    }
}

void MemoryBank::ConfigureInput(unsigned int set_input_address,
                                unsigned char set_write_enable,
                                unsigned int set_write_data){

    input_address = set_input_address >> 2;

    unsigned int memory_address = input_address;

    if(memory_address % 2 == 0){

        memory_address = (memory_address / 2) << 2;

    }else{

        memory_address = ((memory_address - 1) / 2) << 2;
    }

    data_memory_a->ConfigureInput(memory_address,
                                  set_write_enable,
                                  set_write_data);

    data_memory_b->ConfigureInput(memory_address,
                                  set_write_enable,
                                  set_write_data);
}

void MemoryBank::DoAction(){

    if(input_address % 2 == 0){

        data_memory_a->DoAction();

        read_data = data_memory_a->GetOutput();

    }else{

        data_memory_b->DoAction();

        read_data = data_memory_b->GetOutput();
    }
}

unsigned int MemoryBank::GetOutput(){

    return read_data;
}

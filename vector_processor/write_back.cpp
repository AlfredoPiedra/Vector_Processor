#include "write_back.h"

WriteBack::WriteBack(){

    // Initiliaze all the class attributes
    writeback_input.reserve(1);
    writeback_output.resize(16);

    writeback_input.push_back(0);

    vector_d_msb_source = new Multiplexer2x1<unsigned int>();
    vector_d_lsb_source = new Multiplexer2x1<unsigned int>();
    register_d_source = new Multiplexer2x1<unsigned int>();
    read_data_source = new Multiplexer2x1<unsigned int>();
}

void WriteBack::ConfigureInput(std::vector<unsigned char> set_writeback_input){

    writeback_input = set_writeback_input;
}

void WriteBack::OrganizeOutput(){

    std::vector<unsigned char> vector_d_msb = adapter::IntegerToBytes(vector_d_msb_source->GetOutput());
    std::vector<unsigned char> vector_d_lsb = adapter::IntegerToBytes(vector_d_lsb_source->GetOutput());
    std::vector<unsigned char> register_d = adapter::IntegerToBytes(register_d_source->GetOutput());

    writeback_output[0]  = vector_d_msb[0];
    writeback_output[1]  = vector_d_msb[1];
    writeback_output[2]  = vector_d_msb[2];
    writeback_output[3]  = vector_d_msb[3];

    writeback_output[4]  = vector_d_lsb[0];
    writeback_output[5]  = vector_d_lsb[1];
    writeback_output[6]  = vector_d_lsb[2];
    writeback_output[7]  = vector_d_lsb[3];

    writeback_output[8]  = register_d[0];
    writeback_output[9]  = register_d[1];
    writeback_output[10] = register_d[2];
    writeback_output[11] = register_d[3];

    writeback_output[12] = writeback_input[23]; // Vd
    writeback_output[13] = writeback_input[24]; // Rd

    writeback_output[14] = writeback_input[25]; // register write
    writeback_output[15] = writeback_input[26]; // vector write
}

void WriteBack::DoAction(){

    std::vector<unsigned char> buffer;

    buffer.push_back(writeback_input[0]);
    buffer.push_back(writeback_input[1]);
    buffer.push_back(writeback_input[2]);
    buffer.push_back(writeback_input[3]);

    unsigned int vector_d_output_msb = adapter::BytesToInteger(buffer);

    buffer[0] = writeback_input[4];
    buffer[1] = writeback_input[5];
    buffer[2] = writeback_input[6];
    buffer[3] = writeback_input[7];

    unsigned int vector_d_output_lsb = adapter::BytesToInteger(buffer);

    buffer[0] = writeback_input[8];
    buffer[1] = writeback_input[9];
    buffer[2] = writeback_input[10];
    buffer[3] = writeback_input[11];

    unsigned int register_d_output = adapter::BytesToInteger(buffer);

    buffer[0] = writeback_input[12];
    buffer[1] = writeback_input[13];
    buffer[2] = writeback_input[14];
    buffer[3] = writeback_input[15];

    unsigned int read_data_a = adapter::BytesToInteger(buffer);

    buffer[0] = writeback_input[16];
    buffer[1] = writeback_input[17];
    buffer[2] = writeback_input[18];
    buffer[3] = writeback_input[19];

    unsigned int read_data_b = adapter::BytesToInteger(buffer);

    unsigned char read_source = writeback_input[20];
    unsigned char register_write_src = writeback_input[21];
    unsigned char vector_write_src = writeback_input[22];
    unsigned char Vd = writeback_input[23];
    unsigned char Rd = writeback_input[24];


    read_data_source->ConfigureInput(read_data_a,
                                     read_data_b,
                                     read_source);
    read_data_source->DoAction();

    vector_d_msb_source->ConfigureInput(read_data_a,
                                        vector_d_output_msb,
                                        vector_write_src);

    vector_d_msb_source->DoAction();

    vector_d_lsb_source->ConfigureInput(read_data_b,
                                        vector_d_output_lsb,
                                        vector_write_src);
    vector_d_lsb_source->DoAction();

    register_d_source->ConfigureInput(read_data_source->GetOutput(),
                                      register_d_output,
                                      register_write_src);
    register_d_source->DoAction();

    OrganizeOutput();
}

std::vector<unsigned char> WriteBack::GetOutput(){

    return writeback_output;
}

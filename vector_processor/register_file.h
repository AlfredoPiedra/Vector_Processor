#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <iostream>
#include <vector>
#include <stdexcept>

#include "register.h"

class RegisterFile
{

private:

    // Total number of register in the register file
    unsigned char total_registers;

    // Pointer to the array of register objects
    std::vector<Register> register_file;

    // ############### Inputs ##################

    // Write enable signal
    unsigned char write_enable;

    // Registers from which the data will be read
    unsigned char read_register_a;
    unsigned char read_register_b;

    // Register in which the data will be written
    unsigned char write_register;

    // Data that will be written in a register
    std::vector<unsigned char> write_data;

    // ############### Inputs ##################


    // ############### Outputs ##################

    // The data read from the register file
    std::vector<unsigned char> read_data_a;
    std::vector<unsigned char> read_data_b;

    // ############### Outputs ##################

    // Function used to access a particular
    // register in the register file
    std::vector<unsigned char> ReadRegister(unsigned char register_number);

    // Function used to write in a particular
    // register in the register file
    void WriteRegister(unsigned char register_number,
                       std::vector<unsigned char> data);

public:

    // Constructors of the class
    RegisterFile();
    RegisterFile(unsigned char number_of_registers,
                 unsigned char size_of_registers);

    void ConfigureInput(unsigned char write_enable_signal,
                        unsigned char in_read_register_a,
                        unsigned char in_read_register_b,
                        unsigned char in_write_register,
                        std::vector<unsigned char> in_write_data);

    void DoAction();

    std::vector<unsigned char> GetOutputDataA();

    std::vector<unsigned char> GetOutputDataB();

};

#endif // REGISTERFILE_H

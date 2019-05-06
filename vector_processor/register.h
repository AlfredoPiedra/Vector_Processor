#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <vector>

#include "hardware_base.h"

class Register: public HardwareBase
{

private:

    unsigned char register_size;
    std::vector<unsigned char> input_data;
    std::vector<unsigned char> output_data;

public:

    char signal_enable;

    // Constructors of the class
    Register();
    Register(unsigned char);

    // Override the base class function
    void DoAction();

    // Function executed on reset
    void DoReset();

    // Function used to get the output data
    // of the register
    std::vector<unsigned char> GetOutputData();

    // Function used to set the input data
    // of the register
    void SetInputData(std::vector<unsigned char> data);

    // Function used to get the register size
    unsigned char GetRegisterSize();

};

#endif // REGISTER_H

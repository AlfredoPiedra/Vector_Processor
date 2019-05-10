#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <vector>

class Register{

private:

    unsigned char register_size;
    std::vector<unsigned char> input_data;
    std::vector<unsigned char> output_data;

public:

    char signal_enable;

    // Constructors of the class
    Register();
    Register(unsigned char);

    // Function executed on reset
    void DoReset();

    // Function used to set the input data
    // of the register
    void ConfigureInput(std::vector<unsigned char> data);

    // Override the base class function
    void DoAction();

    // Function used to get the output data
    // of the register
    std::vector<unsigned char> GetOutput();

    // Function used to get the register size
    unsigned char GetRegisterSize();

};

#endif // REGISTER_H

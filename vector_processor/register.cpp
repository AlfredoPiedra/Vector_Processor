#include "register.h"

Register::Register(){

    // Set a default register width in bytes
    register_size = 4;

    // Allocate the memory for the buffers
    input_data.resize(register_size);
    output_data.resize(register_size);

    // Set an initial value for the enable signal of the register
    signal_enable = 1;

}

Register::Register(unsigned char length){

    // Check if the register size makes sense
    if(length > 0){

        // Assign the user specified register width
        register_size = length;

    // The register width specified does not makes sense
    // In this case assign a default value to make sure the system dont crash
    }else{

        // Assign a default register width
        register_size = 4;
    }

    // Set an initial value for the enable signal of the register
    signal_enable = 1;

    // Allocate the memory for the buffers
    input_data.resize(register_size);
    output_data.resize(register_size);
}

void Register::DoAction(){

    // Execute the action only if the enable signal is HIGH
    if(signal_enable){

        int byte;

        // On the clock posedge make the output
        // data equal to the input data
        for(byte = 0; byte < register_size; ++byte){

            output_data[byte] = input_data[byte];
        }
    }
}

void Register::DoReset(){

    int byte;

    // When reset signal is HIGH make all the
    // output data of the register equal to 0
    for(byte = 0; byte < register_size; ++byte){

        output_data[byte] = 0;
    }

}

void Register::ConfigureInput(std::vector<unsigned char> data){

    input_data = data;

}

void Register::SetEnable(unsigned char enable){

    signal_enable = enable;

}

std::vector<unsigned char> Register::GetOutput(){

    return output_data;
}

unsigned char Register::GetRegisterSize()
{
    return register_size;
}

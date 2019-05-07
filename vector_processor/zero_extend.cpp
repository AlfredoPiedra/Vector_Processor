#include "zero_extend.h"

ZeroExtend::ZeroExtend(){

    // Initialize all the class attributes
    extend_input = 0;

    extend_output = 0;

}

void ZeroExtend::ConfigureInput(unsigned char set_extend_input){

    extend_input = set_extend_input;
}

void ZeroExtend::DoAction(){

    extend_output = (unsigned int) extend_input;
}

unsigned int ZeroExtend::GetOutput(){

    return extend_output;
}

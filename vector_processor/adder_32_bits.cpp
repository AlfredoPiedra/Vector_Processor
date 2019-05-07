#include "adder_32_bits.h"

Adder::Adder()
{
    // Initialize the class attributes
    operand_a = 0;
    operand_b = 0;

    operation_result = 0;
}

void Adder::ConfigureInput(int in_operand_a,
                           int in_operand_b){

    operand_a = in_operand_a;

    operand_b = in_operand_b;

}

void Adder::DoAction(){


    operation_result = operand_a + operand_b;

}

int Adder::GetOutput(){

    return operation_result;
}

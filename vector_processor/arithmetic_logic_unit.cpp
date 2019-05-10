#include "arithmetic_logic_unit.h"

ArithmeticLogicUnit::ArithmeticLogicUnit()
{

    // Initialize all the class attributes
    flags = 0;
    operand_a = 0;
    operand_b = 0;
    operation_result = 0;
    alu_control = 0;

}

void ArithmeticLogicUnit::DoAction()
{

    switch(alu_control){

    case 0:
        operation_result = operand_a + operand_b;
        break;

    case 1:
        operation_result = operand_a - operand_b;
        break;

    case 2:
        operation_result = operand_a ^ operand_b;
        break;

    case 3:
        operation_result = operand_a & operand_b;
        break;

    case 4:
        operation_result = operand_a | operand_b;
        break;

    default:
        std::cout << "alu_control error" << std::endl;
        break;

    }

    // Clear all the bits
    flags = 0;

    // Detect overflow
    if(operation_result < operand_a
       && operation_result < operand_b){

        // If the operation is add or subtraction
        // the set the C bit to 1 because of overflow
        if(alu_control == 0
           || alu_control == 1){

            // Set the V and C flag to 1
            flags = 3;

        }else{

            // Set V = 1 and C = 0
            flags = 1;

        }
    }

    // Set the Z bit if the result is zero
    if(operation_result == 0){

        // Bitewise OR to set the third bit to 1
        flags = flags | 4;
    }

    // Set the N bit that is connected to
    // the most significant bit of the result

    // First shift the msb to the lsb position
    unsigned char msb = operation_result >> 7;

    // Set the result msb as the 4th bit
    msb = msb << 3;

    // Bitwise OR to set the fourth bit
    flags = flags | msb;

}

void ArithmeticLogicUnit::ConfigureInput(unsigned char the_operand_a,
                                         unsigned char the_operand_b,
                                         unsigned char control_signal)
{
    operand_a = the_operand_a;

    operand_b = the_operand_b;

    alu_control = control_signal;

}

unsigned char ArithmeticLogicUnit::GetOutput()
{
    return operation_result;
}


unsigned char ArithmeticLogicUnit::GetOutputFlags(){

    return flags;
}

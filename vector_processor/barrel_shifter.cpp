#include "barrel_shifter.h"

BarrelShifter::BarrelShifter()
{
    // Initialize all the class attributes
    shift_amount = 0;
    shift_operation = 0;
    shift_result = 0;

}

void BarrelShifter::ConfigureInput(unsigned char set_shift_operand,
                                   unsigned char set_shift_amount,
                                   unsigned char set_shift_operation){

    shift_amount = set_shift_amount;

    shift_operation = set_shift_operation;

    shift_operand = set_shift_operand;

}

void BarrelShifter::DoAction(){

    switch(shift_operation){

    case 0:
        // Right shift
        shift_result = shift_operand >> shift_amount;
        break;

    case 1:
        // Left shift
        shift_result = shift_operand << shift_amount;
        break;

    case 2:
        // Right circular shift
        shift_amount = shift_amount % 8;
        shift_result =  (shift_operand >> shift_amount) | (shift_operand << (8 - shift_amount));
        break;

    case 3:
        // Left circular shift
        shift_amount = shift_amount % 8;
        shift_result =  (shift_operand << shift_amount) | (shift_operand >> (8 - shift_amount));
        break;

    }
}

unsigned char BarrelShifter::GetOutput(){

    return shift_result;
}

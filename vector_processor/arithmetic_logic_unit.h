#ifndef ARITHMETICLOGICUNIT_H
#define ARITHMETICLOGICUNIT_H

#include <iostream>

class ArithmeticLogicUnit{

private:

    unsigned char operand_a;
    unsigned char operand_b;
    unsigned char alu_control;
    unsigned char operation_result;

    // Four bits defined as N,Z,C,V
    // being V the less significant bit
    unsigned char flags;

public:

    ArithmeticLogicUnit();

    void ConfigureInput(unsigned char the_operand_a,
                        unsigned char the_operand_b,
                        unsigned char control_signal);

    void DoAction();

    unsigned char GetOutput();

    unsigned char GetOutputFlags();

};

#endif // ARITHMETICLOGICUNIT_H

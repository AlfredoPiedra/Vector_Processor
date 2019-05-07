#ifndef BARRELSHIFTER_H
#define BARRELSHIFTER_H


class BarrelShifter
{

private:

    // ############### Inputs ##################
    unsigned char shift_amount;
    unsigned char shift_operation;
    unsigned char shift_operand;
    // ############### Inputs ##################

    // ############### Output ##################
    unsigned char shift_result;
    // ############### Output ##################

public:

    BarrelShifter();

    void ConfigureInput(unsigned char set_shift_operand,
                        unsigned char set_shift_amount,
                        unsigned char set_shift_operation);

    void DoAction();

    unsigned char GetOutput();

};

#endif // BARRELSHIFTER_H

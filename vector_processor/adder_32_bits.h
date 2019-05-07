#ifndef ADDER_H
#define ADDER_H


class Adder
{

private:

    // ############### Inputs ##################

    // Operands of the adder
    int operand_a;
    int operand_b;

    // ############### Inputs ##################

    // ############### Output ##################

    // add operation result
    int operation_result;

    // ############### Output ##################

public:

    // Constructor of the class
    Adder();

    // Function used to set the operands
    // of the 32 bits adder
    void ConfigureInput(int in_operand_a,
                        int in_operand_b);

    // Function used to
    // execute the sum
    void DoAction();

    // Function used to get
    // the sum of the operands
    int GetOutput();

};

#endif // ADDER_H

#ifndef ZEROEXTEND_H
#define ZEROEXTEND_H


class ZeroExtend
{

private:

     // ############### Input ##################
    unsigned char extend_input;
     // ############### Input ##################

     // ############### Output ##################
    unsigned int extend_output;
     // ############### Output ##################

public:

    ZeroExtend();

    void ConfigureInput(unsigned char set_extend_input);

    void DoAction();

    unsigned int GetOutput();
};

#endif // ZEROEXTEND_H

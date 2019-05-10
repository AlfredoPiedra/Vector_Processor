#ifndef MULTIPLEXER2X1_H
#define MULTIPLEXER2X1_H

template <class T>
class Multiplexer2x1{

private:

    // ############### Inputs ##################
    T mux_input_0;
    T mux_input_1;
    unsigned char mux_selection;
    // ############### Inputs ##################

    // ############### Output ##################
    T mux_output;
    // ############### Output ##################

public:

    Multiplexer2x1();

    void ConfigureInput(T input_0,
                        T input_1,
                        unsigned char selection);

    void DoAction();

    T GetOutput();

};

#endif // MULTIPLEXER2X1_H

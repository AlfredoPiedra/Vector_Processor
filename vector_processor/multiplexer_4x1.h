#ifndef MULTIPLEXER4X1_H
#define MULTIPLEXER4X1_H


template <class T>
class Multiplexer4x1
{

private:

    // ############### Inputs ##################

    T mux_input_00;
    T mux_input_01;
    T mux_input_10;
    T mux_input_11;

    T mux_selection;

    // ############### Inputs ##################

    // ############### Output ##################

    T mux_output;

    // ############### Output ##################

public:

    Multiplexer4x1();

    void ConfigureInput(T input_00,
                        T input_01,
                        T input_10,
                        T input_11,
                        T selection);

    void DoAction();

    T GetOutput();

};

#endif // MULTIPLEXER4X1_H

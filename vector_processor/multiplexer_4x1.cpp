#include "multiplexer_4x1.h"

template <class T>
Multiplexer4x1<T>::Multiplexer4x1(){

    // Initialize the class attributes
    mux_input_00 = T(0);
    mux_input_01 = T(0);
    mux_input_10 = T(0);
    mux_input_11 = T(0);

    mux_selection = 0;

    mux_output = T(0);

}

template <class T>
void Multiplexer4x1<T>::ConfigureInput(T input_00,
                                       T input_01,
                                       T input_10,
                                       T input_11,
                                       unsigned char selection){

    mux_input_00 = input_00;
    mux_input_01 = input_01;
    mux_input_10 = input_10;
    mux_input_11 = input_11;

    mux_selection = selection;

}

template <class T>
void Multiplexer4x1<T>::DoAction(){

    switch(mux_selection){

    case 0:
        mux_output = mux_input_00;
        break;

    case 1:
        mux_output = mux_input_01;
        break;

    case 2:
        mux_output = mux_input_10;
        break;

    case 3:
        mux_output = mux_input_11;
        break;

    default:
        mux_output = 0;
        break;
    }

}

template <class T>
T Multiplexer4x1<T>::GetOutput(){

    return mux_output;
}

// Explicitly instantiate the templates class
// to ensure that the compiler found and
// compile the needed classes
template class Multiplexer4x1<unsigned int>;
template class Multiplexer4x1<unsigned char>;

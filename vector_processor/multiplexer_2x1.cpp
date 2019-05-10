#include "multiplexer_2x1.h"

template <class T>
Multiplexer2x1<T>::Multiplexer2x1(){

    // Initialize the class attributes
    mux_input_0 = T(0);
    mux_input_1 = T(0);

    mux_selection = 0;

    mux_output = T(0);

}

template <class T>
void Multiplexer2x1<T>::ConfigureInput(T input_0,
                                       T input_1,
                                       unsigned char selection){

    mux_input_0 = input_0;
    mux_input_1 = input_1;

    mux_selection = selection;

}

template <class T>
void Multiplexer2x1<T>::DoAction(){

    switch(mux_selection){

    case 0:
        mux_output = mux_input_0;
        break;

    case 1:
        mux_output = mux_input_1;
        break;

    default:
        mux_output = 0;
        break;
    }

}

template <class T>
T Multiplexer2x1<T>::GetOutput(){

    return mux_output;
}

// Explicitly instantiate the templates class
// to ensure that the compiler found and
// compile the needed classes
template class Multiplexer2x1<unsigned int>;
template class Multiplexer2x1<unsigned char>;



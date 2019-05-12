#include <iostream>

using namespace std;

#include "vectorial_processor.h"

/*template <typename T>
void showbits(T x) {

    for(int i = (sizeof(T) * 8) - 1; i >= 0; i--) {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}*/

int main(){

    VectorialProcessor asip;

    asip.CompleteProcessing();

    asip.ReadAllMemory();

    return 0;
}


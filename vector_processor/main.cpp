#include <iostream>

using namespace std;

#include "register_file.h"

void showbits(unsigned char x) {

    for(int i = (sizeof(char) * 8) - 1; i >= 0; i--) {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int main()
{

    /*RegisterFile rf(8,4);

    std::vector<unsigned char> vec{ 1, 4, 5, 22, 10 };

    rf.WriteRegister(0,vec);

    std::vector<unsigned char> dat = rf.ReadRegister(0);

    for(unsigned int i = 0; i < dat.size(); ++i){

        cout << (int) dat[i] << " ";
    }*/

    cout << sizeof(bool) << endl;

    return 0;
}


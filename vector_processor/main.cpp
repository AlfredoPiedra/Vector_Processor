#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgcodecs/imgcodecs_c.h>

using namespace std;

#include "memory_bank.h"
#include "barrel_shifter.h"

template <typename T>
void showbits(T x) {

    for(int i = (sizeof(T) * 8) - 1; i >= 0; i--) {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int main()
{

    BarrelShifter bs;

    unsigned char c = 7;

    bs.ConfigureInput(7,31,3);

    showbits<unsigned char>(c);

    //unsigned char value = 10;

    //value = value % 8;

    //c = (c >> value) | (c << (8 - value));

    bs.DoAction();

    c = bs.GetOutput();

    showbits<unsigned char>(c);


    int a = c;

    cout << a << endl;

    showbits<int>(a);

   /*char c = 1;

    int b = 0;

    b = c;

    showbits<int>(b);

    b = b << 8;

    showbits<int>(b);

    b = b | c;

    showbits<int>(b);

    b = b << 8;

    showbits<int>(b);

    b = b | c;

    showbits<int>(b);

    b = b << 8;

    showbits<int>(b);

    b = b | c;

    showbits<int>(b);

    cout << b << endl;*/

    // Multiplexer4x1<int> m4;

    // m4.ConfigureInput(1,2,3,4,1);

    /*cv::Mat_<unsigned char> Imagen;

    Imagen = cv::imread("/home/alfredo/Descargas/m2.png",cv::IMREAD_GRAYSCALE);

    if(!Imagen.data) throw std::runtime_error("[ReadRegister]: register does not exist");

    cv::imwrite("/home/alfredo/Descargas/m3.png",Imagen);*/

    /*int i,j;

    for(i = 0; i < Imagen.rows; ++i){

        for(j = 0; j < Imagen.cols; ++j){


            cout << (int) Imagen(i,j) << " ";

        }

        cout << endl;

    }*/

    //cv::namedWindow("Original-1er estrategia", cv::WINDOW_NORMAL);
    //cv::imshow( "Ruta-1er estrategia", Imagen );

    //cv::waitKey(0);

    /*RegisterFile rf(8,4);

    std::vector<unsigned char> vec{ 1, 4, 5, 22, 10 };

    rf.WriteRegister(0,vec);

    std::vector<unsigned char> dat = rf.ReadRegister(0);

    for(unsigned int i = 0; i < dat.size(); ++i){

        cout << (int) dat[i] << " ";
    }*/

    //InstructionMemory imem;

    //imem.GetOutput();

    return 0;
}


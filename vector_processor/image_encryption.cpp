/*#include "image_encryption.h"

ImageEncryption::ImageEncryption(){

}

void ImageEncryption::XOREncryption(std::__cxx11::string input_image_name,
                                    std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/codificacionXORHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

   cv::Mat_<unsigned char> original =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
   cv::Mat_<unsigned char> encrypt =  cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

   cv::imshow( "Original window", original );
   cv::imshow("Encrypted window", encrypt);

   cv::waitKey(0);

}

void ImageEncryption::XORDecryption(std::__cxx11::string input_image_name,
                                    std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/codificacionXORHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> encrypt =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> decrypt =   cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Decrypted window", decrypt );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}

void ImageEncryption::CircularShiftEncryption(std::__cxx11::string input_image_name,
                                              std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/codificacionShiftHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> original =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> encrypt =  cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Original window", original );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}

void ImageEncryption::CircularShiftDecryption(std::__cxx11::string input_image_name,
                                              std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/decodificacionShiftHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> encrypt =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> decrypt =   cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Decrypted window", decrypt );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}

void ImageEncryption::AddEncryption(std::__cxx11::string input_image_name,
                                    std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/codificacionSumaHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> original =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> encrypt =  cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Original window", original );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}

void ImageEncryption::AddDecryption(std::__cxx11::string input_image_name,
                                    std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/decodificacionSumaHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> encrypt =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> decrypt =   cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Decrypted window", decrypt );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}


void ImageEncryption::CustomEncryption(std::__cxx11::string input_image_name,
                                       std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/codificacionPropioHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> original =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> encrypt =  cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Original window", original );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}

void ImageEncryption::CustomDecryption(std::__cxx11::string input_image_name,
                                       std::__cxx11::string output_image_name){

    VectorialProcessor processor;

    processor.LoadProgram("/home/alfredo/VectorProcessor/source_code/bin/decodificacionPropioHex.txt");

    processor.LoadImage(input_image_name);

    processor.CompleteProcessing();

    processor.ReadAllMemory(output_image_name);

    cv::Mat_<unsigned char> encrypt =  cv::imread(input_image_name,cv::IMREAD_GRAYSCALE);
    cv::Mat_<unsigned char> decrypt =   cv::imread(output_image_name,cv::IMREAD_GRAYSCALE);

    cv::imshow( "Decrypted window", decrypt );
    cv::imshow("Encrypted window", encrypt);

    cv::waitKey(0);
}*/

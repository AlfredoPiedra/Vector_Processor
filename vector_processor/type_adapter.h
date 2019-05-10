#ifndef TYPE_ADAPTER_H
#define TYPE_ADAPTER_H

#include <iostream>
#include <vector>
#include <stdexcept>

namespace adapter{

    unsigned int BytesToInteger(std::vector<unsigned char> bytes);

    std::vector<unsigned char> IntegerToBytes(unsigned int word);


} //adapter


#endif // TYPE_ADAPTER_H


#include "type_adapter.h"

unsigned int adapter::BytesToInteger(std::vector<unsigned char> bytes){

    unsigned int compact = 0;

    if(bytes.size() != 4){

        throw std::runtime_error("[BytesToInt]: invalid bytes array size");
    }

    compact = bytes[0];

    compact = ( compact << 8 ) | bytes[1];

    compact = ( compact << 8 ) | bytes[2];

    compact = ( compact << 8 ) | bytes[3];

    return compact;
}

std::vector<unsigned char> adapter::IntegerToBytes(unsigned int word){

    std::vector<unsigned char> bytes;

    bytes.resize(4);

    bytes[0] = word >> 24;
    bytes[1] = word >> 16;
    bytes[2] = word >> 8;
    bytes[3] = word;

    return bytes;
}

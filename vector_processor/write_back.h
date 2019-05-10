#ifndef WRITEBACK_H
#define WRITEBACK_H

#include <vector>
#include "multiplexer_2x1.h"

#include "type_adapter.h"

class WriteBack{

private:

    // ############### Input ##################
    std::vector<unsigned char> writeback_input;
    // ############### Input ##################

    // ############### Output ##################
    std::vector<unsigned char> writeback_output;
    // ############### Output ##################

    Multiplexer2x1<unsigned int> *vector_d_msb_source;
    Multiplexer2x1<unsigned int> *vector_d_lsb_source;
    Multiplexer2x1<unsigned int> *register_d_source;
    Multiplexer2x1<unsigned int> *read_data_source;

    void OrganizeOutput();

public:

    WriteBack();

    void ConfigureInput(std::vector<unsigned char> set_writeback_input);

    void DoAction();

    std::vector<unsigned char> GetOutput();
};

#endif // WRITEBACK_H

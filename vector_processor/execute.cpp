#include "execute.h"

Execute::Execute(){

    execute_input.reserve(1);
    execute_input.push_back(0);

    execute_memory = new Register(28);

    format_i_adder = new Adder();
    format_m_adder = new Adder();
    address_adder  = new Adder();

    operand_b_source  = new Multiplexer2x1<unsigned int>();
    register_d_result = new Multiplexer4x1<unsigned int>();
    address_source    = new Multiplexer4x1<unsigned int>();

    alus.reserve(8);
    shifters.reserve(8);
    vector_result_source.reserve(8);
    vector_operand_source.reserve(8);

    int lane;

    for(lane = 0; lane < 8; ++lane){

        alus.push_back(ArithmeticLogicUnit());
        shifters.push_back(BarrelShifter());
        vector_operand_source.push_back(Multiplexer2x1<unsigned char>());
        vector_result_source.push_back(Multiplexer4x1<unsigned char>());
    }
}

void Execute::ConfigureInput(std::vector<unsigned char> set_execute_input){

    execute_input = set_execute_input;
}

void Execute::OrganizeOutput(){

    std::vector<unsigned char> execute_output;
    std::vector<unsigned char> register_d_output = adapter::IntegerToBytes(register_d_result->GetOutput());
    std::vector<unsigned char> address_bytes = adapter::IntegerToBytes(address_source->GetOutput());
    std::vector<unsigned char> address_plus_bytes = adapter::IntegerToBytes(address_adder->GetOutput());

    execute_output.resize(28);

    execute_output[0] = vector_result_source[0].GetOutput(); // Vd MSB
    execute_output[1] = vector_result_source[1].GetOutput();
    execute_output[2] = vector_result_source[2].GetOutput();
    execute_output[3] = vector_result_source[3].GetOutput();
    execute_output[4] = vector_result_source[4].GetOutput();
    execute_output[5] = vector_result_source[5].GetOutput();
    execute_output[6] = vector_result_source[6].GetOutput();
    execute_output[7] = vector_result_source[7].GetOutput();

    execute_output[8] = register_d_output[0]; // Rd MSB
    execute_output[9] = register_d_output[1];
    execute_output[10] = register_d_output[2];
    execute_output[11] = register_d_output[3];

    execute_output[12] = address_bytes[0]; // Address MSB
    execute_output[13] = address_bytes[1];
    execute_output[14] = address_bytes[2];
    execute_output[15] = address_bytes[3];

    execute_output[16] = address_plus_bytes[0]; // Address plus 4 MSB
    execute_output[17] = address_plus_bytes[1];
    execute_output[18] = address_plus_bytes[2];
    execute_output[19] = address_plus_bytes[3];

    execute_output[20] = execute_input[26]; // memory write
    execute_output[21] = execute_input[27]; // write all
    execute_output[22] = execute_input[36]; // Vd
    execute_output[23] = execute_input[37]; // Rd
    execute_output[24] = execute_input[28]; // register write source
    execute_output[25] = execute_input[29]; // vector write source
    execute_output[26] = execute_input[24]; // register write
    execute_output[27] = execute_input[25]; // vector write


    execute_memory->ConfigureInput(execute_output);
    execute_memory->DoAction();
}

void Execute::DoAction(){

    std::vector<unsigned char> four_bytes;
    four_bytes.resize(4);

    four_bytes[0] = execute_input[0];
    four_bytes[1] = execute_input[1];
    four_bytes[2] = execute_input[2];
    four_bytes[3] = execute_input[3];

    unsigned int register_a_output = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[4];
    four_bytes[1] = execute_input[5];
    four_bytes[2] = execute_input[6];
    four_bytes[3] = execute_input[7];

    unsigned int register_b_output = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[39];
    four_bytes[1] = execute_input[40];
    four_bytes[2] = execute_input[41];
    four_bytes[3] = execute_input[42];

    unsigned int m_immediate = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[43];
    four_bytes[1] = execute_input[44];
    four_bytes[2] = execute_input[45];
    four_bytes[3] = execute_input[46];

    unsigned int i_immediate = adapter::BytesToInteger(four_bytes);


    format_m_adder->ConfigureInput(register_b_output,
                                   m_immediate);

    format_m_adder->DoAction();

    operand_b_source->ConfigureInput(register_b_output,
                                     i_immediate,
                                     execute_input[31]); // immediate source

    operand_b_source->DoAction();


    format_i_adder->ConfigureInput(register_a_output,
                                   operand_b_source->GetOutput());

    format_i_adder->DoAction();

    address_source->ConfigureInput(format_m_adder->GetOutput(),
                                   register_b_output,
                                   operand_b_source->GetOutput(),
                                   0,  // unused multiplexer input
                                   execute_input[32]); // address source

    address_source->DoAction();

    // Compute address plus 4
    address_adder->ConfigureInput(address_source->GetOutput(),
                                  4);

    address_adder->DoAction();

    register_d_result->ConfigureInput(register_a_output,
                                      format_i_adder->GetOutput(),
                                      format_m_adder->GetOutput(),
                                      operand_b_source->GetOutput(),
                                      execute_input[33]); // register d source

    register_d_result->DoAction();

    unsigned char unit;

    for(unit = 0; unit < 8; ++unit){

        vector_operand_source[unit].ConfigureInput(execute_input[16 + unit],   // Vb byte
                                                   execute_input[38],          // f_immediate
                                                   execute_input[31]);         // immediate source

        vector_operand_source[unit].DoAction();

        alus[unit].ConfigureInput(execute_input[8 + unit],                     // Va byte
                                  vector_operand_source[unit].GetOutput(),     // vector operand b
                                  execute_input[34]);                          // alu control

        alus[unit].DoAction();

        shifters[unit].ConfigureInput(execute_input[8 + unit],                 // Va byte
                                      vector_operand_source[unit].GetOutput(), // vector operand b
                                      execute_input[35]);                      // shifter control

        shifters[unit].DoAction();

        vector_result_source[unit].ConfigureInput(alus[unit].GetOutput(),       // alu result
                                                  shifters[unit].GetOutput(),   // shifter result
                                                  vector_operand_source[unit].GetOutput(), // vector operand b
                                                  0, // unused multiplexer input
                                                  execute_input[30]);           // vector result

        vector_result_source[unit].DoAction();
    }

    OrganizeOutput();
}


std::vector<unsigned char> Execute::GetOutput(){

    return execute_memory->GetOutput();
}

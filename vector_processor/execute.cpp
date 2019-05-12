#include "execute.h"

Execute::Execute(){

    execute_input.reserve(1);
    execute_input.push_back(0);

    execute_memory = new Register(28);

    format_i_adder = new Adder();
    format_m_adder = new Adder();
    address_adder  = new Adder();

    operand_b_source  = new Multiplexer2x1<unsigned int>();
    register_d_dir = new Multiplexer2x1<unsigned char>();
    register_d_result = new Multiplexer4x1<unsigned int>();
    address_source    = new Multiplexer4x1<unsigned int>();
    register_a_forward_source = new Multiplexer4x1<unsigned int>();
    register_b_forward_source = new Multiplexer4x1<unsigned int>();

    alus.reserve(8);
    shifters.reserve(8);
    vector_result_source.reserve(8);
    vector_operand_source.reserve(8);
    vector_a_forward_source.reserve(8);
    vector_b_forward_source.reserve(8);

    register_a_forward = 2;
    register_b_forward = 2;
    vector_a_forward = 2;
    vector_b_forward = 2;

    register_a_output = 0;
    register_b_output = 0;
    i_immediate = 0;
    m_immediate = 0;

    memory_forward_register_data = 0;
    writeback_forward_register_data = 0;

    memory_forward_vector_data.resize(8);
    writeback_forward_vector_data.resize(8);

    execute_flags.resize(31);

    int lane;

    for(lane = 0; lane < 8; ++lane){

        alus.push_back(ArithmeticLogicUnit());
        shifters.push_back(BarrelShifter());
        vector_operand_source.push_back(Multiplexer2x1<unsigned char>());
        vector_result_source.push_back(Multiplexer4x1<unsigned char>());
        vector_a_forward_source.push_back(Multiplexer4x1<unsigned char>());
        vector_b_forward_source.push_back(Multiplexer4x1<unsigned char>());
    }
}

void Execute::ConfigureInput(std::vector<unsigned char> set_execute_input){

    execute_input = set_execute_input;
}

void Execute::ConfigureForwardInput(unsigned char set_register_a_forward,
                                    unsigned char set_register_b_forward,
                                    unsigned char set_vector_a_forward,
                                    unsigned char set_vector_b_forward,
                                    unsigned int set_memory_forward_register_data,
                                    unsigned int set_writeback_forward_register_data,
                                    std::vector<unsigned char> set_memory_forward_vector_data,
                                    std::vector<unsigned char> set_writeback_forward_vector_data){

    register_a_forward = set_register_a_forward;
    register_b_forward = set_register_b_forward;

    vector_a_forward = set_vector_a_forward;
    vector_b_forward = set_vector_b_forward;

    memory_forward_register_data = set_memory_forward_register_data;
    writeback_forward_register_data = set_writeback_forward_register_data;

    memory_forward_vector_data = set_memory_forward_vector_data;
    writeback_forward_vector_data = set_writeback_forward_vector_data;
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

    execute_output[20] = execute_flags[0]; // memory write
    execute_output[21] = execute_flags[1]; // write all
    execute_output[22] = execute_flags[2]; // Vd
    execute_output[23] = register_d_dir->GetOutput(); // Rd
    execute_output[24] = execute_flags[4]; // register write source
    execute_output[25] = execute_flags[5]; // vector write source
    execute_output[26] = execute_flags[6]; // register write
    execute_output[27] = execute_flags[7]; // vector write

    execute_memory->ConfigureInput(execute_output);
    execute_memory->DoAction();
}

void Execute::DoNegativeEdgeAction(){

    std::vector<unsigned char> four_bytes;
    four_bytes.resize(4);

    four_bytes[0] = execute_input[0];
    four_bytes[1] = execute_input[1];
    four_bytes[2] = execute_input[2];
    four_bytes[3] = execute_input[3];

    register_a_output = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[4];
    four_bytes[1] = execute_input[5];
    four_bytes[2] = execute_input[6];
    four_bytes[3] = execute_input[7];

    register_b_output = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[39];
    four_bytes[1] = execute_input[40];
    four_bytes[2] = execute_input[41];
    four_bytes[3] = execute_input[42];

    m_immediate = adapter::BytesToInteger(four_bytes);

    four_bytes[0] = execute_input[43];
    four_bytes[1] = execute_input[44];
    four_bytes[2] = execute_input[45];
    four_bytes[3] = execute_input[46];

    i_immediate = adapter::BytesToInteger(four_bytes);

    execute_flags[0] = execute_input[26]; // memory write
    execute_flags[1] = execute_input[27]; // write all
    execute_flags[2] = execute_input[36]; // Vd
    execute_flags[4] = execute_input[28]; // register write source
    execute_flags[5] = execute_input[29]; // vector write source
    execute_flags[6] = execute_input[24]; // register write
    execute_flags[7] = execute_input[25]; // vector write

    execute_flags[8] = execute_input[31]; // immediate_source
    execute_flags[9] = execute_input[32]; // address source
    execute_flags[10] = execute_input[33];// register d source
    execute_flags[11] = execute_input[38];// f immediate
    execute_flags[12] = execute_input[34];// alu control
    execute_flags[13] = execute_input[35];// shifter control
    execute_flags[14] = execute_input[30];// vector result

    execute_flags[15] = execute_input[8]; // Va MSB
    execute_flags[16] = execute_input[9];
    execute_flags[17] = execute_input[10];
    execute_flags[18] = execute_input[11];
    execute_flags[19] = execute_input[12];
    execute_flags[20] = execute_input[13];
    execute_flags[21] = execute_input[14];
    execute_flags[22] = execute_input[15];

    execute_flags[23] = execute_input[16]; // Vb MSB
    execute_flags[24] = execute_input[17];
    execute_flags[25] = execute_input[18];
    execute_flags[26] = execute_input[19];
    execute_flags[27] = execute_input[20];
    execute_flags[28] = execute_input[21];
    execute_flags[29] = execute_input[22];
    execute_flags[30] = execute_input[23];

    register_d_dir->ConfigureInput(execute_input[37], // register d
                                   execute_input[48], // register b
                                   execute_input[27]);// write all
    register_d_dir->DoAction();
}

void Execute::DoPositiveEdgeAction(){


    register_a_forward_source->ConfigureInput(memory_forward_register_data,
                                              writeback_forward_register_data,
                                              register_a_output,
                                              0, // unused multiplexer input
                                              register_a_forward);

    register_a_forward_source->DoAction();

    register_b_forward_source->ConfigureInput(memory_forward_register_data,
                                              writeback_forward_register_data,
                                              register_b_output,
                                              0, // unused multiplexer input
                                              register_b_forward);

    register_b_forward_source->DoAction();

    format_m_adder->ConfigureInput(register_b_forward_source->GetOutput(),
                                   m_immediate);

    format_m_adder->DoAction();

    operand_b_source->ConfigureInput(register_b_forward_source->GetOutput(),
                                     i_immediate,
                                     execute_flags[8]); // immediate source

    operand_b_source->DoAction();


    format_i_adder->ConfigureInput(register_a_forward_source->GetOutput(),
                                   operand_b_source->GetOutput());

    format_i_adder->DoAction();

    address_source->ConfigureInput(0,               // unused multiplexer input
                                   format_m_adder->GetOutput(),
                                   register_b_forward_source->GetOutput(),
                                   operand_b_source->GetOutput(),
                                   execute_flags[9]); // address source

    address_source->DoAction();

    // Compute address plus 4
    address_adder->ConfigureInput(address_source->GetOutput(),
                                  4);

    address_adder->DoAction();

    register_d_result->ConfigureInput(register_a_forward_source->GetOutput(),
                                      format_i_adder->GetOutput(),
                                      format_m_adder->GetOutput(),
                                      operand_b_source->GetOutput(),
                                      execute_flags[10]); // register d source

    register_d_result->DoAction();

    unsigned char unit;

    for(unit = 0; unit < 8; ++unit){


        vector_a_forward_source[unit].ConfigureInput(memory_forward_vector_data[unit],
                                                     writeback_forward_vector_data[unit],
                                                     execute_flags[15 + unit],  // Va byte
                                                     0,                         // unused multiplexer input
                                                     vector_a_forward);
        vector_a_forward_source[unit].DoAction();

        vector_b_forward_source[unit].ConfigureInput(memory_forward_vector_data[unit],
                                                     writeback_forward_vector_data[unit],
                                                     execute_flags[23 + unit],  // Vb byte
                                                     0,                         // unused multiplexer input
                                                     vector_b_forward);
        vector_b_forward_source[unit].DoAction();

        vector_operand_source[unit].ConfigureInput(vector_b_forward_source[unit].GetOutput(),   // forward data
                                                   execute_flags[11],          // f_immediate
                                                   execute_flags[8]);         // immediate source

        vector_operand_source[unit].DoAction();

        alus[unit].ConfigureInput(vector_a_forward_source[unit].GetOutput(),   // forward data
                                  vector_operand_source[unit].GetOutput(),     // vector operand b
                                  execute_flags[12]);                          // alu control

        alus[unit].DoAction();

        shifters[unit].ConfigureInput(vector_a_forward_source[unit].GetOutput(),// forward_data
                                      vector_operand_source[unit].GetOutput(),  // vector operand b
                                      execute_flags[13]);                       // shifter control

        shifters[unit].DoAction();

        vector_result_source[unit].ConfigureInput(alus[unit].GetOutput(),       // alu result
                                                  shifters[unit].GetOutput(),   // shifter result
                                                  vector_operand_source[unit].GetOutput(), // vector operand b
                                                  0,                            // unused multiplexer input
                                                  execute_flags[14]);           // vector result

        vector_result_source[unit].DoAction();
    }

    OrganizeOutput();
}

void Execute::DoAction(unsigned char clock){

    // Write in the registers on posedge
    if(clock){

        DoPositiveEdgeAction();

    // Read the registers values on negedge
    }else{

        DoNegativeEdgeAction();

    }
}

std::vector<unsigned char> Execute::GetHazardUnitInput(){

    std::vector<unsigned char> hazard_input;
    hazard_input.resize(8);

    hazard_input[0] = register_d_dir->GetOutput(); // Register d
    hazard_input[1] = execute_input[47]; // Register a
    hazard_input[2] = execute_input[48]; // Register b
    hazard_input[3] = execute_input[36]; // Vector d

    hazard_input[4] = execute_input[49]; // Vector a
    hazard_input[5] = execute_input[50]; // Vector b
    hazard_input[6] = execute_input[28]; // register write src
    hazard_input[7] = execute_input[29]; // vector write src

    return hazard_input;
}

std::vector<unsigned char> Execute::GetOutput(){

    return execute_memory->GetOutput();
}

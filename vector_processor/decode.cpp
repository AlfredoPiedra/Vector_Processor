#include "decode.h"

Decode::Decode(){

    // Instance a register file with 8 scalar registers, 4 bytes(32 bits) each
    scalar_registers = new RegisterFile(8,4);

    // Instance a register file with 16 vector registers, 8 bytes (64 bits) each
    vector_registers = new RegisterFile(16,8);

    decode_execute = new Register(51);

    control_unit = new ControlUnit();

    operand_a_source = new Multiplexer2x1<unsigned char>();

    vector_write_enable = 0;
    vector_write_register = 0;

    scalar_write_enable = 0;
    scalar_write_register = 0;

    flush_execute = 0;

    decode_instruction.resize(4);
    scalar_write_data.resize(4);
    vector_write_data.resize(8);
}

void Decode::ConfigureInput(std::vector<unsigned char> set_decode_instruction){

    decode_instruction = set_decode_instruction;
}

void Decode::ConfigureWrite(unsigned char set_vector_write_enable,
                            unsigned char set_vector_d,
                            unsigned char set_register_write_enable,
                            unsigned char set_register_d,
                            std::vector<unsigned char> set_vector_write_data,
                            std::vector<unsigned char> set_register_write_data){

    vector_write_enable = set_vector_write_enable;
    vector_write_register = set_vector_d;

    scalar_write_enable = set_register_write_enable;
    scalar_write_register = set_register_d;

    vector_write_data = set_vector_write_data;
    scalar_write_data = set_register_write_data;
}

void Decode::OrganizeOutput(unsigned char vector_d,
                            unsigned char register_d,
                            unsigned char register_a,
                            unsigned char register_b,
                            unsigned char vector_a,
                            unsigned char vector_b,
                            unsigned char f_immediate,
                            unsigned int m_immediate,
                            unsigned int i_immediate){

    std::vector<unsigned char> decode_output;
    std::vector<unsigned char> register_a_output = scalar_registers->GetOutputDataA();
    std::vector<unsigned char> register_b_output = scalar_registers->GetOutputDataB();
    std::vector<unsigned char> vector_a_output = vector_registers->GetOutputDataA();
    std::vector<unsigned char> vector_b_output = vector_registers->GetOutputDataB();
    std::vector<unsigned char> control_bits = control_unit->GetOutput();
    std::vector<unsigned char> m_immediate_bytes = adapter::IntegerToBytes(m_immediate);
    std::vector<unsigned char> i_immediate_bytes = adapter::IntegerToBytes(i_immediate);

    decode_output.resize(51);

    decode_output[0] = register_a_output[0]; // Ra MSB
    decode_output[1] = register_a_output[1];
    decode_output[2] = register_a_output[2];
    decode_output[3] = register_a_output[3];

    decode_output[4] = register_b_output[0]; // Rb MSB
    decode_output[5] = register_b_output[1];
    decode_output[6] = register_b_output[2];
    decode_output[7] = register_b_output[3];

    decode_output[8]  = vector_a_output[0]; // Va MSB
    decode_output[9]  = vector_a_output[1];
    decode_output[10] = vector_a_output[2];
    decode_output[11] = vector_a_output[3];
    decode_output[12] = vector_a_output[4];
    decode_output[13] = vector_a_output[5];
    decode_output[14] = vector_a_output[6];
    decode_output[15] = vector_a_output[7];

    decode_output[16] = vector_b_output[0]; // Vb MSB
    decode_output[17] = vector_b_output[1];
    decode_output[18] = vector_b_output[2];
    decode_output[19] = vector_b_output[3];
    decode_output[20] = vector_b_output[4];
    decode_output[21] = vector_b_output[5];
    decode_output[22] = vector_b_output[6];
    decode_output[23] = vector_b_output[7];

    decode_output[24] = control_bits[0];  // register write
    decode_output[25] = control_bits[1];  // vector write
    decode_output[26] = control_bits[2];  // memory write
    decode_output[27] = control_bits[3];  // write all
    decode_output[28] = control_bits[4];  // register write source
    decode_output[29] = control_bits[5];  // vector write source
    decode_output[30] = control_bits[6];  // vector result
    decode_output[31] = control_bits[7];  // immediate source
    decode_output[32] = control_bits[8];  // address source
    decode_output[33] = control_bits[9];  // register d source
    decode_output[34] = control_bits[10]; // alu control
    decode_output[35] = control_bits[11]; // shifter control

    decode_output[36] = vector_d;   // Vd
    decode_output[37] = register_d; // Rd
    decode_output[38] = f_immediate;

    decode_output[39] = m_immediate_bytes[0]; // MSB
    decode_output[40] = m_immediate_bytes[1];
    decode_output[41] = m_immediate_bytes[2];
    decode_output[42] = m_immediate_bytes[3];

    decode_output[43] = i_immediate_bytes[0]; // MSB
    decode_output[44] = i_immediate_bytes[1];
    decode_output[45] = i_immediate_bytes[2];
    decode_output[46] = i_immediate_bytes[3];

    decode_output[47] = register_a;
    decode_output[48] = register_b;

    decode_output[49] = vector_a;
    decode_output[50] = vector_b;

    decode_execute->ConfigureInput(decode_output);    
}

void Decode::DoNegativeEdgeAction(){

    // Get the operation code that is in the same place for all the formats
    unsigned char opcode = decode_instruction[0] >> 4;

    //std::cout << "Opcode: " << (int) decode_instruction[0] << std::endl;

    // Get the 4th bit encoded in the instruction
    unsigned char i_or_p_bit = (decode_instruction[0] & 8) >> 3;

    //std::cout << "I/P: " << (int) i_or_p_bit << std::endl;

    // For format I get the operands encoded in the instruction

    // Get only the last 3 bits incluiding LSB, for the operand register b;
    unsigned char register_b = decode_instruction[3] & 7;

    //std::cout << "Register_B: " << (int) register_b << std::endl;

    // Get only the first 3 bits incluiding MSB, for the operand register a
    unsigned char register_a = decode_instruction[1] >> 5;

    //std::cout << "Register_A: " << (int) register_a << std::endl;

    // Get only the last 3 bits incluiding LSB, for the operand register d
    unsigned char register_d = decode_instruction[0] & 7;

    //std::cout << "Register_D: " << (int) register_d << std::endl;

    // Get the 21 bits immediate value encoded in the instruction
    unsigned int i_immediate = decode_instruction[1] & 31;
    i_immediate = (i_immediate << 8) | decode_instruction[2];
    i_immediate = (i_immediate << 8) | decode_instruction[3];

    //std::cout << "Immediate_I: " << (int) i_immediate << std::endl;
    // For the format M get the operands encoded in the instruction
    // register_b = source register encoded in the LSB
    unsigned char vector_d = (( decode_instruction[0] & 7 ) << 1 ) | (decode_instruction[1] >> 7);

    //std::cout << "Vector_D: " << (int) vector_d << std::endl;

    // Get the 20 bits immediate value encoded in the instruction
    unsigned int m_immediate = decode_instruction[1] & 127;
    m_immediate = (m_immediate << 8) | decode_instruction[2];
    m_immediate = (m_immediate << 8) | decode_instruction[3];
    m_immediate = m_immediate >> 3;

    //std::cout << "Immediate_M: " << (int) m_immediate << std::endl;

    // For the format F get the operands encoded in the instruction
    // Get the 4 bits in the middle of the byte, for the vector register a
    unsigned char vector_a = decode_instruction[1] << 1;
    vector_a = vector_a >> 4;

    //std::cout << "Vector_A: " << (int) vector_a << std::endl;

    // Get only the last 4 bits incluiding LSB, for the vector register b
    unsigned char vector_b = decode_instruction[3] & 15;

    //std::cout << "Vector_B: " << (int) vector_b << std::endl;

    // Get the 8 bits immediate value encoded in the instruction
    unsigned char f_immediate = decode_instruction[3];

    //std::cout << "Immediate_F: " << (int) f_immediate << std::endl;

    control_unit->ConfigureInput(opcode,i_or_p_bit);
    control_unit->DoAction();

    std::vector<unsigned char> control_output = control_unit->GetOutput();

    operand_a_source->ConfigureInput(register_a, register_d, control_output[2]);
    operand_a_source->DoAction();

    scalar_registers->ConfigureReadInput(operand_a_source->GetOutput(),
                                         register_b);
    scalar_registers->DoReadAction();

    vector_registers->ConfigureReadInput(vector_a,
                                         vector_b);

    vector_registers->DoReadAction();

    OrganizeOutput(vector_d,
                   register_d,
                   register_a,
                   register_b,
                   vector_a,
                   vector_b,
                   f_immediate,
                   m_immediate,
                   i_immediate);
}

void Decode::DoPositiveEdgeAction(){

    scalar_registers->ConfigureWriteInput(scalar_write_enable,
                                          scalar_write_register,
                                          scalar_write_data);
    scalar_registers->DoWriteAction();

    vector_registers->ConfigureWriteInput(vector_write_enable,
                                          vector_write_register,
                                          vector_write_data);
    vector_registers->DoWriteAction();

    if(!flush_execute){

        decode_execute->DoAction();

    }else{

        //std::cout << "Flushing pipe ..." << std::endl;
        decode_execute->DoReset();
    }
}

void Decode::DoAction(unsigned char clock){

    // Write in the registers on posedge
    if(clock){

        DoPositiveEdgeAction();

    // Read the registers values on negedge
    }else{

        DoNegativeEdgeAction();
    }
}

std::vector<unsigned char> Decode::GetHazardUnitInput(){

    // For the format F get the operands encoded in the instruction
    // Get the 4 bits in the middle of the byte, for the vector register a
    unsigned char vector_a = decode_instruction[1] << 1;
    vector_a = vector_a >> 4;

    // Get only the last 4 bits incluiding LSB, for the vector register b
    unsigned char vector_b = decode_instruction[3] & 15;

    // Get only the last 3 bits incluiding LSB, for the operand register b;
    unsigned char register_b = decode_instruction[3] & 7;

    // Get only the first 3 bits incluiding MSB, for the operand register a
    unsigned char register_a = decode_instruction[1] >> 5;

    std::vector<unsigned char> hazard_input;
    hazard_input.resize(4);

    hazard_input[0] = register_a;
    hazard_input[1] = register_b;
    hazard_input[2] = vector_a;
    hazard_input[3] = vector_b;

    return hazard_input;
}

void Decode::DoFlush(unsigned char stall){

    flush_execute = !stall;
}

std::vector<unsigned char> Decode::GetOutput(){

    return decode_execute->GetOutput();
}

void Decode::PrintContent(){

    std::cout << "############## Escalares ######################" << std::endl;

    scalar_registers->PrintContent();

    std::cout << "############## Vectoriales ######################" << std::endl;

    vector_registers->PrintContent();
}

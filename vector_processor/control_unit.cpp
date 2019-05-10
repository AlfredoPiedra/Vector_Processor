#include "control_unit.h"

ControlUnit::ControlUnit(){

    // Initialize all the class attributes
    operational_code = 0;
    i_or_p_bit = 0;

    write_all = 0;
    address_src = 0;
    alu_control = 0;
    vector_write = 0;
    memory_write = 0;
    vector_result = 0;
    immediate_src = 0;
    register_d_src = 0;
    register_write = 0;
    shifter_control = 0;
    vector_write_src = 0;
    register_write_src = 0;

    control_bits.resize(12);
}

void ControlUnit::ConfigureInput(unsigned char set_operational_code,
                                 unsigned char set_i_or_p_bit){

    operational_code = set_operational_code;
    i_or_p_bit = set_i_or_p_bit;

}

void ControlUnit::DoAction(){

    // Format F instructions
    if(operational_code <= 9){

        // Set if the instruction use a immediate value
        immediate_src = i_or_p_bit;

        // All the format F instruction write in the vector register file
        vector_write = 1;

        // This instructions does not write in memory
        memory_write = 0;
        write_all = 0;

        // Choose the data coming from the vector functional unit
        vector_write_src = 1;

        switch(operational_code){

            case 0: alu_control = 0; shifter_control = 0; vector_result = 0; break; // VADD
            case 1: alu_control = 1; shifter_control = 0; vector_result = 0; break; // VSUB
            case 2: alu_control = 2; shifter_control = 0; vector_result = 0; break; // VXOR
            case 3: alu_control = 3; shifter_control = 0; vector_result = 0; break; // VAND
            case 4: alu_control = 4; shifter_control = 0; vector_result = 0; break; // VOR
            case 5: alu_control = 0; shifter_control = 0; vector_result = 1; break; // VSHFR
            case 6: alu_control = 0; shifter_control = 1; vector_result = 1; break; // VSHFL
            case 7: alu_control = 0; shifter_control = 2; vector_result = 1; break; // VCSHFR
            case 8: alu_control = 0; shifter_control = 3; vector_result = 1; break; // VCSHFL
            default: alu_control = 0; shifter_control = 0; vector_result = 2; break; // VSET
        }

        // Dont care values
        register_write = 0;
        register_write_src = 0;
        address_src = 3;
        register_d_src = 0;

    // Format M instruction VLDR and VSTR
    }else if(operational_code == 10 || operational_code == 11){

        // The instruction is VLDR
        if(operational_code == 10){

            // Write data from memory to the vector register file
            vector_write = 1;
            memory_write = 0;

        // The instruction is VSTR
        }else{

            // Write in memory instead of the vector register file
            vector_write = 0;
            memory_write = 1;

        }

        // Write data a 64 bits value in memory
        write_all = 1;

        // Write in the register because of pre/post indexed addressing
        register_write = 1;
        register_write_src = 1;
        register_d_src = 2;

        // Choose the data coming from the memory
        vector_write_src = 0;

        // Choose from the already incremented address or the original value
        address_src = i_or_p_bit;

        // Dont care values
        vector_result = 0;
        immediate_src = 0;
        alu_control = 0;
        shifter_control = 0;

    // Format I instructions
    }else if(operational_code >= 12 && operational_code <= 15){

        if(operational_code != 14){

            // Write in the register file
            register_write = 1;
            memory_write = 0;

        // The instruction is STR
        }else{

            // Write in memory instead of the register file
            register_write = 0;
            memory_write = 1;
        }

        // Write only a 32 bit value in memory
        write_all = 0;

        // If the instruction is ADD or SET or STR
        if(operational_code != 15){

            // Choose the value coming from the functional unit
            register_write_src = 1;

        }else{

            // Choose the value coming from the memory
            register_write_src = 0;
        }

        // Set if the instruction use a immediate value
        immediate_src = i_or_p_bit;

        // Choose the value that will be written in the register file
        if(operational_code == 14){ // STR

            register_d_src = 0;

        }else if(operational_code == 13){ // SET

            register_d_src = 3;

        }else{ // ADD or LDR

            register_d_src = 1;
        }

        // Choose the i format address
        address_src = 2;

        // Dont care values
        vector_write = 0;
        vector_write_src = 0;
        vector_result = 0;
        alu_control = 0;
        shifter_control = 0;

    // Undefined format
    }else{

        throw std::runtime_error("[DoAction] undefined operational code");
    }
}

std::vector<unsigned char>  ControlUnit::GetOutput(){

    control_bits[0] = register_write;
    control_bits[1] = vector_write;
    control_bits[2] = memory_write;
    control_bits[3] = write_all;

    control_bits[4] = register_write_src;
    control_bits[5] = vector_write_src;
    control_bits[6] = vector_result;

    control_bits[7] = immediate_src;
    control_bits[8] = address_src;

    control_bits[9] = register_d_src;
    control_bits[10] = alu_control;
    control_bits[11] = shifter_control;

    return control_bits;
}

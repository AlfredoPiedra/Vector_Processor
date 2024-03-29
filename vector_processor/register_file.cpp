#include "register_file.h"

RegisterFile::RegisterFile()
{
    // Set a default value for the number
    // of register in the register filebank
    total_registers = 8;

    // Allocate the memory for the array of registers
    register_file.reserve(total_registers);

    int register_in_file;

    // Initialize all the register objects in the array
    // using the default values for the register width
    for(register_in_file = 0; register_in_file < total_registers; ++register_in_file){

        register_file.push_back(Register());
    }
}

RegisterFile::RegisterFile(unsigned char number_of_registers,
                           unsigned char size_of_registers)
{

    // Set the number of registers
    // in the register file
    total_registers = number_of_registers;

    // Allocate the memory for the array of registers
    register_file.reserve(total_registers);

    // Counter for iterate over the register array
    int register_in_file;

    // Initialize all the register objects in the array
    // using the specified register width
    for(register_in_file = 0; register_in_file < total_registers; ++register_in_file){

        register_file.push_back(Register(size_of_registers));
    }

}

std::vector<unsigned char> RegisterFile::ReadRegister(unsigned char register_number){

    if(register_number < total_registers){

        return register_file[register_number].GetOutput();

    }else{

         std::cout << "Tratando de leer: " << (int) register_number << std::endl;
         throw std::runtime_error("[ReadRegister]: register does not exist");
    }
}

void RegisterFile::WriteRegister(unsigned char register_number,
                                 std::vector<unsigned char> data)
{
    if(register_number < total_registers){

        if(data.size() > register_file[0].GetRegisterSize()){

            throw std::runtime_error("[WriteRegister]: input data exceed register capacity");
        }

        register_file[register_number].ConfigureInput(data);

        register_file[register_number].DoAction();

    }else{

         throw std::runtime_error("[WriteRegister]: register does not exist");
    }
}

void RegisterFile::ConfigureReadInput(unsigned char in_read_register_a,
                                      unsigned char in_read_register_b){

    read_register_a = in_read_register_a;
    read_register_b = in_read_register_b;
}

void RegisterFile::ConfigureWriteInput(unsigned char write_enable_signal,
                                       unsigned char in_write_register,
                                       std::vector<unsigned char> in_write_data){
    write_enable = write_enable_signal;
    write_register = in_write_register;
    write_data = in_write_data;
}

void RegisterFile::DoReadAction(){

    read_data_a = ReadRegister(read_register_a);
    read_data_b = ReadRegister(read_register_b);

}

void RegisterFile::DoWriteAction(){

    if(write_enable){

        WriteRegister(write_register, write_data);
    }
}

std::vector<unsigned char> RegisterFile::GetOutputDataA()
{
    return read_data_a;

}

std::vector<unsigned char> RegisterFile::GetOutputDataB()
{

    return read_data_b;
}

void RegisterFile::PrintContent(){

    unsigned char reg;
    unsigned char byte;
    std::vector<unsigned char> buffer;

    for(reg = 0; reg < total_registers; ++reg){

        buffer = register_file[reg].GetOutput();

        std::cout << "Reg " << (int) reg << " -----------------------" << std:: endl;

        for(byte = 0; byte < buffer.size(); ++byte){

            std::cout << (int) buffer[byte] << " ";
        }

        std::cout << std:: endl;
        std::cout << std:: endl;

    }


}

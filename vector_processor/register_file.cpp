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

std::vector<unsigned char> RegisterFile::ReadRegister(char register_number){

    if(register_number >= 0
       && register_number < total_registers){

        return register_file[register_number].GetOutputData();

    }else{

         throw std::runtime_error("[ReadRegister]: register does not exist");
    }
}

void RegisterFile::WriteRegister(char register_number,
                                 std::vector<unsigned char> data)
{
    if(register_number >= 0
       && register_number < total_registers){

        if(data.size() == register_file[0].GetRegisterSize()){

            throw std::runtime_error("[WriteRegister]: input data exceed register capacity");
        }

        register_file[register_number].SetInputData(data);

        register_file[register_number].DoAction();

    }else{

         throw std::runtime_error("[WriteRegister]: register does not exist");
    }
}

void RegisterFile::ConfigureInput(char write_enable_signal,
                                  char in_read_register_a,
                                  char in_read_register_b,
                                  char in_write_register,
                                  std::vector<unsigned char> in_write_data)
{
    write_enable = write_enable_signal;
    read_register_a = in_read_register_a;
    read_register_b = in_read_register_b;
    write_register = in_write_register;
    write_data = in_write_data;
}

void RegisterFile::DoAction()
{
    if(write_enable){

        WriteRegister(write_register, write_data);
    }

    read_data_a = ReadRegister(read_register_a);
    read_data_b = ReadRegister(read_register_b);

}

std::vector<unsigned char> RegisterFile::GetOutputDataA()
{
    return read_data_a;

}

std::vector<unsigned char> RegisterFile::GetOutputDataB()
{

    return read_data_b;
}

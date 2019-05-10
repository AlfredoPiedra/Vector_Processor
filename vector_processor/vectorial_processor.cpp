#include "vectorial_processor.h"

VectorialProcessor::VectorialProcessor(){

    fetch_stage = new Fetch();

    decode_stage = new Decode();

    execute_stage = new Execute();

    memory_stage = new Memory();

    writeback_stage = new WriteBack();
}

void VectorialProcessor::PrintBuffer(std::vector<unsigned char> buffer){


    for(int i = 0; i < (int) buffer.size(); ++i){


        std::cout << (int) buffer[i] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

}

void VectorialProcessor::StartProcessing(){

    int cycle;

    for(cycle = 0; cycle < 3; ++cycle){

        std::vector<unsigned char> buffer;

        fetch_stage->DoAction();

        buffer = fetch_stage->GetOutput();

        std::cout << "Paso Fetch" << std::endl;

        decode_stage->ConfigureInput(buffer);

        decode_stage->DoAction();

        buffer = decode_stage->GetOutput();

        std::cout << "Paso Decode" << std::endl;

        execute_stage->ConfigureInput(buffer);

        execute_stage->DoAction();

        buffer = execute_stage->GetOutput();

        std::cout << "Paso Execute" << std::endl;

        memory_stage->ConfigureInput(buffer);

        memory_stage->DoAction();

        buffer = memory_stage->GetOutput();

        std::cout << "Paso Memory" << std::endl;

        writeback_stage->ConfigureInput(buffer);

        writeback_stage->DoAction();

        buffer = writeback_stage->GetOutput();

        std::cout << "Paso Writeback" << std::endl;

        PrintBuffer(buffer);

    }
}


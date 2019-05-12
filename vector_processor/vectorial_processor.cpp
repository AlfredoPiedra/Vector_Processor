#include "vectorial_processor.h"

unsigned char VectorialProcessor::clock = 0;

Fetch VectorialProcessor::fetch_stage;
Decode VectorialProcessor::decode_stage;
Execute VectorialProcessor::execute_stage;
Memory VectorialProcessor::memory_stage;
WriteBack VectorialProcessor::writeback_stage;
HazardUnit VectorialProcessor::hazard_unit;

VectorialProcessor::VectorialProcessor(){

}


void VectorialProcessor::SolveHazards(){

    std::vector<unsigned char> buffer = decode_stage.GetHazardUnitInput();

    hazard_unit.ConfigureDecodeInput(buffer[0],  // register a
                                     buffer[1],  // register b
                                     buffer[2],  // vector a
                                     buffer[3]); // vector b

    buffer = execute_stage.GetHazardUnitInput();

    hazard_unit.ConfigureExecuteInput(buffer[0], // register d
                                      buffer[1], // register a
                                      buffer[2], // register b
                                      buffer[3], // vector d
                                      buffer[4], // vector a
                                      buffer[5], // vector b
                                      buffer[6], // register write src
                                      buffer[7]);// vector write src

    buffer = memory_stage.GetHazardUnitInput();

    hazard_unit.ConfigureMemoryInput(buffer[0], // register d
                                     buffer[1], // vector d
                                     buffer[2], // register write
                                     buffer[3]);// vector write

    std::vector<unsigned char> forward_bytes;
    forward_bytes.resize(4);

    forward_bytes[0] = buffer[4];
    forward_bytes[1] = buffer[5];
    forward_bytes[2] = buffer[6];
    forward_bytes[3] = buffer[7];

    unsigned int memory_forward_data = adapter::BytesToInteger(forward_bytes);

    std::vector<unsigned char> memory_vector_forward_data;
    memory_vector_forward_data.resize(8);

    memory_vector_forward_data[0] = buffer[8];
    memory_vector_forward_data[1] = buffer[9];
    memory_vector_forward_data[2] = buffer[10];
    memory_vector_forward_data[3] = buffer[11];
    memory_vector_forward_data[4] = buffer[12];
    memory_vector_forward_data[5] = buffer[13];
    memory_vector_forward_data[6] = buffer[14];
    memory_vector_forward_data[7] = buffer[15];

    buffer = writeback_stage.GetOutput();

    hazard_unit.ConfigureWritebackInput(buffer[13], // register d
                                        buffer[12], // vector d
                                        buffer[14], // register write
                                        buffer[15]);// vector write

    forward_bytes[0] = buffer[8];
    forward_bytes[1] = buffer[9];
    forward_bytes[2] = buffer[10];
    forward_bytes[3] = buffer[11];

    unsigned int writeback_forward_data = adapter::BytesToInteger(forward_bytes);

    std::vector<unsigned char> writeback_vector_forward_data;
    writeback_vector_forward_data.resize(8);

    writeback_vector_forward_data[0] = buffer[0];
    writeback_vector_forward_data[1] = buffer[1];
    writeback_vector_forward_data[2] = buffer[2];
    writeback_vector_forward_data[3] = buffer[3];
    writeback_vector_forward_data[4] = buffer[4];
    writeback_vector_forward_data[5] = buffer[5];
    writeback_vector_forward_data[6] = buffer[6];
    writeback_vector_forward_data[7] = buffer[7];

    hazard_unit.DoAction();

    buffer = hazard_unit.GetOutput();

    execute_stage.ConfigureForwardInput(buffer[0], // register a
                                        buffer[1], // register b
                                        buffer[2], // vector a
                                        buffer[3], // vector b
                                        memory_forward_data,
                                        writeback_forward_data,
                                        memory_vector_forward_data,
                                        writeback_vector_forward_data);
    fetch_stage.DoStall(buffer[4]);
    decode_stage.DoFlush(buffer[4]);
}

void* VectorialProcessor::StartFetchStage(void *ptr){

    fetch_stage.DoAction(clock);

    return ptr;
}

void* VectorialProcessor::StartDecodeStage(void *ptr){

    if(!clock){

        decode_stage.ConfigureInput(fetch_stage.GetOutput());
    }

    decode_stage.DoAction(clock);

    return ptr;
}

void* VectorialProcessor::StartExecuteStage(void *ptr){

    if(!clock){

        execute_stage.ConfigureInput(decode_stage.GetOutput());

    }

    execute_stage.DoAction(clock);

    return ptr;
}

void* VectorialProcessor::StartMemoryStage(void *ptr){

    if(!clock){

        memory_stage.ConfigureInput(execute_stage.GetOutput());

    }

    memory_stage.DoAction(clock);

    return ptr;
}

void* VectorialProcessor::StartWritebackStage(void *ptr){

    if(!clock){

        writeback_stage.ConfigureInput(memory_stage.GetOutput());
    }

    writeback_stage.DoAction();

    std::vector<unsigned char> writeback_output = writeback_stage.GetOutput();

    std::vector<unsigned char> vector_d_data;
    std::vector<unsigned char> register_d_data;

    vector_d_data.resize(8);
    register_d_data.resize(4);

    vector_d_data[0] = writeback_output[0];
    vector_d_data[1] = writeback_output[1];
    vector_d_data[2] = writeback_output[2];
    vector_d_data[3] = writeback_output[3];
    vector_d_data[4] = writeback_output[4];
    vector_d_data[5] = writeback_output[5];
    vector_d_data[6] = writeback_output[6];
    vector_d_data[7] = writeback_output[7];

    register_d_data[0] = writeback_output[8];
    register_d_data[1] = writeback_output[9];
    register_d_data[2] = writeback_output[10];
    register_d_data[3] = writeback_output[11];

    decode_stage.ConfigureWrite(writeback_output[15], // vector write
                                writeback_output[12], // vector d
                                writeback_output[14], // register enable
                                writeback_output[13], // register d
                                vector_d_data,
                                register_d_data);
    return ptr;
}

void VectorialProcessor::PrintBuffer(std::vector<unsigned char> buffer){

    for(int i = 0; i < (int) buffer.size(); ++i){


        std::cout << (int) buffer[i] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

}

void VectorialProcessor::LoadProgram(std::string file_name){

    fetch_stage.LoadUserProgram(file_name);
}


void VectorialProcessor::CompleteProcessing(){

    pthread_t stage_id[5];

    unsigned char thread;

    while(fetch_stage.GetSourceCodeLimit()){

        pthread_create(&stage_id[0],NULL,StartFetchStage,NULL);

        pthread_create(&stage_id[1],NULL,StartDecodeStage,NULL);

        pthread_create(&stage_id[2],NULL,StartExecuteStage,NULL);

        pthread_create(&stage_id[3],NULL,StartMemoryStage,NULL);

        pthread_create(&stage_id[4],NULL,StartWritebackStage,NULL);

        for(thread = 0; thread < 5; ++thread){

            pthread_join(stage_id[thread],NULL);

        }

        if(!clock){

            SolveHazards();

        }

        usleep(1000);
        clock = !clock;
    }

    decode_stage.PrintContent();
}

void VectorialProcessor::CycleProcessing(){

    pthread_t stage_id[5];

    unsigned char thread;

    pthread_create(&stage_id[0],NULL,StartFetchStage,NULL);

    pthread_create(&stage_id[1],NULL,StartDecodeStage,NULL);

    pthread_create(&stage_id[2],NULL,StartExecuteStage,NULL);

    pthread_create(&stage_id[3],NULL,StartMemoryStage,NULL);

    pthread_create(&stage_id[4],NULL,StartWritebackStage,NULL);

    for(thread = 0; thread < 5; ++thread){

        pthread_join(stage_id[thread],NULL);

    }

    if(!clock){

        SolveHazards();

    }

    usleep(1000);
    clock = !clock;

    decode_stage.PrintContent();

}

void VectorialProcessor::ReadAllMemory(){

    cv::Mat_<unsigned char> result_image(IMAGE_ROWS,IMAGE_COLS);

    int row = 0;
    int column = 0;

    unsigned int memory_address = 0;
    unsigned int bank_address = 0;
    std::vector<unsigned char> buffer;
    buffer.resize(4);

    MemoryBank encripted_image = memory_stage.GetMemoryBank();

    for(row = 0; row < IMAGE_ROWS; ++row){

        for(column = 0; column < IMAGE_COLS; column+=4){

            memory_address = bank_address * 4;

            encripted_image.ConfigureReadInput(memory_address,memory_address);

            encripted_image.DoReadAction();

            if(bank_address % 2 == 0){

                buffer = adapter::IntegerToBytes(encripted_image.GetOutputA());

            }else{

                buffer = adapter::IntegerToBytes(encripted_image.GetOutputB());

            }

            result_image(row,column) = buffer[0];
            result_image(row,column+1) = buffer[1];
            result_image(row,column+2) = buffer[2];
            result_image(row,column+3) = buffer[3];

            ++bank_address;
        }
    }

    cv::imwrite("/home/alfredo/VectorProcessor/result.png", result_image);
}

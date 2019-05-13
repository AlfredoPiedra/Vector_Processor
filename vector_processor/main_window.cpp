#include "main_window.h"

#include "ui_mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    //Create the button
    p_button = new QPushButton("Ejecutar Ciclo", this);
    //set size and location of the button
    p_button->setGeometry(QRect( QPoint(350, 620),
    QSize(200, 40) ));

    //Connect button signal to appropriate slot
    connect(p_button, SIGNAL (released()),this, SLOT (handleButton()));

    processor = new VectorialProcessor();
}

std::string MainWindow::GetHexString(int integer){

    std::stringstream stream;

    stream << std::hex << integer;

    std::string hexa(stream.str());

    return hexa;
}

void MainWindow::handleButton()
{

    processor->CycleProcessing();

    std::vector<unsigned char> buffer = processor->fetch_stage.pc->GetOutput();
    std::vector<unsigned char> int_buffer;
    int acum;

    int_buffer.resize(4);

    ui->F1->setText(GetHexString(adapter::BytesToInteger(buffer)).c_str());

    buffer = processor->fetch_stage.GetOutput();

    ui->F2->setText(GetHexString(adapter::BytesToInteger(buffer)).c_str());

    ui->F3->setText(GetHexString((int) processor->fetch_stage.fetch_stall).c_str());

    buffer = processor->decode_stage.GetOutput();

    int_buffer[0] = buffer[24];
    int_buffer[1] = buffer[25];
    int_buffer[2] = buffer[26];
    int_buffer[3] = buffer[27];

    acum = adapter::BytesToInteger(int_buffer);
    acum  = acum << 4;

    int_buffer[0] = buffer[28];
    int_buffer[1] = buffer[29];
    int_buffer[2] = buffer[30];
    int_buffer[3] = buffer[31];

    acum = adapter::BytesToInteger(int_buffer);
    acum  = acum << 4;

    int_buffer[0] = buffer[32];
    int_buffer[1] = buffer[33];
    int_buffer[2] = buffer[34];
    int_buffer[3] = buffer[35];

    acum = adapter::BytesToInteger(int_buffer);

    ui->D1->setText(GetHexString(acum).c_str());

    ui->D2->setText(GetHexString((int)buffer[36]).c_str());

    ui->D3->setText(GetHexString((int)buffer[37]).c_str());

    ui->D4->setText(GetHexString((int)buffer[38]).c_str());


    int_buffer[0] = buffer[39];
    int_buffer[1] = buffer[40];
    int_buffer[2] = buffer[41];
    int_buffer[3] = buffer[42];

    ui->D5->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[43];
    int_buffer[1] = buffer[44];
    int_buffer[2] = buffer[45];
    int_buffer[3] = buffer[46];

    ui->D6->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    ui->D7->setText(GetHexString((int)buffer[47]).c_str());
    ui->D8->setText(GetHexString((int)buffer[48]).c_str());
    ui->D9->setText(GetHexString((int)buffer[49]).c_str());
    ui->D10->setText(GetHexString((int)buffer[50]).c_str());

    buffer = processor->execute_stage.GetOutput();

    int_buffer[0] = buffer[20];
    int_buffer[1] = buffer[21];
    int_buffer[2] = buffer[24];
    int_buffer[3] = buffer[25];

    ui->E1->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[12];
    int_buffer[1] = buffer[13];
    int_buffer[2] = buffer[14];
    int_buffer[3] = buffer[15];

    ui->E2->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[16];
    int_buffer[1] = buffer[17];
    int_buffer[2] = buffer[18];
    int_buffer[3] = buffer[19];

    ui->E3->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());
    ui->E4->setText(GetHexString((int)buffer[22]).c_str());
    ui->E5->setText(GetHexString((int)buffer[23]).c_str());


    buffer = processor->memory_stage.GetOutput();

    int_buffer[0] = buffer[21];
    int_buffer[1] = buffer[22];
    int_buffer[2] = buffer[15];
    int_buffer[3] = buffer[26];

    ui->M1->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[12];
    int_buffer[1] = buffer[13];
    int_buffer[2] = buffer[14];
    int_buffer[3] = buffer[15];

    ui->M2->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[16];
    int_buffer[1] = buffer[17];
    int_buffer[2] = buffer[18];
    int_buffer[3] = buffer[19];

    ui->M3->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = processor->writeback_stage.GetOutput();

    int_buffer[0] = 0;
    int_buffer[1] = 0;
    int_buffer[2] = buffer[14];
    int_buffer[3] = buffer[15];

    ui->W1->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());


    ui->W2->setText(GetHexString((int)buffer[12]).c_str());
    ui->W3->setText(GetHexString((int)buffer[13]).c_str());

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->W41->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->W42->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[8];
    int_buffer[1] = buffer[9];
    int_buffer[2] = buffer[10];
    int_buffer[3] = buffer[11];

    ui->W5->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    RegisterFile *r_regs = processor->decode_stage.scalar_registers;
    RegisterFile *v_regs = processor->decode_stage.vector_registers;

    ui->R0->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[0].GetOutput())).c_str());
    ui->R1->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[1].GetOutput())).c_str());
    ui->R2->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[2].GetOutput())).c_str());
    ui->R3->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[3].GetOutput())).c_str());
    ui->R4->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[4].GetOutput())).c_str());
    ui->R5->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[5].GetOutput())).c_str());
    ui->R6->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[6].GetOutput())).c_str());
    ui->R7->setText(GetHexString(adapter::BytesToInteger(r_regs->register_file[7].GetOutput())).c_str());

    buffer = v_regs->register_file[0].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V0A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V0B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());


    buffer = v_regs->register_file[1].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V1A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V1B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());


    buffer = v_regs->register_file[2].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V2A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V2B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[3].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V3A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V3B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[4].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V4A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V4B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[5].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V5A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V5B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[6].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V6A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V6B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[7].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V7A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V7B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[8].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V8A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V8B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[9].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V9A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V9B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[10].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V10A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V10B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[11].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V11A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V11B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[12].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V12A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V12B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[13].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V13A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V13B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[14].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V14A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V14B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    buffer = v_regs->register_file[15].GetOutput();

    int_buffer[0] = buffer[0];
    int_buffer[1] = buffer[1];
    int_buffer[2] = buffer[2];
    int_buffer[3] = buffer[3];

    ui->V15A->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

    int_buffer[0] = buffer[4];
    int_buffer[1] = buffer[5];
    int_buffer[2] = buffer[6];
    int_buffer[3] = buffer[7];

    ui->V15B->setText(GetHexString(adapter::BytesToInteger(int_buffer)).c_str());

}

MainWindow::~MainWindow()
{

}


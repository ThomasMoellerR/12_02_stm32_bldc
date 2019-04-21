#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "com.h"
#include "ser.h"
#include "typ.h"
#include "ctl.h"
#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QTimer>
#include <string.h>
#include "json.h"
#include "config.h"

Ser* ser = new Ser();
Config* config = new Config();
QTimer timer;

#define MODE_STEUERUNG 0
#define MODE_MAN_KOMM 1

uint8_t Mode;

uint8_t Motortyp_was_Set = 0;
uint8_t Hall_Information_was_Set = 0;
uint8_t Mode_was_Set = 0;

TUINT32 BLDC_au32Physical_Period[6];
TUINT32 BLDC_au32Physical_Period_Sum;
TUINT32 BLDC_au32Physical_Period_Symmetrie;

float BLDC_afPhysical_Period_Factors[6];

uint8_t noticeLastCmd;


//////////////// Neue Defines

// Protocol Positions
#define CMD						0
#define DIRECTION				1
#define PWM						2
#define DATA					1
#define DELAY					4

// Commands
#define CMD_INIT 					0x11
#define CMD_TEST_MOSFETS 			0x12
#define CMD_HALL 					0x13
#define CMD_SENSORLESS				0x14
#define CMD_MANUAL_COMMUTATION		0x15
#define CMD_SET_HALL_INFORMATION	0x16
#define CMD_STEUERUNG				0x17
#define CMD_REGELUNG				0x18
#define CMD_GET_STATE_REQUEST		0x19
#define CMD_GET_STATE_RESPONSE		0x20
#define SET_MOSFETS					0x21
#define SET_HALL_DETECTION			0x22
#define GET_HALL_INFO				0x23
#define SET_DIR_PWM_DELAY			0x24
#define SET_DIR_PWM					0x25
#define SET_RPS_INFO				0x26
#define GET_RPS_INFO				0x27

#define TEST_MOSFETS_1H     1
#define TEST_MOSFETS_1L     2
#define TEST_MOSFETS_2H     3
#define TEST_MOSFETS_2L     4
#define TEST_MOSFETS_3H     5
#define TEST_MOSFETS_3L     6


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Com* com = new Com();
    Ctl* ctl = new Ctl();


    connect(config, SIGNAL (sigBaud(int)), com, SLOT (setBaud(int)));
    connect(config, SIGNAL (sigPort(QString)), com, SLOT (setPort(QString)));
    config->ini();
    ui->lineEdit_SetHall->setText(config->config_map["Hall"]);


    QThread* com_thread = new QThread();
    com->moveToThread(com_thread);
    connect(com, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(com_thread, SIGNAL (started()), com, SLOT (initPort()));
    connect(com_thread, SIGNAL (started()), com, SLOT (process()));
    connect(com, SIGNAL (finished()), com_thread, SLOT (quit()));
    connect(com_thread, SIGNAL (finished()), com_thread, SLOT (deleteLater()));
    com_thread->start();


    QThread* ctl_thread = new QThread();
    ctl->moveToThread(ctl_thread);
    connect(ctl_thread, SIGNAL (started()), com, SLOT (initPort()));
    connect(ctl_thread, SIGNAL (started()), ctl, SLOT (process()));
    connect(ctl, SIGNAL (finished()), ctl_thread, SLOT (quit()));
    connect(ctl_thread, SIGNAL (finished()), ctl_thread, SLOT (deleteLater()));
    ctl_thread->start();


    timer= new QTimer();
    connect(timer, SIGNAL(timeout()), ctl, SLOT(timer()),Qt::DirectConnection);
    timer->start(100);

    // Serial In
    connect(com, SIGNAL (received(QByteArray)), ser, SLOT (Rec_Input(QByteArray)), Qt::DirectConnection);
    connect(ser, SIGNAL (Rec_Output(QByteArray)), ctl, SLOT (message_in(QByteArray)), Qt::DirectConnection);
    connect(ser, SIGNAL (Rec_Output(QByteArray)), this, SLOT (message_in(QByteArray)), Qt::DirectConnection);

    // Serial Out
    connect(ctl, SIGNAL (message_out(QByteArray)), ser, SLOT (Snd_Input(QByteArray)), Qt::DirectConnection);
    connect(ser, SIGNAL (Snd_Output(QByteArray)), com, SLOT (writeData(QByteArray)), Qt::DirectConnection);


    connect(ser, SIGNAL (Rec_Output(QByteArray)), ser, SLOT (Debug_ASCII(QByteArray)));
    //connect(ser, SIGNAL (Rec_Output(QByteArray)), ser, SLOT (Debug_HEX(QByteArray)));
    connect(ser, SIGNAL (Snd_Output(QByteArray)), ser, SLOT (Debug_HEX(QByteArray)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_aufruf()
{
    tyun_AnyData unAnyData;

    QByteArray senddata;

    switch (noticeLastCmd) // Mode
    {


        case CMD_STEUERUNG:


            unAnyData.u16Data = ui->spinBox_PWM->value();
            senddata[CMD] = SET_DIR_PWM;
            senddata[DIRECTION] = ui->checkBox->checkState() ? 1 : 0; // Dir
            senddata[PWM] = unAnyData.au8Data[0];
            senddata[PWM +1] = unAnyData.au8Data[1];

            ser->Snd_Input(senddata);

            break;


        case CMD_MANUAL_COMMUTATION:
            unAnyData.u16Data = ui->spinBox_PWM->value();
            senddata[CMD] = SET_DIR_PWM_DELAY;
            senddata[DIRECTION] = ui->checkBox->checkState() ? 1 : 0; // Dir
            senddata[PWM] = unAnyData.au8Data[0];
            senddata[PWM +1] = unAnyData.au8Data[1];


            unAnyData.u16Data = ui->spinBox_TIME->value();
            senddata[DELAY] = unAnyData.au8Data[0];
            senddata[DELAY +1] = unAnyData.au8Data[1];
            ser->Snd_Input(senddata);
            break;





        default: break;

    }


}

// Incomming messages form serial interface
void MainWindow::message_in(QByteArray data)
{
    tyun_AnyData unAnyData;

    QString text;

    QByteArray state;

    switch(data[0])
    {
        case GET_HALL_INFO:


            for (int i = DATA; i <= 6; i++) text.append(data.number(data[i]));
            ui->lineEdit->setText(text);
            break;

        case GET_RPS_INFO:


            unAnyData.au8Data[0] = data[1];
            unAnyData.au8Data[1] = data[2];
            text = QString::number(unAnyData.u16Data);
            ui->lineEdit_UMIN->setText(text);
            break;


        case CMD_GET_STATE_RESPONSE:
            ui->lineEdit_SetState->setText(QString::number(data[DATA]));
            break;





        default: break;

    }



    qDebug("incomming message");
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_SetHall->setText(ui->lineEdit->text());
}

void MainWindow::on_pushButton_SetHall_clicked()
{
    tyun_AnyData unAnyData;
    QByteArray senddata;
    QByteArray hall = ui->lineEdit_SetHall->text().toUtf8();

    senddata[CMD] = CMD_SET_HALL_INFORMATION;
    for (int i = 0; i < 6; i++) senddata.append(hall[i] - 48); // -48 von char auf dezimal

    ser->Snd_Input(senddata);
    Hall_Information_was_Set = 1;

}





void MainWindow::on_pushButton_Set_Application_Mode_clicked()
{
    QByteArray senddata;

    if(ui->comboBox_Motortyp->currentText() == "Hall")
    {
        senddata[CMD] = CMD_HALL;
        noticeLastCmd = senddata[CMD];

    }


    ser->Snd_Input(senddata);
    Motortyp_was_Set = 1;


}


void MainWindow::on_pushButton_Save_clicked()
{
    config->config_map["Hall"] = ui->lineEdit->text();
    config->Map_To_JsonFile();
}


void MainWindow::on_pushButton_Set_Mode_clicked()
{
    QByteArray senddata;

    if(ui->comboBox->currentText() == "Steuerung")
    {
        senddata[CMD] = CMD_STEUERUNG;
        noticeLastCmd = senddata[CMD];
        ser->Snd_Input(senddata);
    }

    if(ui->comboBox->currentText() == "Manuelle Kommutierung")
    {
        senddata[CMD] = CMD_MANUAL_COMMUTATION;
        noticeLastCmd = senddata[CMD];
        ser->Snd_Input(senddata);
    }

    if(ui->comboBox->currentText() == "Test Mosfets")
    {
        senddata[CMD] = CMD_TEST_MOSFETS;
        noticeLastCmd = senddata[CMD];
        ser->Snd_Input(senddata);
    }
}



void MainWindow::on_pushButton_Get_State_clicked()
{
    QByteArray senddata;
    senddata[CMD] = CMD_GET_STATE_REQUEST;
    ser->Snd_Input(senddata);
}


void MainWindow::on_checkBox_Send_Cyclic_stateChanged(int arg1)
{
    if (arg1) connect(timer, SIGNAL(timeout()), this, SLOT(timer_aufruf()),Qt::DirectConnection);
    else disconnect(timer, SIGNAL(timeout()), this, SLOT(timer_aufruf()));
}

void MainWindow::on_checkBox_Enable_RPS_Info_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_RPS_INFO;
    senddata[DATA] = arg1 ? 1: 0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_Enable_Hall_Detection_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_HALL_DETECTION;
    senddata[DATA] = arg1 ? 1: 0;
    ser->Snd_Input(senddata);
}



void MainWindow::on_checkBox_1H_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_1L_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_2H_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_2L_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_3H_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

void MainWindow::on_checkBox_3L_stateChanged(int arg1)
{
    QByteArray senddata;
    senddata[CMD] = SET_MOSFETS;
    senddata[TEST_MOSFETS_1H] = ui->checkBox_1H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_1L] = ui->checkBox_1L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2H] = ui->checkBox_2H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_2L] = ui->checkBox_2L->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3H] = ui->checkBox_3H->checkState() ? 1:0;
    senddata[TEST_MOSFETS_3L] = ui->checkBox_3L->checkState() ? 1:0;
    ser->Snd_Input(senddata);
}

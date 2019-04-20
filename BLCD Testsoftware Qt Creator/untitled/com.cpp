#include "com.h"
#include <QDebug>
#include <QMessageBox>

Com::Com()
{
}

Com::~Com()
{
    if (portOpened) portCom->close();
}

void Com::process()
{
    while(1)
    {
        if (portOpened)
        {
            if (portCom->waitForReadyRead(-1))
               {
                  emit received ((QByteArray)portCom->readAll());
               }
        }
   }
   emit finished();
}


void Com::initPort()
{
  if(portCom==NULL)
  {
      portCom=new QSerialPort;
      portCom->setFlowControl(QSerialPort::NoFlowControl);
      portCom->setPortName(Port);
      portCom->setBaudRate(Baud);
      portCom->setDataBits(QSerialPort::Data8);
      portCom->setParity(QSerialPort::NoParity);
  }

  if(portCom->open(QSerialPort::ReadWrite))
  {

      portOpened = 1;
      qDebug() << "port successfully opened";
      emit openPortOk(true);
  }
  else
  {
      emit openPortOk(false);
      qDebug() << "port cannot opened";
  }
}

void Com::setBaud(int setBaud)
{
  Baud = setBaud;

  qDebug() << Baud;
}

void Com::setPort(QString setPort)
{
  Port = setPort;

  qDebug() << Port;
}

void Com::writeData(QByteArray data)
{
    if (portOpened)
    {
         portCom->write(data);
         portCom->waitForBytesWritten(0);
    }
}


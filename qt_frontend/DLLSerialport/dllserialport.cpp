#include "dllserialport.h"


DLLSerialport::DLLSerialport(QObject *parent) : QObject(parent)
{

    objectQSerialPort = new QSerialPort;


    connect (objectQSerialPort, SIGNAL(readyRead()), this, SLOT(readSerialPort()));
}

DLLSerialport::~DLLSerialport()
{

    delete objectQSerialPort;

    objectQSerialPort = nullptr;

    qDebug () << "objectQSerialPort destroyed";

}


void DLLSerialport::readSerialPort()

{

    qDebug() << "Reading data from serial port";

    serialportData="";

    serialportData=objectQSerialPort->readAll();

    serialportData.remove(0,3);

    serialportData.chop(3);

    qDebug() << serialportData;

    qDebug() << "EMIT dataReadDone";

    emit serialportDataReadDone(serialportData);

}

void DLLSerialport::openSerialPort()

{

    objectQSerialPort->setPortName("/dev/ttyACM0");

    objectQSerialPort->setBaudRate(QSerialPort::Baud9600);

    objectQSerialPort->setDataBits(QSerialPort::Data8);

    objectQSerialPort->setParity(QSerialPort::NoParity);

    objectQSerialPort->setStopBits(QSerialPort::OneStop);

    objectQSerialPort->setFlowControl(QSerialPort::NoFlowControl);



    if (objectQSerialPort->open(QIODevice::ReadWrite))

    {

        qDebug () << "Serial port open";

    }

    else

    {

        qDebug () << "Fail to open serial port";

    }

}

QString DLLSerialport::returnSerialportData()

{

    return serialportData;


}

void DLLSerialport::closeSerialPort()

{

    objectQSerialPort->close();

    qDebug () << "Serial port closed";

}

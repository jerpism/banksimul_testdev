#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialport_global.h"
#include <QtSerialPort>

class DLLSERIALPORT_EXPORT DLLSerialport : public QObject
{
        Q_OBJECT
public:
    DLLSerialport(QObject *parent=nullptr);
    ~DLLSerialport();

    void openSerialPort();
    void closeSerialPort();

    QString returnSerialportData();

private:
    QSerialPort *objectQSerialPort = nullptr;
    QString serialportData;
private slots:
    void readSerialPort();

signals:
    void serialportDataReadDone(QString);
};

#endif // DLLSERIALPORT_H

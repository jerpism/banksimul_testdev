#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H

#include "DLLRestAPI_global.h"
#include "engineclass.h"

class DLLRESTAPI_EXPORT DLLRestAPI : public QObject
{
    Q_OBJECT
public:
    DLLRestAPI();
    ~DLLRestAPI();
    QString getBalance();
    QString getCryptoBalance();
    QString getRate();
    QString getName();
    QString getAddr();
    QString getPhone();

    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void buyCrypto(QString);
    void sellCrypto(QString);
    void transferMoney(QString, QString);
    bool accountExists(QString);

private:
    EngineClass *objectEngineClass;

private slots:
    void gotInfoSlot();

signals:
    void infoReceived();
};

#endif // DLLRESTAPI_H

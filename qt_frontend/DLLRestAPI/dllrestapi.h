#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H

#include "DLLRestAPI_global.h"
#include "engineclass.h"

class DLLRESTAPI_EXPORT DLLRestAPI
{
public:
    DLLRestAPI();
    ~DLLRestAPI();
    QString getBalance();
    QString getCryptoBalance();
    QString getRate();

    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void buyCrypto(QString);
    void sellCrypto(QString);
    void transferMoney(QString, QString);

private:
    EngineClass *objectEngineCLass;
};

#endif // DLLRESTAPI_H

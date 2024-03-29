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
    QString getRecent(int, int);

    void login(QString, QString);
    int actionCount();
    void logout();
    void withdrawMoney(QString);
    void buyCrypto(QString);
    void sellCrypto(QString);
    void transferMoney(QString, QString);
    void lockCard(QString);
    bool accountExists(QString);

private:
    EngineClass *objectEngineClass;

private slots:
    void gotInfoSlot();
    void loginSlot(QString);
    void errorSlot(QString);
    void successSlot(QString);

signals:
    void infoReceived();
    void loginSignal(QString);
    void errorSignal(QString);
    void successSignal(QString);
};

#endif // DLLRESTAPI_H

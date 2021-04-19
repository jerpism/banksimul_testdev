#ifndef RESTAPI_H
#define RESTAPI_H

#include "restapi_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>
#include <QString>
#include <QDebug>

class RESTAPI_EXPORT Restapi : public QObject
{
    Q_OBJECT
public:
    Restapi();
    double getBalance();
    double getCryptoBalance();
    double getRate();
    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void transferMoney(QString, QString);
    void buyCrypto(QString);
    void sellCrypto(QString);


private slots:
    void withdrawSlot();
    void accSlot();
    void cryptoSlot();
    void transferSlot();
    void convertCryptoSlot();
    void loginSlot();

signals:
    void errorSignal(QString);
    void successSignal(QString);
    void loginSignal(bool);

private:
    void setAccount(QString);
    void setCryptoAccount(QString);
    QString cardid;
    QString credentials;
    QString account;
    QString cryptoaccount;
    QString url;
    QSslConfiguration config;

    QNetworkAccessManager *networkManager;

    QNetworkReply *balanceReply;
    QNetworkReply *cryptoBalanceReply;
    QNetworkReply *withdrawReply;
    QNetworkReply *accReply;
    QNetworkReply *cryptoReply;
    QNetworkReply *convertCryptoReply;
    QNetworkReply *transferReply;
    QNetworkReply *loginReply;
    QNetworkReply *ratesReply;
};
#endif // RESTAPI_H

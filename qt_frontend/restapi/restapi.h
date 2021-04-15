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
    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void setAccount(QString);
    void setCryptoAccount(QString);
    void transferMoney(QString, QString);
    void buyCrypto(QString);
    void sellCrypto(QString);


private slots:
    void withdrawSlot(QNetworkReply *reply);
    void accSlot(QNetworkReply *reply);
    void cryptoSlot(QNetworkReply *reply);
    void transferSlot(QNetworkReply *reply);
    void convertCryptoSlot(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);

signals:
    void errorSignal(QString);
    void successSignal(QString);
    void loginSignal(bool);

private:
    QString credentials;
    QString account;
    QString cryptoaccount;
    QString url;
    QSslConfiguration config;

    QNetworkAccessManager *balanceManager;
    QNetworkReply *balanceReply;

    QNetworkAccessManager *cryptoBalanceManager;
    QNetworkReply *cryptoBalanceReply;

    QNetworkAccessManager *withdrawManager;
    QNetworkReply *withdrawReply;

    QNetworkAccessManager *accManager;
    QNetworkReply *accReply;

    QNetworkAccessManager *cryptoManager;
    QNetworkReply *cryptoReply;

    QNetworkAccessManager *convertCryptoManager;
    QNetworkReply *convertCryptoReply;

    QNetworkAccessManager *transferManager;
    QNetworkReply *transferReply;

    QNetworkAccessManager *loginManager;
    QNetworkReply *loginReply;
};

#endif // RESTAPI_H

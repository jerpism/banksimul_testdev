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

signals:
    void errorSignal(QString);
    void successSignal(QString);

private:
    QString credentials;
    QString account;
    QString cryptoaccount;
    QString url;
    QSslConfiguration config;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *balanceReply;

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
};

#endif // RESTAPI_H

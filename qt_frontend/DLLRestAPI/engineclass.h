#ifndef ENGINECLASS_H
#define ENGINECLASS_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>
#include <QString>
#include <QDebug>

class EngineClass : public QObject
{
    Q_OBJECT
public:
    EngineClass();
    virtual ~EngineClass();

    double getBalance();
    double getCryptoBalance();
    double getRate();

    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void buyCrypto(QString);
    void sellCrypto(QString);
    void transferMoney(QString, QString);
    bool accountExists(QString);

private slots:
    void loginSlot();
    void accSlot();
    void cryptoAccSlot();
    void withdrawSlot();
    void cryptoSlot();
    void transferSlot();

private:
    void setAccount(QString);
    void setCryptoAccount(QString);

    QString credentials;
    QString url;
    QString account;
    QString cryptoaccount;
    QString cardid;

    QNetworkAccessManager *networkManager;
    QSslConfiguration config;

    QNetworkReply *balanceReply;
    QNetworkReply *loginReply;
    QNetworkReply *accReply;
    QNetworkReply *cryptoAccReply;
    QNetworkReply *cryptoBalanceReply;
    QNetworkReply *withdrawReply;
    QNetworkReply *rateReply;
    QNetworkReply *cryptoReply;
    QNetworkReply *transferReply;
    QNetworkReply *existsReply;

};

#endif // ENGINECLASS_H

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
    QString getName();
    QString getAddr();
    QString getPhone();
    QString getRecent(QString, QString);

    void login(QString, QString);
    void logout();
    void withdrawMoney(QString);
    void buyCrypto(QString);
    void sellCrypto(QString);
    void transferMoney(QString, QString);
    bool accountExists(QString);
    void getInfo();

signals:
    void gotInfo();
    void loginSignal(bool);
    void errorSignal(QString);
    void successSignal(QString);


private slots:
    void loginSlot();
    void accSlot();
    void cryptoAccSlot();
    void withdrawSlot();
    void cryptoSlot();
    void transferSlot();
    void infoSlot();

private:
    void setAccount(QString);
    void setCryptoAccount(QString);

    QString credentials;
    QString url;
    QString account;
    QString cryptoaccount;
    QString cardid;

    QString name;
    QString phone;
    QString addr;

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
    QNetworkReply *infoReply;
    QNetworkReply *actionsReply;

};

#endif // ENGINECLASS_H

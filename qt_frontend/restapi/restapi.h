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
private slots:
    void withdrawSlot(QNetworkReply *reply);
    void accSlot(QNetworkReply *reply);

signals:
    void errorSignal(QString);

private:
    QString credentials;
    QString account;
    QString url;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *balanceReply;

    QNetworkAccessManager *withdrawManager;
    QNetworkReply *withdrawReply;

    QNetworkAccessManager *accManager;
    QNetworkReply *accReply;
};

#endif // RESTAPI_H

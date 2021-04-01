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
    double getBalance(QString);
    void withdrawMoney(QString, QString);
private slots:
    void withdrawSlot(QNetworkReply *reply);

private:
    QString credentials;
    QString tili;
    QString url;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *balanceReply;

    QNetworkAccessManager *withdrawManager;
    QNetworkReply *withdrawReply;
};

#endif // RESTAPI_H

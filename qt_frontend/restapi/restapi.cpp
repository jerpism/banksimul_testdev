#include "restapi.h"

Restapi::Restapi()
{
    credentials="admin:1234";
    url = "http://91.145.117.152:3000";
}


double Restapi::getBalance(QString tili){
    QNetworkRequest request(url+"/account/getBalance/"+tili);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    balanceManager = new QNetworkAccessManager;
    QEventLoop loop;
    balanceReply = balanceManager->get(request);
    connect(balanceReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString response = balanceReply->readAll();
    qDebug() << response;

    balanceReply->deleteLater();
    balanceManager->deleteLater();

    return response.toDouble();
}


void Restapi::withdrawMoney(QString id, QString amount){
    QJsonObject json_obj;
    json_obj.insert("id", id);
    json_obj.insert("amount", amount);
    double saldo = this->getBalance(id);


    if(saldo - amount.toDouble() < 0 ){
        qDebug() << "PRöööööhhh :DDDD";
    }else{


    QNetworkRequest request(url+"/account/withdraw_action");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    withdrawManager = new QNetworkAccessManager;
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));
    withdrawReply=withdrawManager->post(request, QJsonDocument(json_obj).toJson());

    }
}


void Restapi::withdrawSlot(QNetworkReply* reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;
    withdrawManager->deleteLater();
    withdrawReply->deleteLater();
    reply->deleteLater();
}

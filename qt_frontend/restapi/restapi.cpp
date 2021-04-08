#include "restapi.h"

Restapi::Restapi()
{
    credentials="admin:1234";
    url = "http://91.145.117.152:3000";
}

void Restapi::setAccount(QString card){
   QNetworkRequest request(url+"/card/getAccount/"+card);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());
   accManager = new QNetworkAccessManager;
   connect(accManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accSlot(QNetworkReply*)));
   accReply = accManager->get(request);
}

void Restapi::setCryptoAccount(QString card){

}

void Restapi::transferMoney(QString recipient, QString amount){
    QJsonObject json_obj;
    json_obj.insert("id_sender", account);
    json_obj.insert("id_recipient", recipient);
    json_obj.insert("amount", amount);
    double saldo = this->getBalance();

    if(amount.toDouble() < 0){
        emit errorSignal("Et voi siirtää negatiivisia summia");
    }else if(saldo - amount.toDouble() < 0 ){
        emit errorSignal("Tilillä ei ole tarpeeksi rahaa");
    }else{

    QNetworkRequest request(url+"/account/transfer_action");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    transferManager = new QNetworkAccessManager;
    connect(transferManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transferSlot(QNetworkReply*)));
    transferReply=transferManager->post(request, QJsonDocument(json_obj).toJson());

    }
}

double Restapi::getBalance(){
    QNetworkRequest request(url+"/account/getBalance/"+account);
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
    qDebug() << "balance vastaus: "+response;

    balanceReply->deleteLater();
    balanceManager->deleteLater();

    return response.toDouble();
}


void Restapi::withdrawMoney(QString amount){
    QJsonObject json_obj;
    json_obj.insert("id", account);
    json_obj.insert("amount", amount);
    double saldo = this->getBalance();

    if(amount.toDouble() < 0){
        emit errorSignal("Et voi nostaa negatiivisia summia");
    }else if(saldo - amount.toDouble() < 0 ){
        emit errorSignal("Tilillä ei ole tarpeeksi rahaa");
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
    qDebug() << "vastaus: " +response_data;
    withdrawManager->deleteLater();
    withdrawReply->deleteLater();
    reply->deleteLater();
}


void Restapi::transferSlot(QNetworkReply* reply){
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;

    if(response_data == ""){
       emit errorSignal("Siirto ei onnistunut");
    }

    transferManager->deleteLater();
    transferReply->deleteLater();
    reply->deleteLater();
}

void Restapi::accSlot(QNetworkReply* reply){
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;

    if(response_data == "\"Account not found\""){
        qDebug() << "Tiliä ei löytynyt";
        emit errorSignal("Tili hukassa");
        account = "404";
    }else{
        account = response_data;
    }

    accManager->deleteLater();
    accReply->deleteLater();
    reply->deleteLater();

}

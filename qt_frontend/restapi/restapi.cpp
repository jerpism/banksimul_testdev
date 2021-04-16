#include "restapi.h"

Restapi::Restapi()
{
    credentials="admin:1234";
    url = "http://91.145.117.152:3000";
    config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
}

void Restapi::login(QString card, QString pin){
    QJsonObject json_obj;
    json_obj.insert("id", card);
    json_obj.insert("pin", pin);

    QNetworkRequest request(url+"/login");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

   loginManager = new QNetworkAccessManager;
   connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
   loginReply = loginManager->post(request, QJsonDocument(json_obj).toJson());
}
void Restapi::logout(){
   account = "";
   cryptoaccount = "";
}

void Restapi::setAccount(QString card){
   QNetworkRequest request(url+"/card/getAccount/"+card);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());
   accManager = new QNetworkAccessManager;
   connect(accManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accSlot(QNetworkReply*)));
   accReply = accManager->get(request);
}

void Restapi::setCryptoAccount(QString card){
   QNetworkRequest request(url+"/card/getCryptoAccount/"+card);
   config.setPeerVerifyMode(QSslSocket::VerifyNone);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());
   cryptoManager = new QNetworkAccessManager;
   connect(cryptoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cryptoSlot(QNetworkReply*)));
   cryptoReply = cryptoManager->get(request);

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
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    transferManager = new QNetworkAccessManager;
    connect(transferManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transferSlot(QNetworkReply*)));
    transferReply=transferManager->post(request, QJsonDocument(json_obj).toJson());

    }
}

void Restapi::buyCrypto(QString amount){
    QJsonObject json_obj;
    json_obj.insert("id_acc", account);
    json_obj.insert("id_crypto", cryptoaccount);
    json_obj.insert("amount", amount);

    if(amount.toDouble() < 0){
        emit errorSignal("Et voi ostaa negatiivisia summia");
    }else{

    QNetworkRequest request(url+"/cryptoAccount/buy_crypto");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    convertCryptoManager = new QNetworkAccessManager;
    connect(convertCryptoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(convertCryptoSlot(QNetworkReply*)));
    convertCryptoReply=convertCryptoManager->post(request, QJsonDocument(json_obj).toJson());
    }

}

void Restapi::sellCrypto(QString amount){
    QJsonObject json_obj;
    json_obj.insert("id_acc", account);
    json_obj.insert("id_crypto", cryptoaccount);
    json_obj.insert("amount", amount);

    if(amount.toDouble() < 0){
        emit errorSignal("Et voi myydä negatiivisia määriä");
    }else{

    QNetworkRequest request(url+"/cryptoAccount/sell_crypto");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    convertCryptoManager = new QNetworkAccessManager;
    connect(convertCryptoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(convertCryptoSlot(QNetworkReply*)));
    convertCryptoReply=convertCryptoManager->post(request, QJsonDocument(json_obj).toJson());
    }

}

double Restapi::getBalance(){
    QNetworkRequest request(url+"/account/getBalance/"+account);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
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

double Restapi::getRate(){
    QNetworkRequest request(url+"/rates/getRate/");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    ratesManager = new QNetworkAccessManager;
    QEventLoop loop;
    ratesReply = ratesManager->get(request);
    connect(ratesReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString response = ratesReply->readAll();
    qDebug() << "rates vastaus: "+response;

    ratesReply->deleteLater();
    ratesManager->deleteLater();

    return response.toDouble();
}

double Restapi::getCryptoBalance(){
    QNetworkRequest request(url+"/cryptoaccount/getBalance/"+cryptoaccount);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    cryptoBalanceManager = new QNetworkAccessManager;
    QEventLoop loop;
    cryptoBalanceReply = cryptoBalanceManager->get(request);
    connect(cryptoBalanceReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString response = cryptoBalanceReply->readAll();
    qDebug() << "balance vastaus: "+response;

    cryptoBalanceReply->deleteLater();
    cryptoBalanceManager->deleteLater();

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
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    withdrawManager = new QNetworkAccessManager;
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));
    withdrawReply=withdrawManager->post(request, QJsonDocument(json_obj).toJson());

    }
}

void Restapi::loginSlot(QNetworkReply* reply){
    QByteArray response_data = reply->readAll();
    qDebug() << "login vastaus: " + response_data;

    if(response_data == "true"){
        emit loginSignal(true);
    }else{
        emit loginSignal(false);
    }

}

void Restapi::withdrawSlot(QNetworkReply* reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << "vastaus: " +response_data;

    if(response_data.toInt() < 3){
       emit errorSignal("Nosto epäonnistui");
    }else{
       emit successSignal("Nosto onnistui");
    }
    withdrawManager->deleteLater();
    withdrawReply->deleteLater();
    reply->deleteLater();
}


void Restapi::transferSlot(QNetworkReply* reply){
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;

    if(response_data == ""){
       emit errorSignal("Siirto ei onnistunut");
    }else{
       emit successSignal("Siirto onnistui");
    }

    transferManager->deleteLater();
    transferReply->deleteLater();
    reply->deleteLater();
}

void Restapi::convertCryptoSlot(QNetworkReply* reply){
   QByteArray response_data = reply->readAll();
   qDebug() << "Krypton oston data: " + response_data;
   if(response_data != "1"){
       emit successSignal("Krypton vaihto onnistui");
   }else{
       emit errorSignal("Krypton vaihdossa oli virhe");
   }

   convertCryptoManager->deleteLater();
   convertCryptoReply->deleteLater();
   reply->deleteLater();
}

void Restapi::accSlot(QNetworkReply* reply){
    QByteArray response_data=reply->readAll();
    qDebug() << reply->error();
    qDebug() << response_data;
    if(response_data == "\"Account not found\""){
        qDebug() << "Tiliä ei löytynyt";
        emit errorSignal("Tiliä ei ole");
        account = "404";
    }else{
        account = response_data;
    }

    accManager->deleteLater();
    accReply->deleteLater();
    reply->deleteLater();

}

void Restapi::cryptoSlot(QNetworkReply* reply){
    QByteArray response_data=reply->readAll();
    qDebug() << "ktili:" +response_data;

    if(response_data == "\"Account not found\""){
        qDebug() << "Kryptotiliä ei löytynyt";
        cryptoaccount = "404";
    }else{
        cryptoaccount = response_data;
    }

    cryptoManager->deleteLater();
    cryptoReply->deleteLater();
    reply->deleteLater();

}

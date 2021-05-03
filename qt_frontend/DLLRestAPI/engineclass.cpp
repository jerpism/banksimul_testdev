#include "engineclass.h"

EngineClass::EngineClass()
{
    credentials="admin:1234";
    url = "https://91.145.117.152:3443";
    //Asetetaan salattua yhteyttä varten tarvittavat asetukset
    config = QSslConfiguration::defaultConfiguration();
    //Tarvitaan, koska palvelimella on käytössä oma SSL cert.
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    networkManager = new QNetworkAccessManager;

}

EngineClass::~EngineClass()
{

}

void EngineClass::logout(){
   cardid = "";
   account = "";
   cryptoaccount = "";
   name = "";
   phone = "";
   addr = "";
}

void EngineClass::login(QString card, QString pin){
    //Alussa asetetaan pyyntöä varten tarvittavat tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id", card);
    json_obj.insert("pin", pin);

    //Asetetaan kortin id muuttujaan valmiiksi, jotta sitä voidaan käytätä myöhemmin
    cardid = card;

    //Luodaan uusi pyyntö ja asetetaan siihen tarvittavat headerit
    QNetworkRequest request(url+"/login");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö ja liitetään se slottiin loginSlot
    loginReply = networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(loginReply, SIGNAL(finished()), this, SLOT(loginSlot()));
}

void EngineClass::loginSlot(){
    QByteArray response_data = loginReply->readAll();
    qDebug() << "login vastaus: " + response_data;

    /* Jos palvelin vastaa TRUE tilinumeron ja pin-koodin vertaukseen
     * lähetetään pääohjelmalle signaali, että kirjautuminen onnistui */
    if(response_data == "true"){
        this->setAccount(cardid);
        this->setCryptoAccount(cardid);
        this->getInfo();
        emit loginSignal(true);
    }else{
    //Jos palvelin taas vastaa FALSE, niin kerrotaan pääohjelmalle, että kirjautuminen ei onnistunut
        this->logout();
        emit loginSignal(false);
    }

    loginReply->deleteLater();

}


double EngineClass::getBalance()
{
    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/account/getBalance/"+account);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Luodaan tapahtumasilmukka
    QEventLoop loop;

    //Lähetetään GET pyyntö
    balanceReply = networkManager->get(request);

    //Yhdistetään pyynnön finished() silmukan poistumiseen
    connect(balanceReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //Luetaan vastaus
    QString response = balanceReply->readAll();
    qDebug() << "balance vastaus: "+response;

    balanceReply->deleteLater();

    //Palautetaan vastaus kutsujalle doubleksi muunnettuna
    return response.toDouble();
}


void EngineClass::setAccount(QString card){
   QNetworkRequest request(url+"/card/getAccount/"+card);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());

   //Lähetetään GET pyyntö ja yhdistetään se slottiin accSlot
   accReply = networkManager->get(request);
   connect(accReply, SIGNAL(finished()), this, SLOT(accSlot()));
}


void EngineClass::accSlot(){
    QByteArray response_data=accReply->readAll();
//    qDebug() << accReply->error();
    qDebug() << "tili:"+response_data;
    if(response_data == "\"Account not found\""){
        qDebug() << "Tiliä ei löytynyt";
//        emit errorSignal("Tiliä ei ole");
        account = "";
    }else{
        account = response_data;
    }

    accReply->deleteLater();
}


void EngineClass::setCryptoAccount(QString card){
   //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
   QNetworkRequest request(url+"/card/getCryptoAccount/"+card);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());

   //Lähetetään GET pyyntö ja yhdistetään se slottiin cryptoSlot
   cryptoAccReply = networkManager->get(request);
   connect(cryptoAccReply, SIGNAL(finished()), this, SLOT(cryptoAccSlot()));
}


void EngineClass::cryptoAccSlot(){
    QByteArray response_data=cryptoAccReply->readAll();
    qDebug() << "ktili:" +response_data;

    if(response_data == "\"Account not found\""){
        qDebug() << "Kryptotiliä ei löytynyt";
        cryptoaccount = "";
    }else{
        cryptoaccount = response_data;
    }

    cryptoAccReply->deleteLater();
}


double EngineClass::getCryptoBalance(){
    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/cryptoaccount/getBalance/"+cryptoaccount);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään pyyntö
    cryptoBalanceReply = networkManager->get(request);

    //Odotetaan silmukassa kunnes saadaan finished() signaali pyynnöltä
    QEventLoop loop;
    connect(cryptoBalanceReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //Luetaan vastaus
    QString response = cryptoBalanceReply->readAll();
    qDebug() << "cryptobalance vastaus: "+response;

    cryptoBalanceReply->deleteLater();

    //Palautetaan vastaus kutsujalle doubleksi muunettuna
    return response.toDouble();
}

bool EngineClass::accountExists(QString account){
    QNetworkRequest request(url+"/account/exists/"+account);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    existsReply = networkManager->get(request);

    QEventLoop loop;
    connect(existsReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray response_data = existsReply->readAll();
    qDebug() << response_data;

    existsReply->deleteLater();

    if(response_data == "true"){
        return true;
    }else{
        return false;
    }


}

void EngineClass::withdrawMoney(QString amount){
    //Asetetaan tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id", account);
    json_obj.insert("amount", amount);

    //Haetaan saldo
    double saldo = this->getBalance();

    /* Virhe, jos käyttäjä onnistuu
     * lähettämään negatiivisen nostopyynnön
     * Estetään myös palvelimen puolella */
    if(amount.toDouble() < 0){
        emit errorSignal("Et voi nostaa negatiivisia summia");
    }else if(saldo - amount.toDouble() < 0 ){
        emit errorSignal("Tilillä ei ole tarpeeksi rahaa");
    }else{

    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/account/withdraw_action");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö
    withdrawReply=networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(withdrawReply, SIGNAL(finished()), this, SLOT(withdrawSlot()));

    }
}


void EngineClass::withdrawSlot()
{
    QByteArray response_data=withdrawReply->readAll();
    qDebug() << "vastaus: " +response_data;

    if(response_data.toInt() < 1){
       emit errorSignal("Nosto epäonnistui");
    }else{
      emit successSignal("Nosto onnistui");
    }
    withdrawReply->deleteLater();
}


double EngineClass::getRate(){
    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/rates/getRate/");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään pyyntö
    rateReply = networkManager->get(request);

    //Odotetaan silmukassa kunnes saadaan finished() signaali pyynnöltä
    QEventLoop loop;
    connect(rateReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //Luetaan vastaus
    QString response = rateReply->readAll();
    qDebug() << "rates vastaus: "+response;

    rateReply->deleteLater();

    //Palautetaan vastaus kutsujalle doubleksi muunnettuna
    return response.toDouble();
}


void EngineClass::buyCrypto(QString amount){
    //Asetetaan pyyntöä varten tarvittavat tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id_acc", account);
    json_obj.insert("id_crypto", cryptoaccount);
    json_obj.insert("amount", amount);

    /* Annetaan virhe, jos käyttäjä onnistuu jotenkin
     * lähettämään ostopyynnön negatiivisellä summalla.
     * Tämä estetään myös palvelimen puolella */
    if(amount.toDouble() < 0){
        emit errorSignal("Et voi ostaa negatiivisia summia");
    }else{

    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/cryptoAccount/buy_crypto");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö
    cryptoReply=networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(cryptoReply, SIGNAL(finished()), this, SLOT(cryptoSlot()));
    }

}


void EngineClass::sellCrypto(QString amount){
    //Asetetaan pyyntöä varten tarvittavat tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id_acc", account);
    json_obj.insert("id_crypto", cryptoaccount);
    json_obj.insert("amount", amount);

    /* Annetaan virhe jos käyttäjä onnistuu
     * lähettämään myyntipyynnön negatiiviselle summalle
     * Estetään myös palvelimen puolella. */
    if(amount.toDouble() < 0){
//        emit errorSignal("Et voi myydä negatiivisia määriä");
    }else{

    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/cryptoAccount/sell_crypto");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö
    cryptoReply=networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(cryptoReply, SIGNAL(finished()), this, SLOT(cryptoSlot()));
    }

}


void EngineClass::cryptoSlot(){
   QByteArray response_data = cryptoReply->readAll();
   qDebug() << "Krypton oston data: " + response_data;
   if(response_data.toInt() > 1 && response_data.toInt() <=5){
       emit successSignal("Krypton vaihto onnistui");
   }else{
       emit errorSignal("Krypton vaihdossa oli virhe");
   }

   cryptoReply->deleteLater();
}


void EngineClass::transferMoney(QString recipient, QString amount){
    //Asetetaan pyyntöä varten tarvittavat tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id_sender", account);
    json_obj.insert("id_recipient", recipient);
    json_obj.insert("amount", amount);

    //Asetetaan tilin saldo muuttujaan
    double saldo = this->getBalance();

    /* Annetaan virhe, jos käyttäjä onnistuu
     * jotenkin lähettämään pyynnön negatiivisen summan
     * nostolle, ei pitäisi tapahtua ja estetään myös
     * tietokannan puolella, mutta vielä varmuuden vuoksi tässäkin */
    if(amount.toDouble() < 0){
 //       emit errorSignal("Et voi siirtää negatiivisia summia");
    //Annetaan virhe, jos siirrettävä summa ylittää tilin saldon
    }else if(saldo - amount.toDouble() < 0 ){
//        emit errorSignal("Tilillä ei ole tarpeeksi rahaa");
    }else{

    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/account/transfer_action");
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö
    transferReply = networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(transferReply, SIGNAL(finished()), this, SLOT(transferSlot()));

    }
}

void EngineClass::transferSlot(){
    QByteArray response_data=transferReply->readAll();
    qDebug() << response_data;

    if(response_data == "" || response_data.toInt() <= 0){
  //     emit errorSignal("Siirto ei onnistunut");
    }else{
   //    emit successSignal("Siirto onnistui");
    }

    transferReply->deleteLater();
}

void EngineClass::getInfo()
{
   QNetworkRequest request(url+"/customer/getInfo/"+cardid);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());

   infoReply = networkManager->get(request);
//   QEventLoop loop;
   connect(infoReply, SIGNAL(finished()), this, SLOT(infoSlot()));
//   loop.exec();

}

void EngineClass::infoSlot(){
   QByteArray response_data = infoReply->readAll();

   QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
   QJsonObject json_obj=json_doc.object();
   name=json_obj["fullname"].toString();
   addr=json_obj["address"].toString();
   phone=json_obj["phone"].toString();
   qDebug() << name;

   emit gotInfo();
   qDebug() << "gotInfo";

   infoReply->deleteLater();
}

QString EngineClass::getName(){
    return name;
}

QString EngineClass::getAddr(){
    return addr;
}

QString EngineClass::getPhone(){
    return phone;
}

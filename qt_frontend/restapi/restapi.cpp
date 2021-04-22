#include "restapi.h"

Restapi::Restapi()
{
    credentials="admin:1234";
    url = "https://91.145.117.152:3443";
    //Asetetaan salattua yhteyttä varten tarvittavat asetukset
    config = QSslConfiguration::defaultConfiguration();
    //Tarvitaan, koska palvelimella on käytössä oma SSL cert.
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    networkManager = new QNetworkAccessManager;
}

Restapi::~Restapi()
{
    credentials = "";
    url = "";
    delete networkManager;
    networkManager = nullptr;
}

void Restapi::login(QString card, QString pin){
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

void Restapi::logout(){
   //Asetetaan tilimuuttujat tyhjiksi
   cardid= "";
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

   //Lähetetään GET pyyntö ja yhdistetään se slottiin accSlot
   accReply = networkManager->get(request);
   connect(accReply, SIGNAL(finished()), this, SLOT(accSlot()));
}

void Restapi::setCryptoAccount(QString card){
   //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
   QNetworkRequest request(url+"/card/getCryptoAccount/"+card);
   request.setSslConfiguration(config);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   QByteArray data = credentials.toLocal8Bit().toBase64();
   QString headerData = "Basic " + data;

   request.setRawHeader("Authorization", headerData.toLocal8Bit());

   //Lähetetään GET pyyntö ja yhdistetään se slottiin cryptoSlot
   cryptoReply = networkManager->get(request);
   connect(cryptoReply, SIGNAL(finished()), this, SLOT(cryptoSlot()));
}

void Restapi::transferMoney(QString recipient, QString amount){
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
        emit errorSignal("Et voi siirtää negatiivisia summia");
    //Annetaan virhe, jos siirrettävä summa ylittää tilin saldon
    }else if(saldo - amount.toDouble() < 0 ){
        emit errorSignal("Tilillä ei ole tarpeeksi rahaa");
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

void Restapi::buyCrypto(QString amount){
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
    convertCryptoReply=networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(convertCryptoReply, SIGNAL(finished()), this, SLOT(convertCryptoSlot()));
    }

}

void Restapi::sellCrypto(QString amount){
    //Asetetaan pyyntöä varten tarvittavat tiedot json objectiin
    QJsonObject json_obj;
    json_obj.insert("id_acc", account);
    json_obj.insert("id_crypto", cryptoaccount);
    json_obj.insert("amount", amount);

    /* Annetaan virhe jos käyttäjä onnistuu
     * lähettämään myyntipyynnön negatiiviselle summalle
     * Estetään myös palvelimen puolella. */
    if(amount.toDouble() < 0){
        emit errorSignal("Et voi myydä negatiivisia määriä");
    }else{

    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/cryptoAccount/sell_crypto");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään POST pyyntö
    convertCryptoReply=networkManager->post(request, QJsonDocument(json_obj).toJson());
    connect(convertCryptoReply, SIGNAL(finished()), this, SLOT(convertCryptoSlot()));
    }

}

double Restapi::getBalance(){
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

double Restapi::getRate(){
    //Luodaan pyyntö ja asetetaan siihen tarvittavat tiedot
    QNetworkRequest request(url+"/rates/getRate/");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    //Lähetetään pyyntö
    ratesReply = networkManager->get(request);

    //Odotetaan silmukassa kunnes saadaan finished() signaali pyynnöltä
    QEventLoop loop;
    connect(ratesReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //Luetaan vastaus
    QString response = ratesReply->readAll();
    qDebug() << "rates vastaus: "+response;

    ratesReply->deleteLater();

    //Palautetaan vastaus kutsujalle doubleksi muunnettuna
    return response.toDouble();
}

double Restapi::getCryptoBalance(){
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
    qDebug() << "balance vastaus: "+response;

    cryptoBalanceReply->deleteLater();

    //Palautetaan vastaus kutsujalle doubleksi muunettuna
    return response.toDouble();
}

void Restapi::withdrawMoney(QString amount){
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

void Restapi::loginSlot(){
    QByteArray response_data = loginReply->readAll();
    qDebug() << "login vastaus: " + response_data;

    /* Jos palvelin vastaa TRUE tilinumeron ja pin-koodin vertaukseen
     * lähetetään pääohjelmalle signaali, että kirjautuminen onnistui */
    if(response_data == "true"){
        this->setAccount(cardid);
        this->setCryptoAccount(cardid);
        emit loginSignal(true);
    }else{
    //Jos palvelin taas vastaa FALSE, niin kerrotaan pääohjelmalle, että kirjautuminen ei onnistunut
        this->logout();
        emit loginSignal(false);
    }

    loginReply->deleteLater();

}

void Restapi::withdrawSlot()
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


void Restapi::transferSlot(){
    QByteArray response_data=transferReply->readAll();
    qDebug() << response_data;

    if(response_data == ""){
       emit errorSignal("Siirto ei onnistunut");
    }else{
       emit successSignal("Siirto onnistui");
    }

    transferReply->deleteLater();
}

void Restapi::convertCryptoSlot(){
   QByteArray response_data = convertCryptoReply->readAll();
   qDebug() << "Krypton oston data: " + response_data;
   if(response_data.toInt() > 1 && response_data.toInt() <=5){
       emit successSignal("Krypton vaihto onnistui");
   }else{
       emit errorSignal("Krypton vaihdossa oli virhe");
   }

   convertCryptoReply->deleteLater();
}

void Restapi::accSlot(){
    QByteArray response_data=accReply->readAll();
//    qDebug() << accReply->error();
    qDebug() << response_data;
    if(response_data == "\"Account not found\""){
        qDebug() << "Tiliä ei löytynyt";
//        emit errorSignal("Tiliä ei ole");
        account = "";
    }else{
        account = response_data;
    }

    accReply->deleteLater();

}

void Restapi::cryptoSlot(){
    QByteArray response_data=cryptoReply->readAll();
    qDebug() << "ktili:" +response_data;

    if(response_data == "\"Account not found\""){
        qDebug() << "Kryptotiliä ei löytynyt";
        cryptoaccount = "";
    }else{
        cryptoaccount = response_data;
    }

    cryptoReply->deleteLater();
}

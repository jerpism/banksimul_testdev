#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    credentials="admin:1234";
    url = "http://91.145.117.152:3000";
    objectRestapi = new Restapi;
    connect(objectRestapi, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectRestapi;
    ui = nullptr;
    objectRestapi = nullptr;
}

void MainWindow::errorSlot(QString virhe){
    qDebug() << "Virhe otettu vastaan: " + virhe;
    ui->virheLabel->setText(virhe);
    ui->lineEdit->setText("");
}

/*double MainWindow::getBalance(){
    tili = ui->accLineEdit->text();
    QNetworkRequest request(url+"/account/getBalance/"+tili);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    balanceManager = new QNetworkAccessManager(this);
    QEventLoop loop;
    balanceReply = balanceManager->get(request);
    connect(balanceReply, SIGNAL(finished()), &loop, SLOT(quit()));
    qDebug() << "ennen looppia";
    loop.exec();
    qDebug() << "loopin jälkeen";
    QString response = balanceReply->readAll();
    qDebug() << response;
    balanceReply->deleteLater();
    balanceManager->deleteLater();

    return response.toDouble();
}*/

void MainWindow::on_pushButton_clicked()
{
   double saldo = objectRestapi->getBalance();

  ui->lineEdit->setText(QString::number(saldo, 'f', 2));

}


void MainWindow::on_nostaButton_clicked()
{
    QString amount = ui->nostoLineEdit->text();
/*    QJsonObject json_obj;
    json_obj.insert("id", tili);
    json_obj.insert("amount", amount);
    double saldo = getBalance();

    if(saldo-amount.toDouble() < 0){
        ui->virheLabel->setText("Tilillä ei ole tarpeeksi rahaa");
    }else{

    QNetworkRequest request(url+"/account/withdraw_action");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));
    withdrawReply=withdrawManager->post(request, QJsonDocument(json_obj).toJson());

    }*/

    objectRestapi->withdrawMoney(amount);

}

void MainWindow::withdrawSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;

    ui->virheLabel->setText("Nosto toimitettiin");

    withdrawManager->deleteLater();
    withdrawReply->deleteLater();
    reply->deleteLater();

}

void MainWindow::on_cardPushButton_clicked()
{
   objectRestapi->setAccount(ui->cardLineEdit->text());
}

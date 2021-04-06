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

    QTimer::singleShot(10000, this, [&]() { ui->virheLabel->setText("");});
}



void MainWindow::on_pushButton_clicked()
{
   double saldo = objectRestapi->getBalance();

  ui->lineEdit->setText(QString::number(saldo, 'f', 2));

}


void MainWindow::on_nostaButton_clicked()
{
    QString amount = ui->nostoLineEdit->text();
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

void MainWindow::on_siirtoPushButton_clicked()
{
    QString vastaanottaja = ui->accLineEdit->text();
    QString maara = ui->transferLineEdit->text();
    objectRestapi->transferMoney(vastaanottaja, maara);
}

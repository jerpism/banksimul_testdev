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
    timer = new QTimer(this);
    connect(objectRestapi, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(objectRestapi, SIGNAL(successSignal(QString)), this, SLOT(successSlot(QString)));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectRestapi;
    ui = nullptr;
    objectRestapi = nullptr;
}

void MainWindow::successSlot(QString response){
   ui->stackedWidget->setCurrentIndex(4);
   ui->successlabel->setText(response);
   QTimer::singleShot(5000, this, SLOT(returnToMenu()));

}

void MainWindow::errorSlot(QString virhe){
    qDebug() << "Virhe otettu vastaan: " + virhe;
    ui->virheLabel->setText(virhe);

    QTimer::singleShot(10000, this, [&]() { ui->virheLabel->setText("");});
}

void MainWindow::startIdleTimer(){
   connect(timer, SIGNAL(timeout()), this, SLOT(returnToMenu()));
   timer->start(10000);
}

void MainWindow::startMenuIdleTimer(){
   connect(timer, SIGNAL(timeout()), this, SLOT(returnToLogin()));
   timer->start(30000);
}

void MainWindow::stopIdleTimer(){
    timer->stop();
}

void MainWindow::returnToMenu(){
    stopIdleTimer();
    ui->stackedWidget->setCurrentIndex(1);
    startMenuIdleTimer();
}

void MainWindow::returnToLogin(){
   timer->stop();
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_closePushButton_clicked()
{
    returnToMenu();
}

void MainWindow::on_nosta20Button_clicked()
{
    objectRestapi->withdrawMoney("20");
    startIdleTimer();
}

void MainWindow::on_nosta40Button_clicked()
{
    objectRestapi->withdrawMoney("40");

}

void MainWindow::on_nosta60Button_clicked()
{
    objectRestapi->withdrawMoney("60");

}

void MainWindow::on_nosta100Button_clicked()
{
    objectRestapi->withdrawMoney("100");
}

void MainWindow::on_nosta200Button_clicked()
{
    objectRestapi->withdrawMoney("200");

}

void MainWindow::on_nosta500Button_clicked()
{
    objectRestapi->withdrawMoney("500");
}

void MainWindow::on_closeNostoPushButton_clicked()
{
    returnToMenu();
}

void MainWindow::on_startNostoPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
   startIdleTimer();
//   QTimer::singleShot(10000, this, SLOT(returnToMenu()));
}


void MainWindow::on_loginPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
   objectRestapi->setAccount(ui->loginLineEdit->text());
   objectRestapi->setCryptoAccount(ui->loginLineEdit->text());
}

void MainWindow::on_startSiirtoPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
   startIdleTimer();
}

void MainWindow::on_transferButton_clicked()
{
   objectRestapi->transferMoney(ui->recipientLineEdit->text(), ui->transferAmountLineEdit->text());
}

void MainWindow::on_startTestPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    startIdleTimer();
}

void MainWindow::on_buyCryptoPushButton_clicked()
{
   objectRestapi->buyCrypto(ui->buyCryptoLineEdit->text());

}

void MainWindow::on_sellCryptoPushButton_clicked()
{
   objectRestapi->sellCrypto(ui->sellCryptoLineEdit->text());
}

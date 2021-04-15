#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    credentials="admin:1234";
    url = "https://91.145.117.152:3000";
    objectRestapi = new Restapi;
    timer = new QTimer(this);
    connect(objectRestapi, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(objectRestapi, SIGNAL(successSignal(QString)), this, SLOT(successSlot(QString)));
    connect(objectRestapi, SIGNAL(loginSignal(bool)), this, SLOT(loginSlot(bool)));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectRestapi;
    ui = nullptr;
    objectRestapi = nullptr;
}

void MainWindow::loginSlot(bool response){
   if(response ==true){
       ui->stackedWidget->setCurrentIndex(1);
       objectRestapi->setAccount(ui->loginLineEdit->text());
       objectRestapi->setCryptoAccount(ui->loginLineEdit->text());
   }else{
       qDebug() << "pröööh :D";
       ui->loginErrorLabel->setText("Prööh");
   }
}

void MainWindow::successSlot(QString response){
   ui->stackedWidget->setCurrentIndex(4);
   ui->successlabel->setText(response);
   QTimer::singleShot(5000, this, SLOT(returnToMenu()));

}

void MainWindow::errorSlot(QString virhe){
    qDebug() << "Virhe otettu vastaan: " + virhe;
   // int prevPage = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(8);
    ui->virheLabel->setText(virhe);

    if(virhe == "Tiliä ei ole")
        returnToLogin();
    else{
//    QTimer::singleShot(5000, this, [&]() { ui->stackedWidget->setCurrentIndex(prevPage);});
   QTimer::singleShot(5000, this, SLOT(returnToMenu()));
    }
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
   ui->loginLineEdit->setText("");
   ui->loginPinLineEdit->setText("");
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_closePushButton_clicked()
{
    returnToMenu();
}

void MainWindow::on_nosta20Button_clicked()
{
    objectRestapi->withdrawMoney("20");
    stopIdleTimer();
}

void MainWindow::on_nosta40Button_clicked()
{
    objectRestapi->withdrawMoney("40");
    stopIdleTimer();
}

void MainWindow::on_nosta60Button_clicked()
{
    objectRestapi->withdrawMoney("60");
    stopIdleTimer();
}

void MainWindow::on_nosta100Button_clicked()
{
    objectRestapi->withdrawMoney("100");
    stopIdleTimer();
}

void MainWindow::on_nosta200Button_clicked()
{
    objectRestapi->withdrawMoney("200");
    stopIdleTimer();
}

void MainWindow::on_nosta500Button_clicked()
{
    objectRestapi->withdrawMoney("500");
    stopIdleTimer();
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
   //ui->stackedWidget->setCurrentIndex(1);
   //objectRestapi->setAccount(ui->loginLineEdit->text());
   //objectRestapi->setCryptoAccount(ui->loginLineEdit->text());
   objectRestapi->login(ui->loginLineEdit->text(), ui->loginPinLineEdit->text());
   startMenuIdleTimer();
}

void MainWindow::on_startSiirtoPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
   startIdleTimer();
}

void MainWindow::on_transferButton_clicked()
{
   objectRestapi->transferMoney(ui->recipientLineEdit->text(), ui->transferAmountLineEdit->text());
   stopIdleTimer();
}

void MainWindow::on_startTestPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    startIdleTimer();
}

void MainWindow::on_buyCryptoPushButton_clicked()
{
   objectRestapi->buyCrypto(ui->buyCryptoLineEdit->text());
   stopIdleTimer();
}

void MainWindow::on_sellCryptoPushButton_clicked()
{
   objectRestapi->sellCrypto(ui->sellCryptoLineEdit->text());
   stopIdleTimer();
}

void MainWindow::on_exitCryptoPushButton_clicked()
{
   returnToMenu();
}

void MainWindow::on_buySelectPushButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(6);
  ui->balancelabel->setText("Tililläsi on: "+QString::number(objectRestapi->getBalance(), 'f', 2));
  startIdleTimer();
}

void MainWindow::on_sellSelectPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(7);
   ui->cryptobalancelabel->setText("Tililläsi on: "+QString::number(objectRestapi->getCryptoBalance(), 'f', 10));
   startIdleTimer();
}

void MainWindow::on_input1_clicked()
{
   ui->transferAmountLineEdit->setText(ui->transferAmountLineEdit->text()+"1");
   startIdleTimer();
}

void MainWindow::on_logoutPushButton_clicked()
{
   objectRestapi->logout();
   returnToLogin();

}

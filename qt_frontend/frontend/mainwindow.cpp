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
    ui->stackedWidget->setCurrentIndex(0);
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

void MainWindow::startIdleTimer(){
   connect(timer, SIGNAL(timeout()), this, SLOT(returnToMenu()));
   timer->start(10000);
}

void MainWindow::stopIdleTimer(){
    timer->stop();
}

void MainWindow::returnToMenu(){
    ui->stackedWidget->setCurrentIndex(0);
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

void MainWindow::on_startTestPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_closePushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    stopIdleTimer();
}

void MainWindow::on_nosta20Button_clicked()
{
    objectRestapi->withdrawMoney("20");
//    stopIdleTimer();
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
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_startNostoPushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
   startIdleTimer();
//   QTimer::singleShot(10000, this, SLOT(returnToMenu()));
}


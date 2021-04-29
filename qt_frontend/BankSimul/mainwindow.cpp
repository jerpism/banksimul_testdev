#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objectDLLRestAPI = new DLLRestAPI;
    timer = new QTimer(this);
    connect(objectDLLRestAPI, SIGNAL(infoReceived()), this, SLOT(receivedInfoSlot()));
    connect(objectDLLRestAPI, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(objectDLLRestAPI, SIGNAL(successSignal(QString)), this, SLOT(successSlot(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectDLLRestAPI;
    delete timer;
    ui=nullptr;
    objectDLLRestAPI=nullptr;
    timer=nullptr;
}

void MainWindow::startIdleTimer()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(returnToMenu()));
    timer->start(10000);
    qDebug() << "IdleTimer aloitettu";
}

void MainWindow::startMenuIdleTimer()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(logout()));
    timer->start(30000);
    qDebug() << "MenuIdleTimer aloitettu";
}

void MainWindow::stopTimer()
{
    timer->stop();
    qDebug() << "Ajastin pysäytetty";
}

void MainWindow::logout()
{
    stopTimer();
    objectDLLRestAPI->logout();
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::receivedInfoSlot()
{
   ui->menulabel->setText("Tervetuloa "+objectDLLRestAPI->getName());

}

void MainWindow::errorSlot(QString response)
{
    qDebug() << "VIRHE: "+response;

}

void MainWindow::successSlot(QString response)
{
    qDebug() << "ONNISTUI: "+response;

}

void MainWindow::returnToMenu()
{
    ui->stackedWidget->setCurrentIndex(1);
    stopTimer();
    startMenuIdleTimer();
}

/* Sivuindeksit
 * 0 Kirjautuminen
 * 1 Menu
 * 2 Nosto
 * */

void MainWindow::on_loginButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
   objectDLLRestAPI->login("06000641D4", "1234");
   startMenuIdleTimer();
}

void MainWindow::on_withdrawButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
   ui->withdrawLabel->setText("Tililläsi on "+objectDLLRestAPI->getBalance()+" euroa\n\n"
                              "Valitse nostettava summa");
   stopTimer();
   startIdleTimer();
}

void MainWindow::on_withdrawReturnButton_clicked()
{
    returnToMenu();
}

void MainWindow::on_withdraw20Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("20");
   stopTimer();
}

void MainWindow::on_logoutButton_clicked()
{
   logout();
}

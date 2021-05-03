#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objectDLLRestAPI = new DLLRestAPI;
    timer = new QTimer(this);

    /* lineEditit
     * 0 login
     * 1 osta kryptoa
     * 2 myy kryptoa
     * 3 tilisiirto tilinr
     * 4 tilisiirto määrä
     */
    lineEdits.append(ui->loginLineEdit);
    lineEdits.append(ui->buyCryptoLineEdit);
    lineEdits.append(ui->sellCryptoLineEdit);
    lineEdits.append(ui->transferLineEdit);
    lineEdits.append(ui->transferAmountLineEdit);

    connect(objectDLLRestAPI, SIGNAL(infoReceived()), this, SLOT(receivedInfoSlot()));
    connect(objectDLLRestAPI, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(objectDLLRestAPI, SIGNAL(successSignal(QString)), this, SLOT(successSlot(QString)));
    ui->keypad->show();
    lineEditFocus = 0; //Aseta näppäimistö toimimaan kirjautumisnäytön lineEdittiin
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

void MainWindow::clearLineEdits()
{
    foreach(QLineEdit* lineEdit, lineEdits){
        lineEdit->setText("");
    }

}

void MainWindow::logout()
{
    stopTimer();
    objectDLLRestAPI->logout();
    ui->stackedWidget->setCurrentIndex(0);
    ui->keypad->show();
    clearLineEdits();
}
void MainWindow::receivedInfoSlot()
{
   ui->menulabel->setText("Tervetuloa "+objectDLLRestAPI->getName());

}

void MainWindow::errorSlot(QString response)
{
    qDebug() << "VIRHE: "+response;
    ui->errorLabel->setText(response);
    ui->keypad->hide();
    ui->stackedWidget->setCurrentIndex(9);
    QTimer::singleShot(10000, this, SLOT(returnToMenu()));

}

void MainWindow::successSlot(QString response)
{
    qDebug() << "ONNISTUI: "+response;
    ui->successLabel->setText(response);
    ui->keypad->hide();
    ui->stackedWidget->setCurrentIndex(8);
    QTimer::singleShot(5000, this, SLOT(returnToMenu()));

}

void MainWindow::returnToMenu()
{
    ui->keypad->hide();
    ui->stackedWidget->setCurrentIndex(1);
    stopTimer();
    startMenuIdleTimer();
    clearLineEdits();
}

/* Sivuindeksit
 * 0 Kirjautuminen
 * 1 Menu
 * 2 Nosto
 * 3 Kryptomenu
 * 4 Osta kryptoa
 * 5 Myy kryptoa
 * 6 tilisiirto 1
 * 7 tilisiirto 2
 * 8 onnistuminen
 * 9 virhe
 * */

void MainWindow::on_loginButton_clicked()
{
   ui->keypad->hide();
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

void MainWindow::on_withdraw40Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("40");
   stopTimer();

}

void MainWindow::on_withdraw60Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("60");
   stopTimer();
}

void MainWindow::on_withdraw100Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("100");
   stopTimer();

}

void MainWindow::on_withdraw200Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("200");
   stopTimer();

}

void MainWindow::on_withdraw500Button_clicked()
{
   objectDLLRestAPI->withdrawMoney("500");
   stopTimer();
}

void MainWindow::on_logoutButton_clicked()
{
   logout();
   lineEditFocus = 0;//Aseta näppäimistö kirjautumisnäytön lineEdittiin
}


void MainWindow::handleClick()
{
    QObject *sender = QObject::sender();
    qDebug() << sender->objectName();
    QStringList nappi = sender->objectName().split('_');

    QString teksti = lineEdits[lineEditFocus]->text();

    if(nappi.at(1) == "bk"){
        teksti.chop(1);
    }else if(nappi.at(1) == "decimal"){
        teksti.append(".");
    }else{
        teksti.append(nappi.at(1));
    }

    if(ui->stackedWidget->currentIndex() != 0){
        startIdleTimer();
    }

    lineEdits[lineEditFocus]->setText(teksti);
}

void MainWindow::on_kp_0_clicked()
{
    this->handleClick();
}

void MainWindow::on_kp_1_clicked()
{
    this->handleClick();
}


void MainWindow::on_kp_2_clicked()
{
   this->handleClick();

}

void MainWindow::on_kp_3_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_4_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_5_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_6_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_7_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_8_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_9_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_decimal_clicked()
{
   this->handleClick();
}

void MainWindow::on_kp_bk_clicked()
{
   this->handleClick();
}

void MainWindow::on_cryptoCurrencyButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
   stopTimer();
   startIdleTimer();
   ui->keypad->hide();
}

void MainWindow::on_selectBuyCryptoButton_clicked()
{
   ui->cryptoBuyLabel->setText("Tililläsi on "+objectDLLRestAPI->getBalance()+" euroa\n"
                                "Kryptovaluutan kurssi on 1€ = "+objectDLLRestAPI->getRate());
   ui->stackedWidget->setCurrentIndex(4);
   ui->keypad->show();
   stopTimer();
   startIdleTimer();
   lineEditFocus = 1; //Aseta näppäimistö toimimaan krypton ostossa.
}

void MainWindow::on_cryptoMenuReturnButton_clicked()
{
   this->returnToMenu();
}

void MainWindow::on_buyCryptoReturnButton_clicked()
{
   ui->keypad->hide();
   ui->stackedWidget->setCurrentIndex(3);
   stopTimer();
   startIdleTimer();
   clearLineEdits();
}


void MainWindow::on_buyCryptoButton_clicked()
{
   objectDLLRestAPI->buyCrypto(ui->buyCryptoLineEdit->text());
   stopTimer();
}

void MainWindow::on_selectSellCryptoButton_clicked()
{
   ui->cryptoSellLabel->setText("Tililläsi on "+objectDLLRestAPI->getCryptoBalance()+" kryptovaluuttaa\n"
                                "Kryptovaluutan kurssi on 1 = "+objectDLLRestAPI->getRate()+"€");
   ui->stackedWidget->setCurrentIndex(5);
   ui->keypad->show();
   stopTimer();
   startIdleTimer();
   lineEditFocus = 2; //Aseta näppäimistö toimimaan krypton myynnissä.
}

void MainWindow::on_sellCryptoReturnButton_clicked()
{
   ui->keypad->hide();
   ui->stackedWidget->setCurrentIndex(3);
   stopTimer();
   startIdleTimer();
   clearLineEdits();
}

void MainWindow::on_transferButton_clicked()
{
   ui->keypad->show();
   ui->stackedWidget->setCurrentIndex(6);
   lineEditFocus = 3;
   startIdleTimer();
}

void MainWindow::on_transferReturnButton_clicked()
{
   returnToMenu();
}

void MainWindow::on_transferPushButton_clicked()
{
  if(objectDLLRestAPI->accountExists(ui->transferLineEdit->text())){
     ui->stackedWidget->setCurrentIndex(7);
     ui->transferAmountLabel->setText("Syötä siirrettävä rahasumma\n"
                                      "Tililläsi on "+objectDLLRestAPI->getBalance()+"€");
     ui->keypad->show();
     startIdleTimer();
     lineEditFocus = 4;
  }else{
     ui->transferLabel->setText("Annettua tiliä ei ole olemassa!");
     QTimer::singleShot(10000, this, [&]() { ui->transferLabel->setText("Syötä vastaanottajan tilinumero");});
     startIdleTimer();
  }
}

void MainWindow::on_transferAmountReturnButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(6);
   lineEditFocus = 3;
   startIdleTimer();
}

void MainWindow::on_transferAmountButton_clicked()
{
   stopTimer();
   objectDLLRestAPI->transferMoney(ui->transferLineEdit->text(), ui->transferAmountLineEdit->text());
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dllrestapi.h"
#include "dllserialport.h"
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startIdleTimer();
    void startMenuIdleTimer();
    void stopTimer();
    void handleClick();
    void clearLineEdits();
    void openSerial();

private slots:
    void loginSlot(QString);
    void on_loginButton_clicked();

    void on_withdrawButton_clicked();

    void on_withdrawReturnButton_clicked();

    void on_withdraw20Button_clicked();

    void serialDataSlot(QString);
    void receivedInfoSlot();
    void errorSlot(QString);
    void successSlot(QString);
    void logout();
    void returnToMenu();

    void on_logoutButton_clicked();

    void on_kp_0_clicked();

    void on_kp_1_clicked();

    void on_kp_2_clicked();

    void on_kp_3_clicked();

    void on_kp_4_clicked();

    void on_kp_5_clicked();

    void on_kp_6_clicked();

    void on_kp_7_clicked();

    void on_kp_8_clicked();

    void on_kp_9_clicked();

    void on_kp_decimal_clicked();

    void on_kp_bk_clicked();

    void on_cryptoCurrencyButton_clicked();

    void on_selectBuyCryptoButton_clicked();

    void on_cryptoMenuReturnButton_clicked();

    void on_buyCryptoReturnButton_clicked();

    void on_withdraw40Button_clicked();

    void on_withdraw60Button_clicked();

    void on_withdraw100Button_clicked();

    void on_withdraw200Button_clicked();

    void on_withdraw500Button_clicked();

    void on_buyCryptoButton_clicked();

    void on_selectSellCryptoButton_clicked();

    void on_sellCryptoReturnButton_clicked();

    void on_transferButton_clicked();

    void on_transferReturnButton_clicked();

    void on_transferPushButton_clicked();

    void on_transferAmountReturnButton_clicked();

    void on_transferAmountButton_clicked();

    void on_sellCryptoButton_clicked();

    void on_showRecentButton_clicked();

    void on_actionsNewer_clicked();

    void on_actionsOlder_clicked();

    void on_actionsReturnButton_clicked();

    void on_showBalanceButton_clicked();

    void on_balanceReturnButton_clicked();

private:
    Ui::MainWindow *ui;
    DLLRestAPI *objectDLLRestAPI;
    DLLSerialport *objectDLLSerialport;
    QTimer *timer;
    QTimer *menuTimer;
    QList <QLineEdit*> lineEdits;
    QString card;
    short lineEditFocus;
    short n1;
    short failCount=0;
};
#endif // MAINWINDOW_H

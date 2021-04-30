#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dllrestapi.h"

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

private slots:
    void on_loginButton_clicked();

    void on_withdrawButton_clicked();

    void on_withdrawReturnButton_clicked();

    void on_withdraw20Button_clicked();

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

private:
    Ui::MainWindow *ui;
    DLLRestAPI *objectDLLRestAPI;
    QTimer *timer;
};
#endif // MAINWINDOW_H

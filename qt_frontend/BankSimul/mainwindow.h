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

private:
    Ui::MainWindow *ui;
    DLLRestAPI *objectDLLRestAPI;
    QTimer *timer;
};
#endif // MAINWINDOW_H

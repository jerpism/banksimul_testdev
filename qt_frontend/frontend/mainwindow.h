#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "restapi.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>
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
    void stopIdleTimer();
    void startMenuIdleTimer();
    void handleClick();

private slots:
    void returnToMenu();
    void returnToLogin();
    void successSlot(QString);
    void loginSlot(bool);

    void errorSlot(QString);

    void on_closePushButton_clicked();

    void on_nosta20Button_clicked();

    void on_nosta40Button_clicked();

    void on_nosta60Button_clicked();

    void on_nosta100Button_clicked();

    void on_nosta200Button_clicked();

    void on_nosta500Button_clicked();

    void on_closeNostoPushButton_clicked();

    void on_startNostoPushButton_clicked();

    void on_loginPushButton_clicked();

    void on_startSiirtoPushButton_clicked();

    void on_transferButton_clicked();

    void on_startTestPushButton_clicked();

    void on_buyCryptoPushButton_clicked();

    void on_sellCryptoPushButton_clicked();

    void on_exitCryptoPushButton_clicked();

    void on_buySelectPushButton_clicked();

    void on_sellSelectPushButton_clicked();

    void on_input1_clicked();

    void on_logoutPushButton_clicked();

    void on_kp_1_clicked();

    void on_kp_2_clicked();

    void on_kp_3_clicked();

    void on_kp_bk_clicked();

private:
    Ui::MainWindow *ui;
    QString credentials;
    QString tili;
    QString url;
    Restapi *objectRestapi;
    QTimer *timer;
    QList<QLineEdit *> lineEdits;
};
#endif // MAINWINDOW_H

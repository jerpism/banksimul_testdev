#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "restapi.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>

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

private slots:
    void returnToMenu();
    void returnToLogin();
    void successSlot(QString);

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

private:
    Ui::MainWindow *ui;
    QString credentials;
    QString tili;
    QString url;
    Restapi *objectRestapi;
    QTimer *timer;
};
#endif // MAINWINDOW_H

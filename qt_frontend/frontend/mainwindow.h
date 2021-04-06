#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "restapi.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
  //  double getBalance();
    void withdrawSlot(QNetworkReply *reply);

    void on_nostaButton_clicked();

    void on_cardPushButton_clicked();

    void errorSlot(QString);

    void on_siirtoPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString credentials;
    QString tili;
    QString url;
    Restapi *objectRestapi;


    QNetworkAccessManager *balanceManager;
    QNetworkReply *balanceReply;

    QNetworkAccessManager *withdrawManager;
    QNetworkReply *withdrawReply;

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <dll_loggedin.h>
#include <dll_endscene.h>
#include <withdraw.h>
#include "chooseaction.h"
#include <QSound>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const QByteArray &getToken() const;
    void setToken(const QByteArray &newToken);

private slots:
   // void getSerialInfo();
    void numberClickedHandler();
    void logOutAndClose();
    void EraseLoginRemoveClickhandler();
    void loginSlot (QNetworkReply *reply);
    void SendIdTiliSlot(QString tili, QString etunimi, QString sukunimi);
    void sendTiliandToken(QString tili, QByteArray token);
    void changeinfo(QString summa);


private:
    Ui::MainWindow *ui;
    chooseAction DLLchooseAction;
    DLL_loggedin DLLlogin;
    DLL_endscene DLLendscene;
    withdraw DLLwithdraw;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;

    QString portName;
    QString pin = NULL;
    QString fakePin;
    QString SerialInfo = NULL;
    int SerialBytes;
    QSound bts;
    void clearAll();
};
#endif // MAINWINDOW_H

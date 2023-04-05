#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <dll_loggedin.h>
#include <dll_endscene.h>
#include <chooseAction.h>


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

    chooseAction testi;

private slots:
    void getSerialInfo();
    void numberClickedHandler();

    void logOutAndClose();

    void EraseLoginRemoveClickhandler();

    void loginSlot (QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    DLL_loggedin DLLlogin;
    DLL_endscene DLLendscene;

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;
    QString portName;
    QString pin = NULL;
    QString fakePin;
    QString SerialInfo = NULL;
    int SerialBytes;
    void clearAll();
};
#endif // MAINWINDOW_H

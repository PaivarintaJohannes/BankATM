#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getSerialInfo();

    const QByteArray &getToken() const;
    void setToken(const QByteArray &newToken);

private slots:
    void numberClickedHandler();
    void EraseAndLoginClickhandler();

    void loginSlot (QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;

    QString pin;
    QString fakePin;
    QString SerialInfo = NULL;
    int SerialBytes;
};
#endif // MAINWINDOW_H

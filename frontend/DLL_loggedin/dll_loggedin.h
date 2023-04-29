#ifndef DLL_LOGGEDIN_H
#define DLL_LOGGEDIN_H

#include <QDialog>
#include <DLL_loggedin_global.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QSound>

namespace Ui {
class DLL_loggedin;
}

class DLL_loggedin : public QDialog
{
    Q_OBJECT

public:
    explicit DLL_loggedin(QWidget *parent = nullptr);
    ~DLL_loggedin();
    void setToken_idKortti(QByteArray, QString);

signals:
    void logOutClicked();
    void sendIdTili(QString,QString,QString);

private slots:
    void btnClickedHandler();
    void logOutClickedHandler();
    void tilisReplyFinished(QNetworkReply *reply);
    void omistajaSlot (QNetworkReply *reply);

private:
    void retrieveAndSetTilis();
    QString tili1;
    QString tili2;
    Ui::DLL_loggedin *ui;
    QByteArray token;
    QString idkortti;   
    QString etunimi;
    QString sukunimi;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;   
     QSound bts;
};

#endif // DLL_LOGGEDIN_H

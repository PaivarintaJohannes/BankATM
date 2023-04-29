#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QSound>

namespace Ui {
class withdraw;
}

class withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit withdraw(QWidget *parent = nullptr);
    ~withdraw();
    void settili_token(QString,QByteArray);
    void clearAll();

private:
    Ui::withdraw *ui;
    QString tili;
    QByteArray token;
    QString getBaseUrl();
    void getBalanceAndCredit(QString);
    QString summa;
    void makeWithdraw();
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QByteArray Response;
    QString Data;
    QByteArray response_data;
     QSound bts;

private slots:
    void ClickerHandler();
    void logOutClickerHandler();

signals:
    void logOutClicked();
    void sendSumma(QString);
};

#endif // WITHDRAW_H

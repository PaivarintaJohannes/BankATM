#ifndef DLL_ENDSCENE_H
#define DLL_ENDSCENE_H
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>

#include <QDialog>
#include <DLL_endscene_global.h>


namespace Ui {
class DLL_endscene;
}

class DLL_endscene : public QDialog
{
    Q_OBJECT

public:
    explicit DLL_endscene(QWidget *parent = nullptr);
    ~DLL_endscene();
    void getinfo(QString);
    QByteArray transportToken(QByteArray);
    void getTili(QString,QString,QString);
    void changeinfo(QString);
    void changetext();

private:
    Ui::DLL_endscene *ui;
    QString tili;
    QString etunimi;
    QString sukunimi;
    QByteArray tokenValue;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // DLL_ENDSCENE_H

#include "dll_endscene.h"
#include "ui_dll_endscene.h"
#include "enviroment.h"
#include <QDebug>
#include <QJsonDocument>


DLL_endscene::DLL_endscene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLL_endscene)

{

  ui->setupUi(this);

  QPixmap bkgnd("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/taustaa.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Window, bkgnd);
   this->setPalette(palette);

}

DLL_endscene::~DLL_endscene()
{
    delete ui;
}

//hakee saldo ja credit
void DLL_endscene::getinfo(QString balorcred)
{
    QString site_url=enviroment::getBaseUrl()+"/tili/"+tili+"/"+balorcred;
    QNetworkRequest request((site_url));

    QString web_token = tokenValue;
    request.setRawHeader("Authorization", ("Bearer " + web_token).toUtf8());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
            QJsonObject jsonObj = jsonDoc.object();

            float saldo = jsonObj["saldo"].toDouble();
            float credit = jsonObj["credit"].toDouble();
            QString saldoValue = QString::number(saldo);
            QString CreditValue = QString::number(credit);

        if(balorcred == "saldo"){
                ui->txtsaldo->setText("saldo: "+saldoValue+"€");
                //qDebug() << balorcred+": "<<response;
            }
            else if(balorcred == "credit"){
            ui->txtcredit->setText("credit: "+CreditValue+"€");
                //qDebug() << balorcred+": "<<response;
            }

        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}


QByteArray DLL_endscene::transportToken(QByteArray token)
{
    tokenValue = token;
    //qDebug()<<"tämän pitäis olla token: "<<token;
        return 0;
}

void DLL_endscene::getTili(QString a, QString b, QString c)
{
        tili = a;
        etunimi = b;
        sukunimi = c;
        //qDebug()<<tili;
}

void DLL_endscene::changeinfo(QString summa)
{
        ui->txtnosto->setText("Nostit "+summa+" euroa");
}

void DLL_endscene::changetext()
{
        ui->txtnosto->setText("Ei nostotapahtumia");
}

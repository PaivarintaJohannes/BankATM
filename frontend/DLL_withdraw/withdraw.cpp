#include "withdraw.h"
#include "ui_withdraw.h"
#include <QDebug>
#include <QJsonDocument>

withdraw::withdraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdraw),
  bts("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/button.wav")
{
    ui->setupUi(this);

   QPixmap bkgnd("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/taustaa.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    connect(ui->btn100e,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btn50e,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btn20e,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btn10e,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btnTeeNosto,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btnBack,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->btnLogOut,SIGNAL(clicked()),
            this,SLOT(logOutClickerHandler()),Qt::QueuedConnection);
}

withdraw::~withdraw()
{
    delete ui;
}

void withdraw::settili_token(QString a, QByteArray b)
{
    tili = a;
    token = b;
    getBalanceAndCredit("saldo");
    getBalanceAndCredit("credit");
}

void withdraw::getBalanceAndCredit(QString balOrCred)
{
        QString site_url=getBaseUrl()+"/tili/"+tili+"/"+balOrCred;
        QNetworkRequest request((site_url));

        QString web_token = token;
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

                if(balOrCred == "saldo"){
                    ui->labelSaldo->setText("saldo: "+saldoValue+"€");
                    //qDebug() << balOrCred+": "<<response;
                }
                else if(balOrCred == "credit"){
                    ui->labelCredit->setText("credit: "+CreditValue+"€");
                    //qDebug() << balOrCred+": "<<response;
                }

            } else {
                qDebug() << "Error: " << reply->errorString();
            }
            reply->deleteLater();
            manager->deleteLater();
        });
}


QString withdraw::getBaseUrl()
{
    return "http://localhost:3000";
}

void withdraw::ClickerHandler()
{
    bts.play();
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString name = button->objectName();
    if(name == "btn100e"){
        //qDebug() << "Button name:" << name;
        ui ->lineSumma->setText("100");
    }
    else if(name == "btn50e"){
        //qDebug() << "Button name:" << name;
        ui ->lineSumma->setText("50");
    }
    else if(name == "btn20e"){
        //qDebug() << "Button name:" << name;
        ui ->lineSumma->setText("20");
    }
    else if(name == "btn10e"){
        //qDebug() << "Button name:" << name;
        ui ->lineSumma->setText("10");
    }
    else if(name == "btnBack"){
        //qDebug() << "Button name:" << name;
        clearAll();
        close();
    }
    else if(name == "btnTeeNosto"){
        //qDebug() << "Button name:" << name;
        summa = ui->lineSumma->text();

        QString web_token = token;
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);

        // Set up the URL and request headers
        QUrl url(getBaseUrl() + "/tili/nosto/" + tili + "/" + summa);
        QNetworkRequest request(url);
        request.setAttribute(QNetworkRequest::CustomVerbAttribute, "PUT");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setRawHeader("Authorization", ("Bearer " + web_token).toUtf8());

        // Send the PUT request
        QNetworkReply* reply = manager->put(request, QByteArray());

        // Handle the response
        connect(reply, &QNetworkReply::finished, [=]() {
                    response_data=reply->readAll();
                    QString jsonString = QString::fromUtf8(response_data);
                    //qDebug()<<jsonString;
                    if (jsonString.contains("false")){
                        ui->labelNomoney->setText("Tilin kate ei riitä");
                    }
                    else {
                        if (summa != NULL){
                            clearAll();
                            emit sendSumma(summa);
                            emit logOutClicked();
                        }
                    }
                    reply->deleteLater();
                    manager->deleteLater();
                });

        //qDebug() <<reply;
        getBalanceAndCredit("saldo");
        getBalanceAndCredit("credit");
    }
}

void withdraw::clearAll()
{
    ui->lineSumma->clear();
    ui->labelSaldo->setText("Saldo:");
    ui->labelCredit->setText("Credit:");
    tili.clear();
}

void withdraw::logOutClickerHandler()
{
   bts.play();
    clearAll();
    emit logOutClicked();
    //qDebug()<<"logouttia painettu";
}


#include "dll_loggedin.h"

#include "ui_dll_loggedin.h"
#include <QDebug>


DLL_loggedin::DLL_loggedin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLL_loggedin),
   bts("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/button.wav")
{
    ui->setupUi(this);

   QPixmap bkgnd("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/taustaa.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Window, bkgnd);
   this->setPalette(palette);

    //qDebug()<<"dll olio luotu";

    connect(ui->btnTili1,SIGNAL(clicked()),
            this,SLOT(btnClickedHandler()),Qt::QueuedConnection);
    connect(ui->btnTili2,SIGNAL(clicked()),
            this,SLOT(btnClickedHandler()),Qt::QueuedConnection);
    connect(ui->btnLogOut,SIGNAL(clicked()),
            this,SLOT(logOutClickedHandler()),Qt::QueuedConnection);
}

DLL_loggedin::~DLL_loggedin()
{
    delete ui;
}

void DLL_loggedin::setToken_idKortti(QByteArray a, QString b)
{
   token=a;
   idkortti=b;
   //qDebug()<<"DLL-token > "+token;
   //qDebug()<<"DLL-idkortti(serialinfo) > "+idkortti;

   loginManager = new QNetworkAccessManager(this);
   connect(loginManager, SIGNAL(finished(QNetworkReply*)),
           this, SLOT(omistajaSlot(QNetworkReply*)));
   QUrl url("http://localhost:3000/omistaja/getbyid/" + idkortti);
   QNetworkRequest request(url);
   request.setRawHeader("Authorization", "Bearer " + token);
   loginManager->get(request);
    retrieveAndSetTilis();
}

void DLL_loggedin::btnClickedHandler()
{

    bts.play();

    QPushButton * button = qobject_cast<QPushButton*>(sender());
        QString text = button->text();
        if(text == tili1){
            //qDebug() << "Button name:" << text;
            emit sendIdTili(tili1,etunimi,sukunimi);
        }else if(text == tili2){
            //qDebug() << "Button name:" << text;
            emit sendIdTili(tili2,etunimi,sukunimi);
        }
}
void DLL_loggedin::retrieveAndSetTilis() {
    // Retrieve the tilis
    //qDebug()<<"tääl ollaa";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tilisReplyFinished(QNetworkReply*)));
    QUrl url("http://localhost:3000/tili/getbykortti/" + idkortti);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token);
    manager->get(request);

}
void DLL_loggedin::tilisReplyFinished(QNetworkReply *reply) {
    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray tilis = doc.array();

    // Set the button names
    if (tilis.size() >= 1) {
        QString idtili1 = tilis.at(0).toObject()["idtili"].toString();
        //qDebug()<<idtili1;
        ui->btnTili1->setText(idtili1);
        tili1 = idtili1;
    }
    if (tilis.size() >= 2) {
        QString idtili2 = tilis.at(1).toObject()["idtili"].toString();
        //qDebug()<<idtili2;
        tili2 = idtili2;
        ui->btnTili2->setText(idtili2);
    }
}
void DLL_loggedin::logOutClickedHandler()
{
    bts.play();
    emit logOutClicked();
}
void DLL_loggedin::omistajaSlot(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error: " << reply->errorString();
        return;
    }
    response_data = reply->readAll();
    reply->deleteLater();
    //qDebug()<<response_data;
    QJsonDocument doc = QJsonDocument::fromJson(response_data);
    QJsonArray arr = doc.array();
    QJsonObject obj = arr.at(0).toObject();
    etunimi = obj["etunimi"].toString();
    sukunimi = obj["sukunimi"].toString();
    //qDebug()<<etunimi;
    //qDebug()<<sukunimi;
    // Display owner's name in UI
    ui->label->setText("Tervetuloa " +etunimi + " " + sukunimi);
}

#include "chooseaction.h"
#include "transactions.h"
#include "ui_chooseaction.h"
#include <QDebug>
#include "enviroment.h"
#include <QJsonDocument>



chooseAction::chooseAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseAction),
   bts("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/button.wav")
{

    ui->setupUi(this);

   QPixmap bkgnd("C:/Users/Jorku/Desktop/BankATM/frontend/Äänet/taustaa.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Window, bkgnd);
   this->setPalette(palette);

    //Clicker handlers for buttons
    connect(ui->Withdraw,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->Transactions,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->Back,SIGNAL(clicked()),
            this,SLOT(ClickerHandler()),Qt::QueuedConnection);

    connect(ui->logOut,SIGNAL(clicked()),
            this,SLOT(logOutClickerHandler()),Qt::QueuedConnection);
}

chooseAction::~chooseAction()
{
    delete ui;
}

//Get the token from fronted (exe)
QByteArray chooseAction::transportToken(QByteArray token)
{
    tokenValue = token;
    return 0;
}

//Transport info from DLL_loggedin
void chooseAction::getTili(QString a, QString b, QString c)
{
    tili=a;
    etunimi=b;
    sukunimi=c;
    //qDebug()<<tili;
}

void chooseAction::clearAll()
{
    ui->Balance->clear();
    ui->Credit->clear();
    ui->listWidget->clear();
    tili.clear();
    etunimi.clear();
    sukunimi.clear();

}

void chooseAction::getBalanceAndCredit(QString balOrCred)
{
        //Determine url-endpoint
        QString site_url=Enviroment::getBaseUrl()+"/tili/"+tili+"/"+balOrCred;
        QNetworkRequest request((site_url));

        //Include web-token in the request
        QString web_token = tokenValue;
        request.setRawHeader("Authorization", ("Bearer " + web_token).toUtf8());

        //Create manager for reply
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(request);

        //Connect to database and check for errors
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
                    ui->Balance->setText(saldoValue+"€");
                    //qDebug() << balOrCred+": "<<response;
                }
                else if(balOrCred == "credit"){
                    ui->Credit->setText(CreditValue+"€");
                    //qDebug() << balOrCred+": "<<response;
                }

            } else {
                qDebug() << "Error: " << reply->errorString();
            }
            reply->deleteLater();
            manager->deleteLater();
        });
}

void chooseAction::getTransactions(QString showAll)
{
        //Determine url-endpoint
        QString site_url=Enviroment::getBaseUrl()+"/tilitapahtumat/getbytiliid/"+tili;
        QNetworkRequest request((site_url));

        //Include web-token in the request
        QString web_token = tokenValue;
        request.setRawHeader("Authorization", ("Bearer " + web_token).toUtf8());

        //Create manager for reply
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(request);

        //Connect to database and check for errors
        connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QString response = reply->readAll();

                //qDebug()<<"response: "<<response;
                QJsonDocument json_doc = QJsonDocument::fromJson(response.toUtf8());
                QJsonArray json_array = json_doc.array();
                QJsonObject json_obj = json_doc.object();
                QString data;
                //qDebug()<<data;

                foreach (const QJsonValue &value, json_array){
                    QJsonObject json_obj = value.toObject();
                    float summa = json_obj["summa"].toDouble();
                    QString summaValue = QString::number(summa);
                    QString aikaValue = json_obj["aika"].toString();
                    QString date =  aikaValue.left(10);
                    QString time =  aikaValue.right(15);
                    time =  time.mid(2,8);
                    //qDebug()<<summaValue;
                    data += "Päivämäärä:  "+ date +"    |    -"+ summaValue +"€\n";
                }

                //qDebug()<<data;
                if(showAll == "no"){
                    QStringList lines = data.split("\n");
                    QString lessData = lines.mid(0, 7).join("\n");;
                    ui->listWidget->addItem(lessData);
                }

                if(showAll == "yes"){
                    Transactions *objTransactions=new Transactions(this);
                    objTransactions->setMyData(data);
                    //qDebug()<<data;
                    objTransactions->open();
                    reply->deleteLater();
                    manager->deleteLater();
                }
            }
            else{
                qDebug() << "error in connecting to database: " << reply->errorString();
            }
        });
}

void chooseAction::ClickerHandler()
{
    bts.play();
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString name = button->objectName();

    if(name == "Withdraw"){
        //qDebug() << "Button name:" << name;
        emit nostaRahaaClicked(tili, tokenValue);

    }
    else if(name == "Transactions"){
        //qDebug() << "Button name:" << name;
        getTransactions("yes");

    }
    else if(name == "Back"){
        //qDebug() << "Button name:" << name;
        clearAll();
        close();
    }  
}

void chooseAction::logOutClickerHandler()
{
   bts.play();
    clearAll();
    emit logOutClicked();
}



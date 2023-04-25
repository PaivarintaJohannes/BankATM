#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>
#include <QTextEdit>



Transactions::Transactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transactions)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),
            this,SLOT(clickerHandler()),Qt::QueuedConnection);
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::setMyData(const QString &newMyData)
{
    qDebug()<<"dawdadawd";
    myData = newMyData;
    qDebug()<<myData;
    QTextEdit *textEdit = new QTextEdit(this); // create the text edit widget
    textEdit->setReadOnly(true); // set the text edit to be read-only
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // set the vertical scrollbar policy
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setGeometry(50, 50, 400, 160);
    textEdit->setText(myData);

}

void Transactions::clickerHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString name = button->objectName();
    if(name == "pushButton"){
        close();
    }
}



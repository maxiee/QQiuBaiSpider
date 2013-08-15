#include "widget.h"
#include "ui_widget.h"
#include <QNetworkReply>
#include<QRegExp>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    content = new QString();
    ui->setupUi(this);
    mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this, SLOT(query(QNetworkReply*)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::query(QNetworkReply *reply)
{
    QString buffer = reply->readAll();
    QRegExp exp("<div class=\"content\" title=\"(.*)\">(.*)</div>");
    exp.setMinimal(true);
    int pos=0;
    while ((pos = exp.indexIn(buffer,pos)) != -1) {
    content->append(exp.cap(1));
    content->append(exp.cap(2));
    pos += exp.matchedLength();
    qDebug(QString::number(pos).toAscii());
    }
    qDebug(QString::number(pos).toAscii());
    ui->contentEdit->setText(*content);
}

void Widget::on_goButton_clicked()
{
    QString uri = ui->addrEdit->text();
    qDebug("下面开始爬");
    int i;
    for(i=0;i<10;i++)
    {
        QString url2(uri);
        url2.append(QString::number(i,10));
        qDebug(url2.toAscii());
        mgr->get(QNetworkRequest(QUrl(url2)));
    }
}

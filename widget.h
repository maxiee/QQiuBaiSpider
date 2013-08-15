#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void query(QNetworkReply* reply);
    
private slots:
    void on_goButton_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager* mgr;
    QString *content;
};

#endif // WIDGET_H

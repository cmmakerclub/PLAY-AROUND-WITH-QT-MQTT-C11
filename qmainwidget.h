#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <QWidget>
#include "qmqtt.h"

namespace Ui {
class QMainWidget;
}

class QMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMainWidget(QWidget *parent = 0);
    ~QMainWidget();

private slots:
    void mqttConnected();
    void mqttDisconnected();
    void mqttReceived(const QMQTT::Message &msg);
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();

private:
    void uiSetup();

private:
    Ui::QMainWidget *ui;
    QMQTT::Client *client;
};

#endif // QMAINWIDGET_H

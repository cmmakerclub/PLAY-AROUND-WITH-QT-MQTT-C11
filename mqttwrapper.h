#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H

#include <QObject>
#include <qmqtt.h>

class MQTTWrapper : public QObject
{
    Q_OBJECT
public:
    MQTTWrapper() {
        _client = new QMQTT::Client();

        connect(_client,SIGNAL(connected()),this,SLOT(onMQTT_Connected()));
        connect(_client,SIGNAL(connacked(quint8)),this,SLOT(onMQTT_Connacked(quint8)));
        connect(_client,SIGNAL(subscribed(const QString &)), this, SLOT(onSubscribed(const QString &)));
        connect(_client,SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));
        connect(_client,SIGNAL(subacked(quint16, quint8)), this, SLOT(onMQTT_subacked(quint16, quint8)));
    };
    QMQTT::Client* getMqttClient() {
        return _client;
    }

signals:
    void connacked(quint8);
    void connected();
    void subscribed(const QString &);
    void received(const QMQTT::Message &message);


public slots:
    void onMQTT_Connected();
    void onMQTT_Received(const QMQTT::Message &message);
    void onMQTT_Connacked(quint8);
    void onSubscribed(const QString &topic);
    void onMQTT_subacked(quint16 msgid, quint8 qos);
private:
    QMQTT::Client *_client;

};

#endif // MQTTWRAPPER_H

#include "mqttwrapper.h"



void MQTTWrapper::onMQTT_Received(const QMQTT::Message &message)
{
    QRegExp rx("(\\,)");
    QStringList data2 = (((QString)message.payload()).split(rx));
    emit received(message);
//      QTime time = QTime::currentTime();
//      QDateTime date = QDateTime::currentDateTime();
//      QString time_text = time.toString("hh : mm : ss");
//      QString date_text = date.toString("dddd : dd : MMM : yyyy");
}
void MQTTWrapper::onMQTT_Connected(){
        qDebug() << "connected";
        emit connected();
//        log(tr("Connected to %1 on port %2").arg(_client->host()).arg(_client->port()));
//        _client->subscribe("cmmc/Dragon",0);
}
void MQTTWrapper::onMQTT_Connacked(quint8 ack)
{
    QString ackStatus;
    switch(ack) {
    case QMQTT::CONNACK_ACCEPT:
        ackStatus = "Connection Accepted";
        break;
    case QMQTT::CONNACK_PROTO_VER:
        ackStatus = "Connection Refused: unacceptable protocol version";
        break;
    case QMQTT::CONNACK_INVALID_ID:
        ackStatus = "Connection Refused: identifier rejected";
        break;
    case QMQTT::CONNACK_SERVER:
        ackStatus = "Connection Refused: server unavailable";
        break;
    case QMQTT::CONNACK_CREDENTIALS:
        ackStatus = "Connection Refused: bad user name or password";
        break;
    case QMQTT::CONNACK_AUTH:
        ackStatus = "Connection Refused: not authorized";
        break;
    }
//    log(tr("connacked = %1 : %2").arg(ack).arg(ackStatus));
    qDebug() << "connacked =" << ack << ":" << ackStatus;
}
void MQTTWrapper::onSubscribed(const QString &topic)
{
    qDebug() << "Subscribed";
    qDebug() << topic;

    emit subscribed(topic);
}

void MQTTWrapper::onMQTT_subacked(quint16 msgid, quint8 qos)
{
//    log(tr("subacked: msgid=%1, qos=%2").arg(msgid).arg(qos));
    qDebug() << "subacked:" << msgid << ":" << qos;
}

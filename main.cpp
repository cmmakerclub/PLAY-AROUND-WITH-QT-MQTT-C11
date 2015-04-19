#include "qmainwidget.h"
#include <QApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QWindow>
#include <mqttwrapper.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    MQTTWrapper *wrapper = new MQTTWrapper();
    QMQTT::Client *client = wrapper->getMqttClient();

    client->setClientId("clientId");

    client->setHost("iot.eclipse.org");

    client->setPort(1883);
    client->autoReconnect();
    client->connect();


    QObject *topLevel = engine.rootObjects().value(0);
    qDebug() << engine.rootObjects().size();

    QWindow *window = qobject_cast<QWindow*>(topLevel);
    QObject *textView = window->findChild<QObject*>("text1");

    QObject::connect(wrapper, &MQTTWrapper::connected, [=] () {
      qDebug() << "MQTT CONNECTED" << endl;
      textView ->setProperty("text", "CONNECTED");
      client->subscribe("hello", 0);
    });

    QObject::connect(wrapper, &MQTTWrapper::subscribed, [=] (const QString &topic) -> void {
      textView->setProperty("text", "SUBSCRIBED");
      qDebug() << "MQTT SUBSCRIBED: " <<  topic << endl;
    });

    QObject::connect(wrapper, &MQTTWrapper::received, [=] (const QMQTT::Message &message) -> void {
      textView->setProperty("text", message.payload());
      qDebug() << "MQTT received: " <<  message.payload() << endl;
    });


    int val = 4;
    auto add = [=] (int a) mutable -> int {
        qDebug() << "ADD 1 TO: " << val << endl;
        val += 1;
        return a+val;
    };


    qDebug() << "BEFORE: " << add(add(add(1))) <<  " AFTER: " << add(1) <<endl;



    return app.exec();
}

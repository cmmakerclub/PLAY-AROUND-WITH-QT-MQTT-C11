#include "qmainwidget.h"
#include <QApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    QMQTT::Client *_client = new QMQTT::Client();
    _client->setHost("iot.eclipse.org");
    _client->setPort(1883);
    _client->setKeepAlive(300);
    _client->setCleansess(1);
    _client->connect();

    return app.exec();
}

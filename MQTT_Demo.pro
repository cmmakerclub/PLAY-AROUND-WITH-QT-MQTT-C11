#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T07:41:37
#
#-------------------------------------------------


CONFIG += c++11
QT       += qml core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MQTT_Demo
TEMPLATE = app

DEFINES += QMQTT_LIBRARY

DEFINES += LG_SCREEN

SOURCES += main.cpp \
    qmainwidget.cpp \
    qmqtt_client.cpp \
    qmqtt_client_p.cpp \
    qmqtt_frame.cpp \
    qmqtt_message.cpp \
    qmqtt_network.cpp \
    qmqtt_will.cpp \
    mqttwrapper.cpp


HEADERS  += qmainwidget.h \
    qmqtt.h \
    qmqtt_client.h \
    qmqtt_client_p.h \
    qmqtt_frame.h \
    qmqtt_global.h \
    qmqtt_message.h \
    qmqtt_network.h \
    qmqtt_will.h \
    mqttwrapper.h

RESOURCES += \
    resources.qrc

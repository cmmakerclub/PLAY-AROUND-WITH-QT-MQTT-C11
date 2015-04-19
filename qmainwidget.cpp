#include "qmainwidget.h"
#include "ui_qmainwidget.h"
#include <QDebug>

#define DISP_SEC_MAX                30

#ifdef LG_SCREEN
    #define ICON_SIZE               100
    #define BIG_FONT_SIZE           32
    #define SMALL_FONT_SIZE         22
    #define VALUE_MIN_WIDTH         140
    #define UNIT_WIDTH              50
#endif

#ifdef MID_SCREEN
    #define ICON_SIZE               70
    #define BIG_FONT_SIZE           22
    #define SMALL_FONT_SIZE         16
    #define VALUE_MIN_WIDTH         90
    #define UNIT_WIDTH              30
#endif

QMainWidget::QMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMainWidget)
{
    ui->setupUi(this);
    uiSetup();
    client = new QMQTT::Client();

    connect(client, SIGNAL(connected()), this, SLOT(mqttConnected()));
    connect(client, SIGNAL(disconnected()), this, SLOT(mqttDisconnected()));
    connect(client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(mqttReceived(const QMQTT::Message &)));
}

QMainWidget::~QMainWidget()
{
    delete ui;
}


void QMainWidget::uiSetup()
{
    QPixmap pixmap;
    QFont font;  

    //=============================================================================

    ui->lblTmp->setMinimumWidth(VALUE_MIN_WIDTH);
    font = ui->lblTmp->font();
    font.setPointSize(BIG_FONT_SIZE);
    font.setBold(true);
    ui->lblTmp->setFont(font);

    font = ui->lblTmpUnit->font();
    font.setPointSize(SMALL_FONT_SIZE);
    font.setBold(true);
    ui->lblTmpUnit->setFont(font);
    ui->lblTmpUnit->setMinimumWidth(UNIT_WIDTH);
    ui->lblTmpUnit->setMaximumWidth(UNIT_WIDTH);

    ui->lblTmpIcon->setText("");
    pixmap.load(":/tmp_icon.png");
    ui->lblTmpIcon->setPixmap(pixmap);
    ui->lblTmpIcon->setScaledContents(true);
    ui->lblTmpIcon->setMinimumSize(QSize(ICON_SIZE, ICON_SIZE));
    ui->lblTmpIcon->setMaximumSize(QSize(ICON_SIZE, ICON_SIZE));

    //=============================================================================

    ui->lblHum->setMinimumWidth(VALUE_MIN_WIDTH);
    font = ui->lblHum->font();
    font.setPointSize(BIG_FONT_SIZE);
    font.setBold(true);
    ui->lblHum->setFont(font);

    font = ui->lblHumUnit->font();
    font.setPointSize(SMALL_FONT_SIZE);
    font.setBold(true);
    ui->lblHumUnit->setFont(font);
    ui->lblHumUnit->setMinimumWidth(UNIT_WIDTH);
    ui->lblHumUnit->setMaximumWidth(UNIT_WIDTH);

    ui->lblTmpIcon->setText("");
    pixmap.load(":/water_icon.png");
    ui->lblHumIcon->setPixmap(pixmap);
    ui->lblHumIcon->setScaledContents(true);
    ui->lblHumIcon->setMinimumSize(QSize(ICON_SIZE, ICON_SIZE));
    ui->lblHumIcon->setMaximumSize(QSize(ICON_SIZE, ICON_SIZE));

    //=============================================================================

    ui->lblPir->setMinimumWidth(VALUE_MIN_WIDTH);
    font = ui->lblPir->font();
    font.setPointSize(BIG_FONT_SIZE);
    font.setBold(true);
    ui->lblPir->setFont(font);

    font = ui->lblPirUnit->font();
    font.setPointSize(SMALL_FONT_SIZE);
    font.setBold(true);
    ui->lblPirUnit->setFont(font);
    ui->lblPirUnit->setMinimumWidth(UNIT_WIDTH);
    ui->lblPirUnit->setMaximumWidth(UNIT_WIDTH);

    ui->lblPirIcon->setText("");
    pixmap.load(":/pir_icon.png");
    ui->lblPirIcon->setPixmap(pixmap);
    ui->lblPirIcon->setScaledContents(true);
    ui->lblPirIcon->setMinimumSize(QSize(ICON_SIZE, ICON_SIZE));
    ui->lblPirIcon->setMaximumSize(QSize(ICON_SIZE, ICON_SIZE));
}

void QMainWidget::mqttConnected()
{
    qDebug() << "Connected";
    client->subscribe("#", 0);
}

void QMainWidget::mqttDisconnected()
{
    qDebug() << "Disconnected";
}

void QMainWidget::mqttReceived(const QMQTT::Message &msg)
{
    if (msg.topic() == ui->txtTmpSub->text()) {
        ui->lblTmp->setText(QString(msg.payload()));
    }

    if (msg.topic() ==  ui->txtHumSub->text()) {
        ui->lblHum->setText(QString(msg.payload()));
    }

    if (msg.topic() == ui->txtPirSub->text()) {
        ui->lblPir->setText(QString(msg.payload()));
    }

    qDebug() << "Received";
}

void QMainWidget::on_btnConnect_clicked()
{
    client->setHost(ui->txtHost->text());
    client->setPort(ui->txtPort->text().toInt());
    client->connect();
    client->subscribe(ui->txtTmpSub->text(), 0);
    client->subscribe(ui->txtHumSub->text(), 0);
    client->subscribe(ui->txtPirSub->text(), 0);
    ui->txtTmpSub->setEnabled(false);
    ui->txtHumSub->setEnabled(false);
    ui->txtPirSub->setEnabled(false);
}


void QMainWidget::on_btnDisconnect_clicked()
{
    client->disconnect();
    client->unsubscribe("#");
    ui->txtTmpSub->setEnabled(true);
    ui->txtHumSub->setEnabled(true);
    ui->txtPirSub->setEnabled(true);
}

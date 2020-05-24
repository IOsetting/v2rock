#include "settingsgeneraltab.h"
#include "ui_settingsgeneraltab.h"

SettingsGeneralTab::SettingsGeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGeneralTab)
{
    ui->setupUi(this);
    subscribeUrlEdit = new QLineEdit(this);
    v2executablePathEdit = new QLineEdit(this);

    httpCheckBox = new QCheckBox("HTTP Proxy", this);
    socksCheckBox = new QCheckBox("SOCKS5 Proxy", this);

    httpListenEdit = new QLineEdit(this);
    httpPortEdit = new QLineEdit(this);
    httpPortEdit->setValidator(new QIntValidator(1024, 65535));
    socksListenEdit = new QLineEdit(this);
    socksPortEdit = new QLineEdit(this);
    socksPortEdit->setValidator(new QIntValidator(1024, 65535));

    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(socksCheckBox);
    checkBoxLayout->addWidget(httpCheckBox);

    QGroupBox *socksGroupBox = new QGroupBox(tr("Socks proxy"));
    QVBoxLayout *socksListenLayout = new QVBoxLayout;
    socksListenLayout->addWidget(new QLabel(tr("Listen:")));
    socksListenLayout->addWidget(socksListenEdit);
    QVBoxLayout *socksPortLayout = new QVBoxLayout;
    socksPortLayout->addWidget(new QLabel(tr("Port:")));
    socksPortLayout->addWidget(socksPortEdit);
    QHBoxLayout *socksGroupLayout = new QHBoxLayout;
    socksGroupLayout->addLayout(socksListenLayout, 3);
    socksGroupLayout->addLayout(socksPortLayout, 1);
    socksGroupBox->setLayout(socksGroupLayout);

    QGroupBox *httpGroupBox = new QGroupBox(tr("HTTP proxy"));
    QVBoxLayout *httpListenLayout = new QVBoxLayout;
    httpListenLayout->addWidget(new QLabel(tr("Listen:")));
    httpListenLayout->addWidget(httpListenEdit);
    QVBoxLayout *httpPortLayout = new QVBoxLayout;
    httpPortLayout->addWidget(new QLabel(tr("Port:")));
    httpPortLayout->addWidget(httpPortEdit);
    QHBoxLayout *httpGroupLayout = new QHBoxLayout;
    httpGroupLayout->addLayout(httpListenLayout, 3);
    httpGroupLayout->addLayout(httpPortLayout, 1);
    httpGroupBox->setLayout(httpGroupLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Subscribe URL:")));
    mainLayout->addWidget(subscribeUrlEdit);
    mainLayout->addWidget(new QLabel(tr("Path to v2ray executable")));
    mainLayout->addWidget(v2executablePathEdit);
    mainLayout->addLayout(checkBoxLayout);
    mainLayout->addWidget(socksGroupBox);
    mainLayout->addWidget(httpGroupBox);
    setLayout(mainLayout);
}

SettingsGeneralTab::~SettingsGeneralTab()
{
    delete ui;
    delete subscribeUrlEdit;
    delete v2executablePathEdit;

    delete httpCheckBox;
    delete socksCheckBox;
    delete httpListenEdit;
    delete httpPortEdit;
    delete socksListenEdit;
    delete socksPortEdit;
}

void SettingsGeneralTab::init(V2RockConfig *v2rockConfig)
{
    this->subscribeUrlEdit->setText(v2rockConfig->getSubscribeUrl());
    this->v2executablePathEdit->setText(v2rockConfig->getV2executablePath());

    if (v2rockConfig->getSocksConfig()) {
        this->socksCheckBox->setChecked(true);
        this->socksListenEdit->setText(v2rockConfig->getSocksConfig()->getListen());
        this->socksPortEdit->setText(QString::number(v2rockConfig->getSocksConfig()->getPort()));
    } else {
        this->socksCheckBox->setChecked(false);
        this->socksListenEdit->setText("127.0.0.1");
        this->socksPortEdit->setText("1080");
    }

    if (v2rockConfig->getHttpConfig()) {
        this->httpCheckBox->setChecked(true);
        this->httpListenEdit->setText(v2rockConfig->getHttpConfig()->getListen());
        this->httpPortEdit->setText(QString::number(v2rockConfig->getHttpConfig()->getPort()));
    } else {
        this->httpCheckBox->setChecked(false);
        this->httpListenEdit->setText("127.0.0.1");
        this->httpPortEdit->setText("1081");
    }

}

QString SettingsGeneralTab::getSubscribeUrl() const
{
    return subscribeUrlEdit->text();
}

QString SettingsGeneralTab::getV2executablePath() const
{
    return v2executablePathEdit->text();
}

bool SettingsGeneralTab::isSocksChecked() const
{
    return socksCheckBox->isChecked();
}

QString SettingsGeneralTab::getSocksListen() const
{
    return socksListenEdit->text();
}

int SettingsGeneralTab::getSocksPort() const
{
    QString portText = socksPortEdit->text();
    if (!portText.isEmpty())
    {
        bool ok;
        int port = portText.toInt(&ok, 10);
        if (ok) {
            return port;
        }
    }
    return -1;
}

bool SettingsGeneralTab::isHttpChecked() const
{
    return httpCheckBox->isChecked();
}

QString SettingsGeneralTab::getHttpListen() const
{
    return httpListenEdit->text();
}

int SettingsGeneralTab::getHttpPort() const
{
    QString portText = httpPortEdit->text();
    if (!portText.isEmpty())
    {
        bool ok;
        int port = portText.toInt(&ok, 10);
        if (ok) {
            return port;
        }
    }
    return -1;
}

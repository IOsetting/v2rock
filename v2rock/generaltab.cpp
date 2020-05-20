#include "generaltab.h"
#include "ui_generaltab.h"

GeneralTab::GeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralTab)
{
    ui->setupUi(this);
    subscribeUrlEdit = new QLineEdit(this);
    v2executablePathEdit = new QLineEdit(this);

    httpCheckBox = new QCheckBox("HTTP Proxy", this);
    socksCheckBox = new QCheckBox("SOCKS5 Proxy", this);

    httpListenEdit = new QLineEdit(this);
    httpPortEdit = new QLineEdit(this);
    socksListenEdit = new QLineEdit(this);
    socksPortEdit = new QLineEdit(this);

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

GeneralTab::~GeneralTab()
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

void GeneralTab::init(V2RockConfig *v2rockConfig)
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

QString GeneralTab::getSubscribeUrl() const
{
    return subscribeUrlEdit->text();
}

QString GeneralTab::getV2executablePath() const
{
    return v2executablePathEdit->text();
}

bool GeneralTab::isSocksChecked() const
{
    return socksCheckBox->isChecked();
}

QString GeneralTab::getSocksListen() const
{
    return socksListenEdit->text();
}

int GeneralTab::getSocksPort() const
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

bool GeneralTab::isHttpChecked() const
{
    return httpCheckBox->isChecked();
}

QString GeneralTab::getHttpListen() const
{
    return httpListenEdit->text();
}

int GeneralTab::getHttpPort() const
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

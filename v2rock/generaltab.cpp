#include "generaltab.h"
#include "ui_generaltab.h"

GeneralTab::GeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralTab)
{
    ui->setupUi(this);
    subscribeUrlEdit = new QLineEdit(this);
    localSocks5PortEdit = new QLineEdit(this);
    v2executablePathEdit = new QLineEdit(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Subscribe URL:")));
    mainLayout->addWidget(subscribeUrlEdit);
    mainLayout->addWidget(new QLabel(tr("Local socks5 port: [1024 - 65535]")));
    mainLayout->addWidget(localSocks5PortEdit);
    mainLayout->addWidget(new QLabel(tr("Path to v2ray executable")));
    mainLayout->addWidget(v2executablePathEdit);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

GeneralTab::~GeneralTab()
{
    delete ui;
    delete v2executablePathEdit;
    delete subscribeUrlEdit;
    delete localSocks5PortEdit;
}

void GeneralTab::init(V2RockConfig *v2rockConfig)
{
    this->subscribeUrlEdit->setText(v2rockConfig->getSubscribeUrl());
    this->localSocks5PortEdit->setText(QString::number(v2rockConfig->getLocalSocks5Port()));
    this->v2executablePathEdit->setText(v2rockConfig->getV2executablePath());
}

QString GeneralTab::getSubscribeUrl() const
{
    return subscribeUrlEdit->text();
}

int GeneralTab::getLocalSocks5Port() const
{
    QString portText = localSocks5PortEdit->text();
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

QString GeneralTab::getV2executablePath() const
{
    return v2executablePathEdit->text();
}

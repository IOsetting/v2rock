#include "settingsgeneraltab.h"
#include "ui_settingsgeneraltab.h"

SettingsGeneralTab::SettingsGeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGeneralTab)
{
    ui->setupUi(this);

    subscribeUrlEdit = new QLineEdit(this);
    v2executablePathEdit = new QLineEdit(this);
    loglevelCombo = new QComboBox();
    loglevelCombo->addItems(QStringList({"debug", "info", "warning", "error", "none"}));

    QVBoxLayout *vlay10 = new QVBoxLayout;
    vlay10->addWidget(new QLabel(tr("Path to v2ray executable")));
    vlay10->addWidget(v2executablePathEdit);
    QVBoxLayout *vlay11 = new QVBoxLayout;
    vlay11->addWidget(new QLabel(tr("Log level")));
    vlay11->addWidget(loglevelCombo);
    QHBoxLayout *hlay10 = new QHBoxLayout;
    hlay10->addLayout(vlay10, 3);
    hlay10->addLayout(vlay11, 1);

    httpCheckBox = new QCheckBox("HTTP Proxy", this);
    socksCheckBox = new QCheckBox("SOCKS5 Proxy", this);
    QHBoxLayout *hlay20 = new QHBoxLayout;
    hlay20->addWidget(socksCheckBox);
    hlay20->addWidget(httpCheckBox);

    // socks proxy
    socksProxyPanel = new QWidget();
    socksListenEdit = new QLineEdit(this);
    socksPortEdit = new QLineEdit(this);
    socksPortEdit->setValidator(new QIntValidator(1024, 65535));

    QVBoxLayout *vlay30 = new QVBoxLayout;
    vlay30->addWidget(new QLabel(tr("SOCKS5 listen")));
    vlay30->addWidget(socksListenEdit);
    QVBoxLayout *vlay31 = new QVBoxLayout;
    vlay31->addWidget(new QLabel(tr("SOCKS5 port:")));
    vlay31->addWidget(socksPortEdit);
    QHBoxLayout *hlay30 = new QHBoxLayout;
    hlay30->addLayout(vlay30, 3);
    hlay30->addLayout(vlay31, 1);
    hlay30->setMargin(0);
    socksProxyPanel->setLayout(hlay30);

    // http proxy
    httpProxyPanel = new QWidget();
    httpListenEdit = new QLineEdit(this);
    httpPortEdit = new QLineEdit(this);
    httpPortEdit->setValidator(new QIntValidator(1024, 65535));

    QVBoxLayout *vlay40 = new QVBoxLayout;
    vlay40->addWidget(new QLabel(tr("HTTP listen")));
    vlay40->addWidget(httpListenEdit);
    QVBoxLayout *vlay41 = new QVBoxLayout;
    vlay41->addWidget(new QLabel(tr("HTTP port")));
    vlay41->addWidget(httpPortEdit);
    QHBoxLayout *hlay40 = new QHBoxLayout;
    hlay40->addLayout(vlay40, 3);
    hlay40->addLayout(vlay41, 1);
    hlay40->setMargin(0);
    httpProxyPanel->setLayout(hlay40);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Subscribe URL:")));
    mainLayout->addWidget(subscribeUrlEdit);
    mainLayout->addLayout(hlay10);
    mainLayout->addLayout(hlay20);
    mainLayout->addWidget(socksProxyPanel);
    mainLayout->addWidget(httpProxyPanel);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(mainLayout);

    connect(socksCheckBox, SIGNAL(clicked(bool)), socksProxyPanel, SLOT(setVisible(bool)));
    connect(httpCheckBox, SIGNAL(clicked(bool)), httpProxyPanel, SLOT(setVisible(bool)));
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
    this->loglevelCombo->setCurrentText(v2rockConfig->getLoglevel());

    if (v2rockConfig->getSocksConfig()) {
        this->socksCheckBox->setChecked(true);
        this->socksProxyPanel->setVisible(true);
        this->socksListenEdit->setText(v2rockConfig->getSocksConfig()->getListen());
        this->socksPortEdit->setText(QString::number(v2rockConfig->getSocksConfig()->getPort()));
    } else {
        this->socksCheckBox->setChecked(false);
        this->socksProxyPanel->setVisible(false);
        this->socksListenEdit->setText("127.0.0.1");
        this->socksPortEdit->setText("1080");
    }

    if (v2rockConfig->getHttpConfig()) {
        this->httpCheckBox->setChecked(true);
        this->httpProxyPanel->setVisible(true);
        this->httpListenEdit->setText(v2rockConfig->getHttpConfig()->getListen());
        this->httpPortEdit->setText(QString::number(v2rockConfig->getHttpConfig()->getPort()));
    } else {
        this->httpCheckBox->setChecked(false);
        this->httpProxyPanel->setVisible(false);
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

QString SettingsGeneralTab::getLoglevel() const
{
    return loglevelCombo->currentText();
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

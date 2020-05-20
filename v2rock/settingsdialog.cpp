#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget;
    generalTab = new GeneralTab();
    tabWidget->addTab(generalTab, tr("General"));
    byPassIpTab = new ByPassIpTab();
    tabWidget->addTab(byPassIpTab, tr("Bypass Ips"));
    byPassDomainTab = new ByPassDomainTab();
    tabWidget->addTab(byPassDomainTab, tr("Bypass Domains"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Settings"));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

V2RockConfig *SettingsDialog::getV2rockConfig() const
{
    return v2rockConfig;
}

void SettingsDialog::setV2rockConfig(V2RockConfig *value)
{
    v2rockConfig = value;
    this->generalTab->init(v2rockConfig);
    this->byPassIpTab->init(v2rockConfig);
    this->byPassDomainTab->init(v2rockConfig);
}

void SettingsDialog::accept()
{
    /* subscribe url */
    QString subscribeUrl = generalTab->getSubscribeUrl();
    v2rockConfig->setSubscribeUrl(subscribeUrl);

    /* v2executable path */
    QString v2executablePath = generalTab->getV2executablePath();
    v2rockConfig->setV2executablePath(v2executablePath);

    /* error check */
    if (!generalTab->isHttpChecked() && !generalTab->isSocksChecked()) {
        QMessageBox::critical(
                    this, tr("Error"), tr("HTTP and SOCKS cannot be both unchecked."), QMessageBox::Ok);
        return;
    } else if (generalTab->getHttpPort() == generalTab->getSocksPort()) {
        QMessageBox::critical(
                    this, tr("Error"), tr("HTTP and SOCKS ports cannot be the same."), QMessageBox::Ok);
        return;
    }

    if (generalTab->isSocksChecked()) {
        /* socks port */
        int port = generalTab->getSocksPort();
        if (port <= -1) {
            QMessageBox::critical(
                        this, tr("Error"), tr("Invalid port number."), QMessageBox::Ok);
            return;
        }
        if (port < 1024 || port > 65535) {
            QMessageBox::critical(
                        this, tr("Error"), tr("Port value should be between 1024 and 65535"), QMessageBox::Ok);
            return;
        }

        /* socks listen */
        QString listen = generalTab->getSocksListen();
        if (listen.length() == 0) {
            listen = "127.0.0.1";
        }

        if (v2rockConfig->getSocksConfig()) {
            v2rockConfig->getSocksConfig()->setListen(listen);
            v2rockConfig->getSocksConfig()->setPort(port);
        } else {
            v2rockConfig->initSocksConfig(listen, port);
        }
    } else {
        v2rockConfig->deleteSocksConfig();
    }

    if (generalTab->isHttpChecked()) {
        /* http port */
        int port = generalTab->getHttpPort();
        if (port <= -1) {
            QMessageBox::critical(
                        this, tr("Error"), tr("Invalid port number."), QMessageBox::Ok);
            return;
        }
        if (port < 1024 || port > 65535) {
            QMessageBox::critical(
                        this, tr("Error"), tr("Port value should be between 1024 and 65535"), QMessageBox::Ok);
            return;
        }

        /* http listen */
        QString listen = generalTab->getHttpListen();
        if (listen.length() == 0) {
            listen = "127.0.0.1";
        }

        if (v2rockConfig->getHttpConfig()) {
            v2rockConfig->getHttpConfig()->setListen(listen);
            v2rockConfig->getHttpConfig()->setPort(port);
        } else {
            v2rockConfig->initHttpConfig(listen, port);
        }
    } else {
        v2rockConfig->deleteHttpConfig();
    }

    /* bypass ips */
    QList<QString> ips = byPassIpTab->getBypassIps();
    v2rockConfig->setBypassIps(ips);

    /* bypass domains */
    QList<QString> domains = byPassDomainTab->getBypassDomains();
    v2rockConfig->setBypassDomains(domains);

    QDialog::accept();
}

void SettingsDialog::reject()
{
    QDialog::reject();
}

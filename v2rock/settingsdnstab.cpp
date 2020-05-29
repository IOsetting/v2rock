#include "settingsdnstab.h"
#include "ui_settingsdnstab.h"

SettingsDnsTab::SettingsDnsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDnsTab)
{
    ui->setupUi(this);

    dnsCheckBox = new QCheckBox(tr("Enable DNS"));
    dnsPanel = new QWidget();
    connect(dnsCheckBox, SIGNAL(clicked(bool)), dnsPanel, SLOT(setVisible(bool)));

    tagEdit = new QLineEdit;
    clientIpEdit = new QLineEdit;

    QVBoxLayout *vlay10 = new QVBoxLayout;
    vlay10->addWidget(new QLabel(tr("Tag")));
    vlay10->addWidget(tagEdit);
    QVBoxLayout *vlay11 = new QVBoxLayout;
    vlay11->addWidget(new QLabel(tr("Client IP")));
    vlay11->addWidget(clientIpEdit);
    QHBoxLayout *hlay10 = new QHBoxLayout;
    hlay10->addLayout(vlay10);
    hlay10->addLayout(vlay11);

    hostsEdit = new QPlainTextEdit;
    serversEdit = new QPlainTextEdit;

    QVBoxLayout *vlay20 = new QVBoxLayout;
    vlay20->addLayout(hlay10);
    vlay20->addWidget(new QLabel(tr("Hosts")));
    vlay20->addWidget(hostsEdit);
    vlay20->addWidget(new QLabel(tr("Servers (JSON text)")));
    vlay20->addWidget(serversEdit);
    vlay20->setMargin(0);
    dnsPanel->setLayout(vlay20);

    QVBoxLayout *mainlay = new QVBoxLayout;
    mainlay->addWidget(dnsCheckBox);
    mainlay->addWidget(dnsPanel);
    mainlay->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    this->setLayout(mainlay);
}

SettingsDnsTab::~SettingsDnsTab()
{
    delete tagEdit;
    delete clientIpEdit;
    delete hostsEdit;
    delete serversEdit;
    delete dnsPanel;
    delete dnsCheckBox;
    delete ui;
}

void SettingsDnsTab::init(V2RockConfig *v2rockConfig)
{
    if (v2rockConfig->getDnsConfig()) {
        dnsCheckBox->setChecked(true);
        dnsPanel->setVisible(true);
        tagEdit->setText(v2rockConfig->getDnsConfig()->tag);
        clientIpEdit->setText(v2rockConfig->getDnsConfig()->clientIp);
        //  hosts
        QStringList hosts;
        QMapIterator<QString, QString> it(v2rockConfig->getDnsConfig()->hosts);
        while (it.hasNext()) {
            it.next();
            hosts.append(it.key() + " " + it.value());
        }
        hostsEdit->setPlainText(hosts.join("\n"));
        // servers
        QJsonArray serverObjs;
        foreach (DNSServerObject *server, v2rockConfig->getDnsConfig()->serverObjects) {
            QJsonObject serverObj;
            V2RayConfig::toJson(server, serverObj);
            serverObjs.append(serverObj);
        }
        foreach (QString server, v2rockConfig->getDnsConfig()->servers) {
            serverObjs.append(QString(server));
        }
        serversEdit->setPlainText(V2RayConfigOutbound::toText(serverObjs));
    } else {
        dnsCheckBox->setChecked(false);
        dnsPanel->setVisible(false);

        tagEdit->setText("dns_inbound");
        clientIpEdit->setText("");
        //  hosts
        QStringList hosts({"example.com 1.2.3.4", "example.net 2.3.4.5"});
        hostsEdit->setPlainText(hosts.join("\n"));
        // servers
        QJsonArray serverObjs;
        serverObjs.append("8.8.8.8");
        serverObjs.append("8.8.4.4");
        serversEdit->setPlainText(V2RayConfigOutbound::toText(serverObjs));
    }
}

bool SettingsDnsTab::isDnsChecked()
{
    return dnsCheckBox->isChecked();
}

void SettingsDnsTab::getDnsSettings(DNSObject &settings)
{
    settings.tag = tagEdit->text();
    settings.clientIp = clientIpEdit->text();
    // hosts
    settings.hosts.clear();
    QStringList hostsList = hostsEdit->toPlainText().split("\n");
    foreach(QString line, hostsList) {
        QStringList host = line.split(" ");
        if (host.size() >= 2) {
            settings.hosts.insert(host.at(0), host.at(1));
        }
    }

    // servers
    settings.servers.clear();
    foreach (DNSServerObject *server, settings.serverObjects) {
        delete server;
    }
    settings.serverObjects.clear();

    QString jsonText = serversEdit->toPlainText();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(jsonText.toUtf8(), &errorPtr);
    if (doc.isNull() || !doc.isArray()) {
        qDebug() << "Servers format is invalid." << errorPtr.errorString();
        emit logReceived("Servers format is invalid.");
    } else {
        QJsonArray array = doc.array();
        foreach (QJsonValue val, array) {
            if (val.isObject()) {
                QJsonObject obj = val.toObject();
                DNSServerObject *server = new DNSServerObject;
                V2RayConfig::fromJson(*server, obj);
                settings.serverObjects.append(server);
            } else if (val.isString()) {
                settings.servers.append(val.toString());
            }
        }
    }
}

#include "nodeeditgeneraltab.h"
#include "ui_nodeeditgeneraltab.h"

NodeEditGeneralTab::NodeEditGeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditGeneralTab)
{
    ui->setupUi(this);

    nameEdit = new QLineEdit();
    protocolComb = new QComboBox();
    protocolComb->addItem("HTTP", "http");
    protocolComb->addItem("MTProto", "mtproto");
    protocolComb->addItem("Shadowsocks", "shadowsocks");
    protocolComb->addItem("Socks", "socks");
    protocolComb->addItem("VMess", "vmess");
    connect(protocolComb, SIGNAL(currentIndexChanged(int)), this, SLOT(protocolSwitch(int)));

    QVBoxLayout *vlay10 = new QVBoxLayout;
    vlay10->addWidget(new QLabel(tr("Name")));
    vlay10->addWidget(nameEdit);
    QVBoxLayout *vlay11 = new QVBoxLayout;
    vlay11->addWidget(new QLabel(tr("Protocol")));
    vlay11->addWidget(protocolComb);
    QHBoxLayout *hlay10 = new QHBoxLayout;
    hlay10->addLayout(vlay10, 3);
    hlay10->addLayout(vlay11, 1);

    // vmess
    vmessPanel = new QWidget();
    vmessAddressEdit = new QLineEdit();
    vmessPortEdit = new QLineEdit();
    vmessPortEdit->setValidator(new QIntValidator(0, 65535));
    vmessUserIdEdit = new QLineEdit();
    vmessUserAidEdit = new QLineEdit();
    vmessUserAidEdit->setValidator(new QIntValidator());
    vmessUserLevelEdit = new QLineEdit();
    vmessUserLevelEdit->setValidator(new QIntValidator());
    vmessUserSecurityComb = new QComboBox();
    vmessUserSecurityComb->addItem("none");
    vmessUserSecurityComb->addItem("auto");
    vmessUserSecurityComb->addItem("aes-128-gcm");
    vmessUserSecurityComb->addItem("chacha20-poly1305");

    QVBoxLayout *vlay20 = new QVBoxLayout;
    vlay20->addWidget(new QLabel(tr("Address")));
    vlay20->addWidget(vmessAddressEdit);
    QVBoxLayout *vlay21 = new QVBoxLayout;
    vlay21->addWidget(new QLabel(tr("Port")));
    vlay21->addWidget(vmessPortEdit);
    QHBoxLayout *hlay20 = new QHBoxLayout;
    hlay20->addLayout(vlay20, 3);
    hlay20->addLayout(vlay21, 1);

    QVBoxLayout *vlay22 = new QVBoxLayout;
    vlay22->addWidget(new QLabel(tr("User ID")));
    vlay22->addWidget(vmessUserIdEdit);
    QVBoxLayout *vlay23 = new QVBoxLayout;
    vlay23->addWidget(new QLabel(tr("User AlterId")));
    vlay23->addWidget(vmessUserAidEdit);
    QVBoxLayout *vlay24 = new QVBoxLayout;
    vlay24->addWidget(new QLabel(tr("User Level")));
    vlay24->addWidget(vmessUserLevelEdit);
    QVBoxLayout *vlay25 = new QVBoxLayout;
    vlay25->addWidget(new QLabel(tr("Security")));
    vlay25->addWidget(vmessUserSecurityComb);
    QHBoxLayout *hlay21 = new QHBoxLayout;
    hlay21->addLayout(vlay23, 2);
    hlay21->addLayout(vlay24, 2);
    hlay21->addLayout(vlay25, 3);

    QVBoxLayout *vlay26 = new QVBoxLayout;
    vlay26->addLayout(hlay20);
    vlay26->addLayout(vlay22);
    vlay26->addLayout(hlay21);
    vlay26->setMargin(0);
    vmessPanel->setLayout(vlay26);

    // socks
    socksPanel = new QWidget();
    socksAddressEdit = new QLineEdit();
    socksPortEdit = new QLineEdit();
    socksPortEdit->setValidator(new QIntValidator(0, 65535));
    socksUserUserEdit = new QLineEdit();
    socksUserPassEdit = new QLineEdit();
    socksUserLevelEdit = new QLineEdit();
    socksUserLevelEdit->setValidator(new QIntValidator());

    QVBoxLayout *vlay30 = new QVBoxLayout;
    vlay30->addWidget(new QLabel(tr("Address")));
    vlay30->addWidget(socksAddressEdit);
    QVBoxLayout *vlay31 = new QVBoxLayout;
    vlay31->addWidget(new QLabel(tr("Port")));
    vlay31->addWidget(socksPortEdit);
    QHBoxLayout *hlay30 = new QHBoxLayout;
    hlay30->addLayout(vlay30, 3);
    hlay30->addLayout(vlay31, 1);

    QVBoxLayout *vlay32 = new QVBoxLayout;
    vlay32->addWidget(new QLabel(tr("User")));
    vlay32->addWidget(socksUserUserEdit);
    QVBoxLayout *vlay33 = new QVBoxLayout;
    vlay33->addWidget(new QLabel(tr("Pass")));
    vlay33->addWidget(socksUserPassEdit);
    QVBoxLayout *vlay34 = new QVBoxLayout;
    vlay34->addWidget(new QLabel(tr("Level")));
    vlay34->addWidget(socksUserLevelEdit);
    QHBoxLayout *hlay31 = new QHBoxLayout;
    hlay31->addLayout(vlay32, 1);
    hlay31->addLayout(vlay33, 1);
    hlay31->addLayout(vlay34, 1);

    QVBoxLayout *vlay35 = new QVBoxLayout;
    vlay35->addLayout(hlay30);
    vlay35->addLayout(hlay31);
    vlay35->setMargin(0);
    socksPanel->setLayout(vlay35);

    // shadowsocks
    shadowsocksPanel = new QWidget();
    shadowsocksAddressEdit = new QLineEdit();
    shadowsocksPortEdit = new QLineEdit();
    shadowsocksPortEdit->setValidator(new QIntValidator(0, 65535));
    shadowsocksEmailEdit = new QLineEdit();
    shadowsocksPasswordEdit = new QLineEdit();
    shadowsocksOtaCheckbox = new QCheckBox("OTA");
    shadowsocksLevelEdit = new QLineEdit();
    shadowsocksLevelEdit->setValidator(new QIntValidator());
    shadowsocksMethodComb = new QComboBox();
    shadowsocksMethodComb->addItem("aes-128-cfb");
    shadowsocksMethodComb->addItem("aes-256-cfb");
    shadowsocksMethodComb->addItem("aes-128-gcm");
    shadowsocksMethodComb->addItem("aes-256-gcm");
    shadowsocksMethodComb->addItem("chacha20");
    shadowsocksMethodComb->addItem("chacha20-ietf");
    shadowsocksMethodComb->addItem("chacha20-poly1305");

    QVBoxLayout *vlay40 = new QVBoxLayout;
    vlay40->addWidget(new QLabel(tr("Address")));
    vlay40->addWidget(shadowsocksAddressEdit);
    QVBoxLayout *vlay41 = new QVBoxLayout;
    vlay41->addWidget(new QLabel(tr("Port")));
    vlay41->addWidget(shadowsocksPortEdit);
    QHBoxLayout *hlay40 = new QHBoxLayout;
    hlay40->addLayout(vlay40, 3);
    hlay40->addLayout(vlay41, 1);

    QVBoxLayout *vlay42 = new QVBoxLayout;
    vlay42->addWidget(new QLabel(tr("Email")));
    vlay42->addWidget(shadowsocksEmailEdit);
    QVBoxLayout *vlay43 = new QVBoxLayout;
    vlay43->addWidget(new QLabel(tr("Pass")));
    vlay43->addWidget(shadowsocksPasswordEdit);
    QVBoxLayout *vlay44 = new QVBoxLayout;
    vlay44->addWidget(new QLabel(tr("Level")));
    vlay44->addWidget(shadowsocksLevelEdit);
    QHBoxLayout *hlay41 = new QHBoxLayout;
    hlay41->addLayout(vlay42, 3);
    hlay41->addLayout(vlay43, 2);
    hlay41->addLayout(vlay44, 1);


    QVBoxLayout *vlay45 = new QVBoxLayout;
    vlay45->addWidget(new QLabel(tr("Method")));
    vlay45->addWidget(shadowsocksMethodComb);
    QVBoxLayout *vlay46 = new QVBoxLayout;
    vlay46->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlay46->addWidget(shadowsocksOtaCheckbox);
    QHBoxLayout *hlay42 = new QHBoxLayout;
    hlay42->addLayout(vlay45);
    hlay42->addLayout(vlay46);

    QVBoxLayout *vlay47 = new QVBoxLayout;
    vlay47->addLayout(hlay40);
    vlay47->addLayout(hlay41);
    vlay47->addLayout(hlay42);
    vlay47->setMargin(0);
    shadowsocksPanel->setLayout(vlay47);

    // http
    httpPanel = new QWidget();
    httpAddressEdit = new QLineEdit();
    httpPortEdit = new QLineEdit();
    httpPortEdit->setValidator(new QIntValidator(0, 65535));
    httpUserUserEdit = new QLineEdit();
    httpUserPassEdit = new QLineEdit();

    QVBoxLayout *vlay50 = new QVBoxLayout;
    vlay50->addWidget(new QLabel(tr("Address")));
    vlay50->addWidget(httpAddressEdit);
    QVBoxLayout *vlay51 = new QVBoxLayout;
    vlay51->addWidget(new QLabel(tr("Port")));
    vlay51->addWidget(httpPortEdit);
    QHBoxLayout *hlay50 = new QHBoxLayout;
    hlay50->addLayout(vlay50, 3);
    hlay50->addLayout(vlay51, 1);

    QVBoxLayout *vlay52 = new QVBoxLayout;
    vlay52->addWidget(new QLabel(tr("User")));
    vlay52->addWidget(httpUserUserEdit);
    QVBoxLayout *vlay53 = new QVBoxLayout;
    vlay53->addWidget(new QLabel(tr("Pass")));
    vlay53->addWidget(httpUserPassEdit);
    QHBoxLayout *hlay51 = new QHBoxLayout;
    hlay51->addLayout(vlay52, 1);
    hlay51->addLayout(vlay53, 1);

    QVBoxLayout *vlay55 = new QVBoxLayout;
    vlay55->addLayout(hlay50);
    vlay55->addLayout(hlay51);
    vlay55->setMargin(0);
    httpPanel->setLayout(vlay55);

    // Main layout
    QVBoxLayout *mainlay = new QVBoxLayout;
    mainlay->addLayout(hlay10);
    mainlay->addWidget(vmessPanel);
    mainlay->addWidget(socksPanel);
    mainlay->addWidget(shadowsocksPanel);
    mainlay->addWidget(httpPanel);
    mainlay->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(mainlay);
    protocolComb->setCurrentIndex(4);
    protocolSwitch(4);
}

NodeEditGeneralTab::~NodeEditGeneralTab()
{
    delete ui;
}

void NodeEditGeneralTab::init(V2RockConfig *v2rockConfig, int index)
{
    if (index == -1) { // when adding a new node
        return;
    }
    QList<V2RockNode *> nodes = v2rockConfig->getNodes();
    nameEdit->setText(nodes.at(index)->getName());
    int current = 0;
    if (nodes.at(index)->getProtocol() == "http") {
        current = 0;
    } else if (nodes.at(index)->getProtocol() == "mtproto") {
        current = 1;
    } else if (nodes.at(index)->getProtocol() == "shadowsocks") {
        current = 2;
    } else if (nodes.at(index)->getProtocol() == "socks") {
        current = 3;
    } else if (nodes.at(index)->getProtocol() == "vmess") {
        current = 4;
    }
    protocolComb->setCurrentIndex(current);
    protocolSwitch(current);

    if (nodes.at(index)->getVMessSettings()) {
        if (!nodes.at(index)->getVMessSettings()->vnext.isEmpty()) {
            VMessServerObject *server = nodes.at(index)->getVMessSettings()->vnext.at(0);
            vmessAddressEdit->setText(server->address);
            vmessPortEdit->setText(QString::number(server->port));
            if (!server->users.isEmpty()) {
                vmessUserIdEdit->setText(server->users.at(0)->id);
                vmessUserAidEdit->setText(QString::number(server->users.at(0)->alterId));
                vmessUserLevelEdit->setText(QString::number(server->users.at(0)->level));
                vmessUserSecurityComb->setCurrentText(server->users.at(0)->security);
            }
        }
    }
    if (nodes.at(index)->getSocksSettings()) {
        if (!nodes.at(index)->getSocksSettings()->servers.isEmpty()) {
            SocksServerObject *server = nodes.at(index)->getSocksSettings()->servers.at(0);
            socksAddressEdit->setText(server->address);
            socksAddressEdit->setText(QString::number(server->port));
            if (!server->users.isEmpty()) {
                socksUserUserEdit->setText(server->users.at(0)->user);
                socksUserPassEdit->setText(server->users.at(0)->pass);
                socksUserLevelEdit->setText(QString::number(server->users.at(0)->level));
            }
        }
    }
    if (nodes.at(index)->getShadowSocksSettings()) {
        if (!nodes.at(index)->getShadowSocksSettings()->servers.isEmpty()) {
            ShadowsocksServerObject *server = nodes.at(index)->getShadowSocksSettings()->servers.at(0);
            shadowsocksAddressEdit->setText(server->address);
            shadowsocksPortEdit->setText(QString::number(server->port));
            shadowsocksEmailEdit->setText(server->email);
            shadowsocksMethodComb->setCurrentText(server->method);
            shadowsocksPasswordEdit->setText(server->password);
            if (server->ota) {
                shadowsocksOtaCheckbox->setChecked(true);
            } else {
                shadowsocksOtaCheckbox->setChecked(false);
            }
            shadowsocksLevelEdit->setText(QString::number(server->level));
        }
    }
    if (nodes.at(index)->getHTTPSettings()) {
        if (!nodes.at(index)->getHTTPSettings()->servers.isEmpty()) {
            HTTPServerObject *server = nodes.at(index)->getHTTPSettings()->servers.at(0);
            httpAddressEdit->setText(server->address);
            httpPortEdit->setText(QString::number(server->port));
            if (!server->users.isEmpty()) {
                httpUserUserEdit->setText(server->users.at(0)->user);
                httpUserPassEdit->setText(server->users.at(0)->pass);
            }
        }
    }
}

QString NodeEditGeneralTab::getName() const
{
    return nameEdit->text();
}

QString NodeEditGeneralTab::getProtocol() const
{
    return protocolComb->itemData(protocolComb->currentIndex()).toString();
}

void NodeEditGeneralTab::getVMessSettings(OutboundVMessConfigurationObject &settings) const
{
    VMessServerObject *server = new VMessServerObject;
    server->address = vmessAddressEdit->text();
    server->port = vmessPortEdit->text().toInt();
    UserObject *user = new UserObject;
    user->id = vmessUserIdEdit->text();
    user->alterId = vmessUserAidEdit->text().toInt();
    user->level = vmessUserLevelEdit->text().toInt();
    user->security = vmessUserSecurityComb->currentText();
    server->users.append(user);
    settings.vnext.append(server);
}

void NodeEditGeneralTab::getSocksSettings(OutboundSocksConfigurationObject &settings) const
{
    SocksServerObject *server = new SocksServerObject;
    server->address = socksAddressEdit->text();
    server->port = socksPortEdit->text().toInt();
    AccountUserObject *user = new AccountUserObject;
    user->user = socksUserUserEdit->text();
    user->pass = socksUserPassEdit->text();
    user->level = socksUserLevelEdit->text().toInt();
    server->users.append(user);
    settings.servers.append(server);
}

void NodeEditGeneralTab::getShadowsocksSettings(OutboundShadowsocksConfigurationObject &settings) const
{
    ShadowsocksServerObject *server = new ShadowsocksServerObject;
    server->address = shadowsocksAddressEdit->text();
    server->port = shadowsocksPortEdit->text().toInt();
    server->email = shadowsocksEmailEdit->text();
    server->password = shadowsocksPasswordEdit->text();
    server->method = shadowsocksMethodComb->currentText();
    server->ota = shadowsocksOtaCheckbox->isChecked();
    server->level = shadowsocksLevelEdit->text().toInt();
    settings.servers.append(server);
}

void NodeEditGeneralTab::getHTTPSettings(OutboundHTTPConfigurationObject &settings) const
{
    HTTPServerObject *server = new HTTPServerObject;
    server->address = httpAddressEdit->text();
    server->port = httpPortEdit->text().toInt();
    AccountObject *user = new AccountObject;
    user->user = httpUserUserEdit->text();
    user->pass = httpUserPassEdit->text();
    server->users.append(user);
    settings.servers.append(server);
}

void NodeEditGeneralTab::protocolSwitch(const int index)
{
    vmessPanel->setVisible(false);
    socksPanel->setVisible(false);
    shadowsocksPanel->setVisible(false);
    httpPanel->setVisible(false);

    if (index == 0) {
        httpPanel->setVisible(true);
    } else if (index == 1) {
        // show nothing
    } else if (index == 2) {
        shadowsocksPanel->setVisible(true);
    } else if (index == 3) {
        socksPanel->setVisible(true);
    } else if (index == 4) {
        vmessPanel->setVisible(true);
    }
}

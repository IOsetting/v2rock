#include "nodeeditdialog.h"
#include "ui_nodeeditdialog.h"

NodeEditDialog::NodeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeEditDialog)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget;
    generalTab = new NodeEditGeneralTab(this);
    miscTab = new NodeEditMiscTab(this);
    networkTab = new NodeEditNetworkTab(this);
    tabWidget->addTab(generalTab, tr("General"));
    tabWidget->addTab(networkTab, tr("Network"));
    tabWidget->addTab(miscTab, tr("Misc"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Edit Node"));
}

NodeEditDialog::~NodeEditDialog()
{
    delete generalTab;
    delete miscTab;
    delete networkTab;
    delete tabWidget;
    delete buttonBox;
    delete ui;
}

void NodeEditDialog::init(V2RockConfig *v2rockConfig, int index)
{
    this->v2rockConfig = v2rockConfig;
    this->index = index;
    generalTab->init(v2rockConfig, index);
    networkTab->init(v2rockConfig->getNodes().at(index)->getStreamSettings());
}

void NodeEditDialog::accept()
{
    QList<V2RockNode *> nodes = v2rockConfig->getNodes();
    V2RockNode *node = nodes.at(index);
    // General Tab
    node->setName(generalTab->getName());
    node->setProtocol(generalTab->getProtocol());
    if (node->getProtocol() == "vmess") {
        OutboundVMessConfigurationObject *settings = new OutboundVMessConfigurationObject;
        generalTab->getVMessSettings(*settings);
        node->setVMessSettings(settings);
    } else if (node->getProtocol() == "http") {
        OutboundHTTPConfigurationObject *settings = new OutboundHTTPConfigurationObject;
        generalTab->getHTTPSettings(*settings);
        node->setHTTPSettings(settings);
    } else if (node->getProtocol() == "mtproto") {
        OutboundMTProtoConfigurationObject *settings = new OutboundMTProtoConfigurationObject;
        node->setMTProtoSettings(settings);
    } else if (node->getProtocol() == "shadowsocks") {
        OutboundShadowsocksConfigurationObject *settings = new OutboundShadowsocksConfigurationObject;
        generalTab->getShadowsocksSettings(*settings);
        node->setShadowSocksSettings(settings);
    } else if (node->getProtocol() == "socks") {
        OutboundSocksConfigurationObject *settings = new OutboundSocksConfigurationObject;
        generalTab->getSocksSettings(*settings);
        node->setSocksSettings(settings);
    }

    // Network Tab
    StreamSettingsObject *streamSettings = new StreamSettingsObject();
    streamSettings->network = networkTab->getNetwork();
    if (streamSettings->network == "tcp") {
        streamSettings->tcpSettings = new TransportTcpObject();
        networkTab->getTcpSettings(*(streamSettings->tcpSettings));
    } else if (streamSettings->network == "kcp") {
        streamSettings->kcpSettings = new TransportKcpObject();
        networkTab->getKcpSettings(*(streamSettings->kcpSettings));
    } else if (streamSettings->network == "ws") {
        streamSettings->wsSettings = new TransportWebSocketObject();
        networkTab->getWsSettings(*(streamSettings->wsSettings));
    } else if (streamSettings->network == "http") {
        streamSettings->httpSettings = new TransportHTTPObject();
        networkTab->getHttpSettings(*(streamSettings->httpSettings));
    } else if (streamSettings->network == "domainsocket") {
        streamSettings->dsSettings = new TransportDomainSocketObject();
        networkTab->getDsSettings(*(streamSettings->dsSettings));
    } else if (streamSettings->network == "quic") {
        streamSettings->quicSettings = new TransportQuicObject();
        networkTab->getQuicSettings(*(streamSettings->quicSettings));
    }

    node->setStreamSettings(streamSettings);
    QDialog::accept();
}

void NodeEditDialog::reject()
{
    QDialog::reject();
}

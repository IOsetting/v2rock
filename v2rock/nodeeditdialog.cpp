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
}

void NodeEditDialog::accept()
{
    QList<V2RockNode *> nodes = v2rockConfig->getNodes();
    V2RockNode *node = nodes.at(index);
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
    QDialog::accept();
}

void NodeEditDialog::reject()
{
    QDialog::reject();
}

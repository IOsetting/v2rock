#include "nodeeditnetworktab.h"
#include "ui_nodeeditnetworktab.h"

NodeEditNetworkTab::NodeEditNetworkTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditNetworkTab)
{
    ui->setupUi(this);

    networkComb = new QComboBox();
    networkComb->addItem("tcp");
    networkComb->addItem("kcp");
    networkComb->addItem("ws");
    networkComb->addItem("http");
    networkComb->addItem("domainsocket");
    networkComb->addItem("quic");
    connect(networkComb, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(networkSwitch(const QString&)));

    QVBoxLayout *vlay10 = new QVBoxLayout;
    vlay10->addWidget(new QLabel(tr("Network")));
    vlay10->addWidget(networkComb);
    QHBoxLayout *hlay10 = new QHBoxLayout;
    hlay10->addLayout(vlay10);
    hlay10->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // TCP
    tcpPanel = new QWidget();
    tcpHttpPanel = new QWidget();
    tcpHeaderTypeComb = new QComboBox();
    tcpHeaderTypeComb->addItem("none");
    tcpHeaderTypeComb->addItem("http");
    connect(tcpHeaderTypeComb, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(tcpHttpPanelSwitch(const QString&)));
    tcpHeaderRequestVersionEdit = new QLineEdit();
    tcpHeaderRequestMethodComb = new QComboBox();
    tcpHeaderRequestMethodComb->addItems({"GET", "POST", "PUT", "FETCH"});
    tcpHeaderRequestPathEdit = new QLineEdit();
    tcpHeaderRequestHeadersEdit = new QPlainTextEdit();

    tcpHeaderResponseVersionEdit = new QLineEdit();
    tcpHeaderResponseStatusComb = new QComboBox();
    tcpHeaderResponseStatusComb->addItems({"200", "201", "202", "301", "304", "400", "401", "403", "404", "500", "501", "502", "503", "504"});
    tcpHeaderResponseReasonEdit = new QLineEdit();
    tcpHeaderResponseHeadersEdit = new QPlainTextEdit();

    QVBoxLayout *vlay21 = new QVBoxLayout;
    vlay21->addWidget(new QLabel(tr("Req. Path")));
    vlay21->addWidget(tcpHeaderRequestPathEdit);
    QVBoxLayout *vlay22 = new QVBoxLayout;
    vlay22->addWidget(new QLabel(tr("Version")));
    vlay22->addWidget(tcpHeaderRequestVersionEdit);
    QVBoxLayout *vlay23 = new QVBoxLayout;
    vlay23->addWidget(new QLabel(tr("Method")));
    vlay23->addWidget(tcpHeaderRequestMethodComb);
    QHBoxLayout *hlay20 = new QHBoxLayout;
    hlay20->addLayout(vlay21, 2);
    hlay20->addLayout(vlay22, 1);
    hlay20->addLayout(vlay23, 1);

    QVBoxLayout *vlay24 = new QVBoxLayout;
    vlay24->addWidget(new QLabel(tr("Rsp. Reason")));
    vlay24->addWidget(tcpHeaderResponseReasonEdit);
    QVBoxLayout *vlay25 = new QVBoxLayout;
    vlay25->addWidget(new QLabel(tr("Version")));
    vlay25->addWidget(tcpHeaderResponseVersionEdit);
    QVBoxLayout *vlay26 = new QVBoxLayout;
    vlay26->addWidget(new QLabel(tr("Status")));
    vlay26->addWidget(tcpHeaderResponseStatusComb);
    QHBoxLayout *hlay21 = new QHBoxLayout;
    hlay21->addLayout(vlay24, 2);
    hlay21->addLayout(vlay25, 1);
    hlay21->addLayout(vlay26, 1);

    QVBoxLayout *vlay27 = new QVBoxLayout;
    vlay27->addLayout(hlay20);
    vlay27->addWidget(new QLabel(tr("Req. Headers")));
    vlay27->addWidget(tcpHeaderRequestHeadersEdit);
    vlay27->addLayout(hlay21);
    vlay27->addWidget(new QLabel(tr("Rsp. Headers")));
    vlay27->addWidget(tcpHeaderResponseHeadersEdit);
    vlay27->setMargin(0);
    tcpHttpPanel->setLayout(vlay27);

    QVBoxLayout *vlay20 = new QVBoxLayout;
    vlay20->addWidget(new QLabel(tr("Header Type")));
    vlay20->addWidget(tcpHeaderTypeComb);
    vlay20->addWidget(tcpHttpPanel);
    vlay20->setMargin(0);
    tcpPanel->setLayout(vlay20);
    tcpHeaderTypeComb->setCurrentText("none");
    tcpHttpPanelSwitch("none");

    // KCP
    kcpPanel = new QWidget();
    kcpMtuEdit = new QLineEdit();
    kcpTtiEdit = new QLineEdit();
    kcpUplinkCapacityEdit = new QLineEdit();
    kcpDownlinkCapacityEdit = new QLineEdit();
    kcpCongestionEdit = new QLineEdit();
    kcpReadBufferSizeEdit = new QLineEdit();
    kcpWriteBufferSizeEdit = new QLineEdit();
    kcpHeaderTypeComb = new QComboBox();
    kcpHeaderTypeComb->addItem("none");
    kcpHeaderTypeComb->addItem("srtp");
    kcpHeaderTypeComb->addItem("utp");
    kcpHeaderTypeComb->addItem("wechat-video");
    kcpHeaderTypeComb->addItem("dtls");
    kcpHeaderTypeComb->addItem("wireguard");

    QVBoxLayout *vlay30 = new QVBoxLayout;
    vlay30->addWidget(new QLabel(tr("MTU")));
    vlay30->addWidget(kcpMtuEdit);
    QVBoxLayout *vlay32 = new QVBoxLayout;
    vlay32->addWidget(new QLabel(tr("Uplink Cap")));
    vlay32->addWidget(kcpUplinkCapacityEdit);
    QVBoxLayout *vlay35 = new QVBoxLayout;
    vlay35->addWidget(new QLabel(tr("Read Buf")));
    vlay35->addWidget(kcpReadBufferSizeEdit);
    QHBoxLayout *hlay30 = new QHBoxLayout;
    hlay30->addLayout(vlay30);
    hlay30->addLayout(vlay32);
    hlay30->addLayout(vlay35);

    QVBoxLayout *vlay31 = new QVBoxLayout;
    vlay31->addWidget(new QLabel(tr("TTI")));
    vlay31->addWidget(kcpTtiEdit);
    QVBoxLayout *vlay33 = new QVBoxLayout;
    vlay33->addWidget(new QLabel(tr("Downlink Cap")));
    vlay33->addWidget(kcpDownlinkCapacityEdit);
    QVBoxLayout *vlay36 = new QVBoxLayout;
    vlay36->addWidget(new QLabel(tr("Write Buf")));
    vlay36->addWidget(kcpWriteBufferSizeEdit);
    QHBoxLayout *hlay31 = new QHBoxLayout;
    hlay31->addLayout(vlay31);
    hlay31->addLayout(vlay33);
    hlay31->addLayout(vlay36);

    QVBoxLayout *vlay34 = new QVBoxLayout;
    vlay34->addWidget(new QLabel(tr("Congestion")));
    vlay34->addWidget(kcpCongestionEdit);
    QVBoxLayout *vlay37 = new QVBoxLayout;
    vlay37->addWidget(new QLabel(tr("Header")));
    vlay37->addWidget(kcpHeaderTypeComb);
    QHBoxLayout *hlay32 = new QHBoxLayout;
    hlay32->addLayout(vlay34);
    hlay32->addLayout(vlay37);

    QVBoxLayout *vlay38 = new QVBoxLayout;
    vlay38->addLayout(hlay30);
    vlay38->addLayout(hlay31);
    vlay38->addLayout(hlay32);
    vlay38->setMargin(0);
    kcpPanel->setLayout(vlay38);

    // WS
    wsPanel = new QWidget();
    wsPathEdit = new QLineEdit();
    wsHeadersEdit = new QPlainTextEdit();

    QVBoxLayout *vlay40 = new QVBoxLayout;
    vlay40->addWidget(new QLabel(tr("Path")));
    vlay40->addWidget(wsPathEdit);
    vlay40->addWidget(new QLabel(tr("Headers")));
    vlay40->addWidget(wsHeadersEdit);
    vlay40->setMargin(0);
    wsPanel->setLayout(vlay40);

    // HTTP
    httpPanel = new QWidget();
    httpPathEdit = new QLineEdit();
    httpHostEdit = new QPlainTextEdit();

    QVBoxLayout *vlay50 = new QVBoxLayout;
    vlay50->addWidget(new QLabel(tr("Path")));
    vlay50->addWidget(httpPathEdit);
    vlay50->addWidget(new QLabel(tr("Hosts")));
    vlay50->addWidget(httpHostEdit);
    vlay50->setMargin(0);
    httpPanel->setLayout(vlay50);

    // DS
    dsPanel = new QWidget();
    dsPathEdit = new QLineEdit();
    QVBoxLayout *vlay60 = new QVBoxLayout;
    vlay60->addWidget(new QLabel(tr("Path")));
    vlay60->addWidget(dsPathEdit);
    vlay60->setMargin(0);
    dsPanel->setLayout(vlay60);

    // QUIC
    quicPanel = new QWidget();
    quicKeyEdit = new QLineEdit();
    quicSecurityComb = new QComboBox();
    quicSecurityComb->addItem("none");
    quicSecurityComb->addItem("aes-128-gcm");
    quicSecurityComb->addItem("chacha20-poly1305");
    quicHeaderTypeComb = new QComboBox();
    quicHeaderTypeComb->addItem("none");
    quicHeaderTypeComb->addItem("srtp");
    quicHeaderTypeComb->addItem("utp");
    quicHeaderTypeComb->addItem("wechat-video");
    quicHeaderTypeComb->addItem("dtls");
    quicHeaderTypeComb->addItem("wireguard");

    QVBoxLayout *vlay70 = new QVBoxLayout;
    vlay70->addWidget(new QLabel(tr("Key")));
    vlay70->addWidget(quicKeyEdit);
    QVBoxLayout *vlay71 = new QVBoxLayout;
    vlay71->addWidget(new QLabel(tr("Security")));
    vlay71->addWidget(quicSecurityComb);
    QVBoxLayout *vlay72 = new QVBoxLayout;
    vlay72->addWidget(new QLabel(tr("Header Type")));
    vlay72->addWidget(quicHeaderTypeComb);
    QHBoxLayout *hlay70 = new QHBoxLayout;
    hlay70->addLayout(vlay71);
    hlay70->addLayout(vlay72);
    vlay70->addLayout(hlay70);
    vlay70->setMargin(0);
    quicPanel->setLayout(vlay70);

    // Main layout
    QVBoxLayout *mainlay = new QVBoxLayout;
    mainlay->addLayout(hlay10);
    mainlay->addWidget(tcpPanel);
    mainlay->addWidget(kcpPanel);
    mainlay->addWidget(wsPanel);
    mainlay->addWidget(httpPanel);
    mainlay->addWidget(dsPanel);
    mainlay->addWidget(quicPanel);
    mainlay->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(mainlay);

    networkComb->setCurrentText("tcp");
    networkSwitch("tcp");
}

NodeEditNetworkTab::~NodeEditNetworkTab()
{
    delete ui;
}

QString NodeEditNetworkTab::getNetwork() const
{
    return networkComb->currentText();
}

void NodeEditNetworkTab::getTcpSettings(TransportTcpObject &settings) const
{
    settings.header.type = tcpHeaderTypeComb->currentText();
    if (settings.header.type == "http") {
        settings.header.request = new HTTPRequestObject();
        settings.header.response = new HTTPResponseObject();
        settings.header.request->version = tcpHeaderRequestVersionEdit->text();
        settings.header.request->method = tcpHeaderRequestMethodComb->currentText();
        settings.header.request->path = tcpHeaderRequestVersionEdit->text().split(",");

        settings.header.response->reason = tcpHeaderResponseReasonEdit->text();
        settings.header.response->status = tcpHeaderResponseStatusComb->currentText();
        settings.header.response->version = tcpHeaderResponseVersionEdit->text();
    }
}

void NodeEditNetworkTab::getKcpSettings(TransportKcpObject &settings) const
{

}

void NodeEditNetworkTab::getWsSettings(TransportWebSocketObject &settings) const
{

}

void NodeEditNetworkTab::getHttpSettings(TransportHTTPObject &settings) const
{

}

void NodeEditNetworkTab::getDsSettings(TransportDomainSocketObject &settings) const
{

}

void NodeEditNetworkTab::getQuicSettings(TransportQuicObject &settings) const
{

}

void NodeEditNetworkTab::networkSwitch(const QString &text)
{
    tcpPanel->setVisible(false);
    kcpPanel->setVisible(false);
    wsPanel->setVisible(false);
    httpPanel->setVisible(false);
    dsPanel->setVisible(false);
    quicPanel->setVisible(false);

    if (text == "tcp") {
        tcpPanel->setVisible(true);
    } else if (text == "kcp") {
        kcpPanel->setVisible(true);
    } else if (text == "ws") {
        wsPanel->setVisible(true);
    } else if (text == "http") {
        httpPanel->setVisible(true);
    } else if (text == "domainsocket") {
        dsPanel->setVisible(true);
    } else if (text == "quic" ) {
        quicPanel->setVisible(true);
    }
}

void NodeEditNetworkTab::tcpHttpPanelSwitch(const QString &text)
{
    if (text == "http") {
        tcpHttpPanel->setVisible(true);
    } else {
        tcpHttpPanel->setVisible(false);
    }
}

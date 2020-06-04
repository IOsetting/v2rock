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

    // KCP
    kcpPanel = new QWidget();
    kcpMtuEdit = new QLineEdit();
    kcpMtuEdit->setValidator(new QIntValidator(576, 1460));
    kcpTtiEdit = new QLineEdit();
    kcpTtiEdit->setValidator(new QIntValidator(10, 100));
    kcpUplinkCapacityEdit = new QLineEdit();
    kcpUplinkCapacityEdit->setValidator(new QIntValidator(0, 9999));
    kcpDownlinkCapacityEdit = new QLineEdit();
    kcpDownlinkCapacityEdit->setValidator(new QIntValidator(0, 9999));
    kcpCongestionCheckBox = new QCheckBox(tr("Enable"));
    kcpReadBufferSizeEdit = new QLineEdit();
    kcpReadBufferSizeEdit->setValidator(new QIntValidator(0, 128));
    kcpWriteBufferSizeEdit = new QLineEdit();
    kcpWriteBufferSizeEdit->setValidator(new QIntValidator(0, 128));
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
    vlay34->addWidget(kcpCongestionCheckBox);
    QVBoxLayout *vlay37 = new QVBoxLayout;
    vlay37->addWidget(new QLabel(tr("Header Type")));
    vlay37->addWidget(kcpHeaderTypeComb);
    QHBoxLayout *hlay32 = new QHBoxLayout;
    hlay32->addLayout(vlay37);
    hlay32->addLayout(vlay34);
    hlay32->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

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

}

NodeEditNetworkTab::~NodeEditNetworkTab()
{
    delete ui;
}

void NodeEditNetworkTab::init(StreamSettingsObject *streamSettings)
{
    this->clean();
    if (!streamSettings) return;

    networkComb->setCurrentText(streamSettings->network);
    networkSwitch(streamSettings->network);
    if (streamSettings->tcpSettings) {
        tcpHeaderTypeComb->setCurrentText(streamSettings->tcpSettings->header.type);
        tcpHttpPanelSwitch(streamSettings->tcpSettings->header.type);
        if (streamSettings->tcpSettings->header.type == "http") {
            if (streamSettings->tcpSettings->header.request) {
                tcpHeaderRequestVersionEdit->setText(streamSettings->tcpSettings->header.request->version);
                tcpHeaderRequestMethodComb->setCurrentText(streamSettings->tcpSettings->header.request->method);
                tcpHeaderRequestPathEdit->setText(streamSettings->tcpSettings->header.request->path.join(","));
                QJsonObject headerObj;
                V2RayConfigOutbound::toJson(&(streamSettings->tcpSettings->header.request->headers), headerObj);
                tcpHeaderRequestHeadersEdit->setPlainText(V2RayConfigOutbound::toText(headerObj));
            }
            if (streamSettings->tcpSettings->header.response) {
                tcpHeaderResponseVersionEdit->setText(streamSettings->tcpSettings->header.response->version);
                tcpHeaderResponseStatusComb->setCurrentText(streamSettings->tcpSettings->header.response->status);
                tcpHeaderResponseReasonEdit->setText(streamSettings->tcpSettings->header.response->reason);
                QJsonObject headerObj;
                V2RayConfigOutbound::toJson(&(streamSettings->tcpSettings->header.response->headers), headerObj);
                tcpHeaderResponseHeadersEdit->setPlainText(V2RayConfigOutbound::toText(headerObj));
            }

        }
    }
    if (streamSettings->kcpSettings) {
        kcpMtuEdit->setText(QString::number(streamSettings->kcpSettings->mtu));
        kcpTtiEdit->setText(QString::number(streamSettings->kcpSettings->tti));
        kcpUplinkCapacityEdit->setText(QString::number(streamSettings->kcpSettings->uplinkCapacity));
        kcpDownlinkCapacityEdit->setText(QString::number(streamSettings->kcpSettings->downlinkCapacity));
        kcpCongestionCheckBox->setChecked(streamSettings->kcpSettings->congestion);
        kcpReadBufferSizeEdit->setText(QString::number(streamSettings->kcpSettings->readBufferSize));
        kcpWriteBufferSizeEdit->setText(QString::number(streamSettings->kcpSettings->writeBufferSize));
        kcpHeaderTypeComb->setCurrentText(streamSettings->kcpSettings->header.type);
    }
    if (streamSettings->wsSettings) {
        wsPathEdit->setText(streamSettings->wsSettings->path);
        QJsonObject headersObj;
        V2RayConfigOutbound::toJson(&(streamSettings->wsSettings->headers), headersObj);
        wsHeadersEdit->setPlainText(V2RayConfigOutbound::toText(headersObj));
    }
    if (streamSettings->httpSettings) {
        httpPathEdit->setText(streamSettings->httpSettings->path);
        httpHostEdit->setPlainText(streamSettings->httpSettings->host.join("\n"));
    }
    if (streamSettings->dsSettings) {
        dsPathEdit->setText(streamSettings->dsSettings->path);
    }
    if (streamSettings->quicSettings) {
        quicKeyEdit->setText(streamSettings->quicSettings->key);
        quicSecurityComb->setCurrentText(streamSettings->quicSettings->security);
        quicHeaderTypeComb->setCurrentText(streamSettings->quicSettings->header.type);
    }
}

QString NodeEditNetworkTab::getNetwork() const
{
    return networkComb->currentText();
}

void NodeEditNetworkTab::getTcpSettings(TransportTcpObject &settings)
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
        // request headers
        QString jsonText = tcpHeaderRequestHeadersEdit->toPlainText();
        QJsonParseError errorPtr;
        QJsonDocument doc = QJsonDocument::fromJson(jsonText.toUtf8(), &errorPtr);
        if (doc.isNull() || !doc.isObject()) {
            qDebug() << "Request headers format is invalid." << errorPtr.errorString();
            emit logReceived("Request headers format is invalid.");
        } else {
            QJsonObject obj = doc.object();
            V2RayConfigOutbound::fromJson(settings.header.request->headers, obj);
        }
        // response headers
        jsonText = tcpHeaderRequestHeadersEdit->toPlainText();
        doc = QJsonDocument::fromJson(jsonText.toUtf8(), &errorPtr);
        if (doc.isNull() || !doc.isObject()) {
            qDebug() << "Response headers format is invalid." << errorPtr.errorString();
            emit logReceived("Response headers format is invalid.");
        } else {
            QJsonObject obj = doc.object();
            V2RayConfigOutbound::fromJson(settings.header.response->headers, obj);
        }
    } else {
        settings.header.request = 0;
        settings.header.response = 0;
    }
}

void NodeEditNetworkTab::getKcpSettings(TransportKcpObject &settings) const
{
    settings.mtu = kcpMtuEdit->text().toInt();
    settings.tti = kcpTtiEdit->text().toInt();
    settings.uplinkCapacity = kcpUplinkCapacityEdit->text().toInt();
    settings.downlinkCapacity = kcpDownlinkCapacityEdit->text().toInt();
    settings.congestion = kcpCongestionCheckBox->isChecked();
    settings.readBufferSize = kcpReadBufferSizeEdit->text().toInt();
    settings.writeBufferSize = kcpWriteBufferSizeEdit->text().toInt();
    settings.header.type = kcpHeaderTypeComb->currentText();
}

void NodeEditNetworkTab::getWsSettings(TransportWebSocketObject &settings)
{
    settings.path = wsPathEdit->text();
    QString jsonText = wsHeadersEdit->toPlainText();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(jsonText.toUtf8(), &errorPtr);
    if (doc.isNull() || !doc.isObject()) {
        qDebug() << "Websock headers format is invalid." << errorPtr.errorString();
        emit logReceived("Websock headers format is invalid.");
    } else {
        QJsonObject obj = doc.object();
        V2RayConfigOutbound::fromJson(settings.headers, obj);
    }
}

void NodeEditNetworkTab::getHttpSettings(TransportHTTPObject &settings) const
{
    settings.path = httpPathEdit->text();
    settings.host = httpHostEdit->toPlainText().split("\n");
}

void NodeEditNetworkTab::getDsSettings(TransportDomainSocketObject &settings) const
{
    settings.path = dsPathEdit->text();
}

void NodeEditNetworkTab::getQuicSettings(TransportQuicObject &settings) const
{
    settings.key = quicKeyEdit->text();
    settings.security = quicSecurityComb->currentText();
    settings.header.type = quicHeaderTypeComb->currentText();
}

void NodeEditNetworkTab::clean()
{
    networkComb->setCurrentText("tcp");
    networkSwitch("tcp");
    // tcp
    tcpHeaderTypeComb->setCurrentText("none");
    tcpHttpPanelSwitch("none");
    tcpHeaderRequestVersionEdit->setText("1.1");
    tcpHeaderRequestMethodComb->setCurrentIndex(0);
    tcpHeaderRequestPathEdit->setText("/");
    tcpHeaderResponseVersionEdit->setText("1.1");
    tcpHeaderResponseStatusComb->setCurrentIndex(0);
    tcpHeaderResponseReasonEdit->setText("OK");
    // Request headers
    QJsonObject headerObj;
    QMap<QString, QStringList> map;
    map.insert("Host", QStringList({}));
    map.insert("User-Agent", QStringList({}));
    map.insert("Accept-Encoding", QStringList({}));
    map.insert("Connection", QStringList({}));
    map.insert("Pragma", QStringList({}));
    V2RayConfigOutbound::toJson(&map, headerObj);
    tcpHeaderRequestHeadersEdit->setPlainText(V2RayConfigOutbound::toText(headerObj));

    // Response headers
    QJsonObject headerObj2;
    map.clear();
    map.insert("Content-Type", QStringList({}));
    map.insert("Transfer-Encoding", QStringList({}));
    map.insert("Connection", QStringList({}));
    map.insert("Pragma", QStringList({}));
    V2RayConfigOutbound::toJson(&map, headerObj2);
    tcpHeaderResponseHeadersEdit->setPlainText(V2RayConfigOutbound::toText(headerObj2));

    // kcp
    kcpMtuEdit->setText("1350");
    kcpTtiEdit->setText("50");
    kcpUplinkCapacityEdit->setText("5");
    kcpDownlinkCapacityEdit->setText("20");
    kcpCongestionCheckBox->setChecked(false);
    kcpReadBufferSizeEdit->setText("2");
    kcpWriteBufferSizeEdit->setText("2");
    kcpHeaderTypeComb->setCurrentIndex(0);
    // ws
    wsPathEdit->setText("/");
    wsHeadersEdit->setPlainText("{\n\n}");
    // HTTP
    httpHostEdit->setPlainText("");
    httpPathEdit->setText("/");
    // DS
    dsPathEdit->setText("/path/to/ds/file");
    // QUIC
    quicSecurityComb->setCurrentIndex(0);
    quicKeyEdit->setText("");
    quicHeaderTypeComb->setCurrentIndex(0);
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

#include "nodeeditmisctab.h"
#include "ui_nodeeditmisctab.h"

NodeEditMiscTab::NodeEditMiscTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditMiscTab)
{
    ui->setupUi(this);
    sockOptComb = new QComboBox();
    sockOptComb->addItems(QStringList({"off", "on"}));
    connect(sockOptComb, SIGNAL(currentIndexChanged(QString)), this, SLOT(sockOptSwitch(QString)));
    securityComb = new QComboBox();
    securityComb->addItems(QStringList({"none", "tls"}));
    connect(securityComb, SIGNAL(currentIndexChanged(QString)), this, SLOT(securitySwitch(QString)));
    QVBoxLayout *vlay00 = new QVBoxLayout;
    vlay00->addWidget(new QLabel(tr("Sock Options")));
    vlay00->addWidget(sockOptComb);
    QVBoxLayout *vlay01 = new QVBoxLayout;
    vlay01->addWidget(new QLabel(tr("Security")));
    vlay01->addWidget(securityComb);
    QHBoxLayout *hlay00 = new QHBoxLayout;
    hlay00->addLayout(vlay00);
    hlay00->addLayout(vlay01);

    // SOCK OPT
    sockOptPanel = new QWidget();
    sockOptMarkEdit = new QLineEdit();
    sockOptMarkEdit->setValidator(new QIntValidator(0, 65535));
    sockOptTcpFastOpenCheckBox = new QCheckBox(tr("Enable Fast Open"));
    sockOptTproxyComb = new QComboBox();
    sockOptTproxyComb->addItems(QStringList({"off", "redirect", "tproxy"}));

    QVBoxLayout *vlay10 = new QVBoxLayout;
    vlay10->addWidget(new QLabel(tr("SO_MARK")));
    vlay10->addWidget(sockOptMarkEdit);
    QVBoxLayout *vlay11 = new QVBoxLayout;
    vlay11->addWidget(new QLabel(""));
    vlay11->addWidget(sockOptTcpFastOpenCheckBox);
    QVBoxLayout *vlay12 = new QVBoxLayout;
    vlay12->addWidget(new QLabel(tr("TProxy")));
    vlay12->addWidget(sockOptTproxyComb);
    QHBoxLayout *hlay10 = new QHBoxLayout;
    hlay10->addLayout(vlay10);
    hlay10->addLayout(vlay12);
    hlay10->addLayout(vlay11);
    hlay10->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlay10->setMargin(0);
    sockOptPanel->setLayout(hlay10);

    // TLS
    tlsPanel = new QWidget();
    tlsServerNameEdit = new QLineEdit();
    tlsAllowInsecureCheckBox = new QCheckBox(tr("Allow Insecure"));
    tlsAlpnEdit = new QLineEdit();
    tlsCertificatesEdit = new QPlainTextEdit();
    tlsDisableSystemRootCheckBox = new QCheckBox(tr("Disable System Root CA"));
    QVBoxLayout *vlay20 = new QVBoxLayout;
    vlay20->addWidget(new QLabel(tr("Server Name")));
    vlay20->addWidget(tlsServerNameEdit);
    QVBoxLayout *vlay21 = new QVBoxLayout;
    vlay21->addWidget(new QLabel(tr("Alpn")));
    vlay21->addWidget(tlsAlpnEdit);
    QHBoxLayout *hlay20 = new QHBoxLayout;
    hlay20->addLayout(vlay20, 1);
    hlay20->addLayout(vlay21, 2);
    QHBoxLayout *hlay21 = new QHBoxLayout;
    hlay21->addWidget(new QLabel(tr("Certificates")));
    hlay21->addWidget(tlsDisableSystemRootCheckBox);
    hlay21->addWidget(tlsAllowInsecureCheckBox);

    QVBoxLayout *vlay22 = new QVBoxLayout;
    vlay22->addLayout(hlay20);
    vlay22->addLayout(hlay21);
    vlay22->addWidget(tlsCertificatesEdit);
    vlay22->setMargin(0);
    tlsPanel->setLayout(vlay22);

    QVBoxLayout *mainlay = new QVBoxLayout;
    mainlay->addLayout(hlay00);
    mainlay->addWidget(sockOptPanel);
    mainlay->addWidget(tlsPanel);
    mainlay->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setLayout(mainlay);
}

NodeEditMiscTab::~NodeEditMiscTab()
{
    delete ui;
}

void NodeEditMiscTab::init(StreamSettingsObject *streamSettings)
{
    this->clean();
    if (!streamSettings) return;

    securityComb->setCurrentText(streamSettings->security);
    securitySwitch(streamSettings->security);
    if (streamSettings->sockopt) {
        sockOptComb->setCurrentText("on");
        sockOptSwitch("on");
        sockOptMarkEdit->setText(QString::number(streamSettings->sockopt->mark));
        sockOptTcpFastOpenCheckBox->setChecked(streamSettings->sockopt->tcpFastOpen);
        sockOptTproxyComb->setCurrentText(streamSettings->sockopt->tproxy);
    }
    if (streamSettings->tlsSettings) {
        tlsServerNameEdit->setText(streamSettings->tlsSettings->serverName);
        tlsAllowInsecureCheckBox->setChecked(streamSettings->tlsSettings->allowInsecure);
        tlsAlpnEdit->setText(streamSettings->tlsSettings->alpn.join(","));
        tlsDisableSystemRootCheckBox->setChecked(streamSettings->tlsSettings->disableSystemRoot);
        // certificate objects
        QJsonArray certObjects;
        foreach (CertificateObject cert, streamSettings->tlsSettings->certificates) {
            QJsonObject certObject;
            V2RayConfigOutbound::toJson(&cert, certObject);
            certObjects.append(certObject);
        }
        tlsCertificatesEdit->setPlainText(V2RayConfigOutbound::toText(certObjects));
    }
}

QString NodeEditMiscTab::getSockopt() const
{
    return sockOptComb->currentText();
}

QString NodeEditMiscTab::getSecurity() const
{
    return securityComb->currentText();
}

void NodeEditMiscTab::getSockoptSettings(SockoptObject &settings)
{
    settings.mark = sockOptMarkEdit->text().toInt();
    settings.tcpFastOpen = sockOptTcpFastOpenCheckBox->isChecked();
    settings.tproxy = sockOptTproxyComb->currentText();
}

void NodeEditMiscTab::getTlsSettings(TransportTlsObject &settings)
{
    settings.serverName = tlsServerNameEdit->text();
    settings.allowInsecure = tlsAllowInsecureCheckBox->isChecked();
    settings.alpn = tlsAlpnEdit->text().split(",");
    settings.disableSystemRoot = tlsDisableSystemRootCheckBox->isChecked();
    // certificate objects
    QString jsonText = tlsCertificatesEdit->toPlainText();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(jsonText.toUtf8(), &errorPtr);
    if (doc.isNull() || !doc.isArray()) {
        qDebug() << "Certificates format is invalid." << errorPtr.errorString();
        emit logReceived("Certificates format is invalid.");
    } else {
        QJsonArray array = doc.array();
        foreach (QJsonValue val, array) {
            if (val.isObject()) {
                QJsonObject obj = val.toObject();
                CertificateObject cert;
                V2RayConfigOutbound::fromJson(cert, obj);
                settings.certificates.append(cert);
            }
        }
    }
}

void NodeEditMiscTab::clean()
{
    // SOCK OPT
    sockOptComb->setCurrentText("off");
    sockOptSwitch("off");

    sockOptMarkEdit->setText("0");
    sockOptTcpFastOpenCheckBox->setChecked(false);
    sockOptTproxyComb->setCurrentIndex(0);

    // TLS
    securityComb->setCurrentText("none");
    securitySwitch("none");
    tlsServerNameEdit->setText("");
    tlsAllowInsecureCheckBox->setChecked(false);
    tlsAlpnEdit->setText("http/1.1");

    QJsonArray certObjects;
    CertificateObject cert;
    cert.usage = "encipherment";
    cert.certificateFile = "/path/to/certificate.crt";
    cert.keyFile = "/path/to/key.key";
    QJsonObject certObject;
    V2RayConfigOutbound::toJson(&cert, certObject);
    certObjects.append(certObject);
    tlsCertificatesEdit->setPlainText(V2RayConfigOutbound::toText(certObjects));
    tlsDisableSystemRootCheckBox->setChecked(false);
}

void NodeEditMiscTab::sockOptSwitch(const QString &text)
{
    if (text == "on") {
        sockOptPanel->setVisible(true);
    } else {
        sockOptPanel->setVisible(false);
    }
}

void NodeEditMiscTab::securitySwitch(const QString &text)
{
    if (text == "tls") {
        tlsPanel->setVisible(true);
    } else {
        tlsPanel->setVisible(false);
    }
}

#ifndef NODEEDITNETWORKTAB_H
#define NODEEDITNETWORKTAB_H

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "v2rayconfigoutbound.h"

namespace Ui {
class NodeEditNetworkTab;
}

class NodeEditNetworkTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditNetworkTab(QWidget *parent = 0);
    ~NodeEditNetworkTab();
    void init(StreamSettingsObject *streamSettings);
    QString getNetwork() const;
    void getTcpSettings(TransportTcpObject &settings);
    void getKcpSettings(TransportKcpObject &settings) const;
    void getWsSettings(TransportWebSocketObject &settings);
    void getHttpSettings(TransportHTTPObject &settings) const;
    void getDsSettings(TransportDomainSocketObject &settings) const;
    void getQuicSettings(TransportQuicObject &settings) const;

signals:
    void logReceived(const QString&);

private:
    Ui::NodeEditNetworkTab *ui;
    QComboBox *networkComb;

    // tcp
    QWidget *tcpPanel;
    QWidget *tcpHttpPanel;
    QComboBox *tcpHeaderTypeComb;
    QLineEdit *tcpHeaderRequestVersionEdit;
    QComboBox *tcpHeaderRequestMethodComb;
    QLineEdit *tcpHeaderRequestPathEdit;
    QPlainTextEdit *tcpHeaderRequestHeadersEdit;

    QLineEdit *tcpHeaderResponseVersionEdit;
    QComboBox *tcpHeaderResponseStatusComb;
    QLineEdit *tcpHeaderResponseReasonEdit;
    QPlainTextEdit *tcpHeaderResponseHeadersEdit;

    // kcp
    QWidget *kcpPanel;
    QLineEdit *kcpMtuEdit;
    QLineEdit *kcpTtiEdit;
    QLineEdit *kcpUplinkCapacityEdit;
    QLineEdit *kcpDownlinkCapacityEdit;
    QCheckBox *kcpCongestionCheckBox;
    QLineEdit *kcpReadBufferSizeEdit;
    QLineEdit *kcpWriteBufferSizeEdit;
    QComboBox *kcpHeaderTypeComb;

    // ws
    QWidget *wsPanel;
    QLineEdit *wsPathEdit;
    QPlainTextEdit *wsHeadersEdit;

    // HTTP
    QWidget *httpPanel;
    QPlainTextEdit *httpHostEdit;
    QLineEdit *httpPathEdit;

    // DS
    QWidget *dsPanel;
    QLineEdit *dsPathEdit;

    // QUIC
    QWidget *quicPanel;
    QComboBox *quicSecurityComb;
    QLineEdit *quicKeyEdit;
    QComboBox *quicHeaderTypeComb;

    void clean();

private slots:
    void networkSwitch(const QString& text);
    void tcpHttpPanelSwitch(const QString& text);
};

#endif // NODEEDITNETWORKTAB_H

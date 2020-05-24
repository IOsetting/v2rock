#ifndef NODEEDITGENERALTAB_H
#define NODEEDITGENERALTAB_H

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class NodeEditGeneralTab;
}

class NodeEditGeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditGeneralTab(QWidget *parent = 0);
    ~NodeEditGeneralTab();
    void init(V2RockConfig *v2rockConfig, int index);
    QString getName() const;
    QString getProtocol() const;
    void getVMessSettings(OutboundVMessConfigurationObject &settings) const;
    void getSocksSettings(OutboundSocksConfigurationObject &settings) const;
    void getShadowsocksSettings(OutboundShadowsocksConfigurationObject &settings) const;
    void getHTTPSettings(OutboundHTTPConfigurationObject &settings) const;

private:
    Ui::NodeEditGeneralTab *ui;
    QLineEdit *nameEdit;
    QComboBox *protocolComb;

    // vmess
    QWidget *vmessPanel;
    QLineEdit *vmessAddressEdit;
    QLineEdit *vmessPortEdit;
    QLineEdit *vmessUserIdEdit;
    QLineEdit *vmessUserAidEdit;
    QComboBox *vmessUserSecurityComb;
    QLineEdit *vmessUserLevelEdit;

    // socks
    QWidget *socksPanel;
    QLineEdit *socksAddressEdit;
    QLineEdit *socksPortEdit;
    QLineEdit *socksUserUserEdit;
    QLineEdit *socksUserPassEdit;
    QLineEdit *socksUserLevelEdit;

    // shadowsocks
    QWidget *shadowsocksPanel;
    QLineEdit *shadowsocksAddressEdit;
    QLineEdit *shadowsocksPortEdit;
    QLineEdit *shadowsocksEmailEdit;
    QComboBox *shadowsocksMethodComb;
    QLineEdit *shadowsocksPasswordEdit;
    QCheckBox *shadowsocksOtaCheckbox;
    QLineEdit *shadowsocksLevelEdit;

    // mtproto: none

    // http
    QWidget *httpPanel;
    QLineEdit *httpAddressEdit;
    QLineEdit *httpPortEdit;
    QLineEdit *httpUserUserEdit;
    QLineEdit *httpUserPassEdit;

private slots:
    void protocolSwitch(const int index);
};

#endif // NODEEDITGENERALTAB_H

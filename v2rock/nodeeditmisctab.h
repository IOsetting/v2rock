#ifndef NODEEDITMISCTAB_H
#define NODEEDITMISCTAB_H

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "v2rayconfigoutbound.h"

namespace Ui {
class NodeEditMiscTab;
}

class NodeEditMiscTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditMiscTab(QWidget *parent = 0);
    ~NodeEditMiscTab();

    void init(StreamSettingsObject *streamSettings);
    QString getSockopt() const;
    QString getSecurity() const;
    void getSockoptSettings(SockoptObject &settings);
    void getTlsSettings(TransportTlsObject &settings);

signals:
    void logReceived(const QString&);

private:
    Ui::NodeEditMiscTab *ui;
    QComboBox *sockOptComb;
    QComboBox *securityComb;

    // SOCK OPT
    QWidget *sockOptPanel;
    QLineEdit *sockOptMarkEdit;
    QCheckBox *sockOptTcpFastOpenCheckBox;
    QComboBox *sockOptTproxyComb;

    // TLS
    QWidget *tlsPanel;
    QLineEdit *tlsServerNameEdit;
    QCheckBox *tlsAllowInsecureCheckBox;
    QLineEdit *tlsAlpnEdit;
    QPlainTextEdit *tlsCertificatesEdit;
    QCheckBox *tlsDisableSystemRootCheckBox;

    void clean();

private slots:
    void sockOptSwitch(const QString& text);
    void securitySwitch(const QString& text);
};

#endif // NODEEDITMISCTAB_H

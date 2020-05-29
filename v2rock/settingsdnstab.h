#ifndef SETTINGSDNSTAB_H
#define SETTINGSDNSTAB_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "v2rockconfig.h"

namespace Ui {
class SettingsDnsTab;
}

class SettingsDnsTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDnsTab(QWidget *parent = 0);
    ~SettingsDnsTab();
    void init(V2RockConfig *v2rockConfig);
    bool isDnsChecked();
    void getDnsSettings(DNSObject &settings);

signals:
    void logReceived(const QString&);

private:
    Ui::SettingsDnsTab *ui;

    QCheckBox *dnsCheckBox;
    QWidget *dnsPanel;
    QLineEdit *tagEdit;
    QLineEdit *clientIpEdit;
    QPlainTextEdit *hostsEdit;
    QPlainTextEdit *serversEdit;
};

#endif // SETTINGSDNSTAB_H

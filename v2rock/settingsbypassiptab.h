#ifndef BYPASSIPTAB_H
#define BYPASSIPTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class SettingsBypassIpTab;
}

class SettingsBypassIpTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsBypassIpTab(QWidget *parent = 0);
    ~SettingsBypassIpTab();
    void init(V2RockConfig *v2rockConfig);
    QList<QString> getBypassIps() const;

private:
    Ui::SettingsBypassIpTab *ui;
    QPlainTextEdit *bypassIpsEdit;
};

#endif // BYPASSIPTAB_H

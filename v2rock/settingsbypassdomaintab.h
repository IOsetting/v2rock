#ifndef BYPASSDOMAINTAB_H
#define BYPASSDOMAINTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class SettingsBypassDomainTab;
}

class SettingsBypassDomainTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsBypassDomainTab(QWidget *parent = 0);
    ~SettingsBypassDomainTab();
    void init(V2RockConfig *v2rockConfig);
    QList<QString> getBypassDomains() const;

private:
    Ui::SettingsBypassDomainTab *ui;
    QPlainTextEdit *bypassDomainsEdit;
};

#endif // BYPASSDOMAINTAB_H

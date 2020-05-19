#ifndef BYPASSDOMAINTAB_H
#define BYPASSDOMAINTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class ByPassDomainTab;
}

class ByPassDomainTab : public QWidget
{
    Q_OBJECT

public:
    explicit ByPassDomainTab(QWidget *parent = 0);
    ~ByPassDomainTab();
    void init(V2RockConfig *v2rockConfig);
    QList<QString> getBypassDomains() const;

private:
    Ui::ByPassDomainTab *ui;
    QPlainTextEdit *bypassDomainsEdit;
};

#endif // BYPASSDOMAINTAB_H

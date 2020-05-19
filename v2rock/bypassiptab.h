#ifndef BYPASSIPTAB_H
#define BYPASSIPTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class ByPassIpTab;
}

class ByPassIpTab : public QWidget
{
    Q_OBJECT

public:
    explicit ByPassIpTab(QWidget *parent = 0);
    ~ByPassIpTab();
    void init(V2RockConfig *v2rockConfig);
    QList<QString> getBypassIps() const;

private:
    Ui::ByPassIpTab *ui;
    QPlainTextEdit *bypassIpsEdit;
};

#endif // BYPASSIPTAB_H

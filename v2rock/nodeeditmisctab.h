#ifndef NODEEDITMISCTAB_H
#define NODEEDITMISCTAB_H

#include <QCheckBox>
#include <QComboBox>
#include <QWidget>

namespace Ui {
class NodeEditMiscTab;
}

class NodeEditMiscTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditMiscTab(QWidget *parent = 0);
    ~NodeEditMiscTab();

private:
    Ui::NodeEditMiscTab *ui;
    // SOCK OPT
    QCheckBox *sockOptTcpFastOpenCheckBox;
    QComboBox *sockOptTproxyComb;
};

#endif // NODEEDITMISCTAB_H

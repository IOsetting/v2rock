#ifndef NODEEDITTRANSPORTTAB_H
#define NODEEDITTRANSPORTTAB_H

#include <QWidget>

namespace Ui {
class NodeEditTransportTab;
}

class NodeEditTransportTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditTransportTab(QWidget *parent = 0);
    ~NodeEditTransportTab();

private:
    Ui::NodeEditTransportTab *ui;
};

#endif // NODEEDITTRANSPORTTAB_H

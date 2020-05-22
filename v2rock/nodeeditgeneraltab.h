#ifndef NODEEDITGENERALTAB_H
#define NODEEDITGENERALTAB_H

#include <QWidget>

namespace Ui {
class NodeEditGeneralTab;
}

class NodeEditGeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditGeneralTab(QWidget *parent = 0);
    ~NodeEditGeneralTab();

private:
    Ui::NodeEditGeneralTab *ui;
};

#endif // NODEEDITGENERALTAB_H

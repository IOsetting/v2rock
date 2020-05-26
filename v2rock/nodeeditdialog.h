#ifndef NODEEDITDIALOG_H
#define NODEEDITDIALOG_H

#include <QDebug>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>

#include "nodeeditgeneraltab.h"
#include "nodeeditmisctab.h"
#include "nodeeditnetworktab.h"
#include "v2rockconfig.h"

namespace Ui {
class NodeEditDialog;
}

class NodeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodeEditDialog(QWidget *parent = 0);
    ~NodeEditDialog();
    void init(V2RockConfig *v2rockConfig, int index, bool isNew=false);

private:
    V2RockConfig *v2rockConfig;
    int index;
    bool isNew;

    Ui::NodeEditDialog *ui;
    QTabWidget *tabWidget;
    NodeEditGeneralTab *generalTab;
    NodeEditMiscTab *miscTab;
    NodeEditNetworkTab *networkTab;
    QDialogButtonBox *buttonBox;

private slots:
    void accept();
    void reject();
};

#endif // NODEEDITDIALOG_H

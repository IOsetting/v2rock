#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QVBoxLayout>

#include "generaltab.h"
#include "bypassiptab.h"
#include "bypassdomaintab.h"
#include "v2rockconfig.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    V2RockConfig *getV2rockConfig() const;
    void setV2rockConfig(V2RockConfig *value);

private:
    V2RockConfig *v2rockConfig;

    Ui::SettingsDialog *ui;
    QTabWidget *tabWidget;
    GeneralTab *generalTab;
    ByPassIpTab *byPassIpTab;
    ByPassDomainTab * byPassDomainTab;
    QDialogButtonBox *buttonBox;

private slots:
    void accept();
    void reject();
};

#endif // SETTINGSDIALOG_H

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QMenu>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSystemTrayIcon>

#include "pingprocess.h"
#include "v2rockconfig.h"
#include "xinjieconfig.h"
#include "nodeeditdialog.h"
#include "settingsdialog.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

public slots:
    void appendLog(const QString &text);

protected:
    void showEvent(QShowEvent *ev) override;
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *event) override;

private:
    QString baseDir;
    V2RockConfig *v2rockConfig;
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    PingProcess *pingProcess;

    Ui::MainDialog *ui;
    SettingsDialog *dialogSettings;
    NodeEditDialog *dialogNodeEdit;
    QPushButton *btnImport, *btnTest, *btnStart, *btnStop, *btnSettings, *btnQuit;
    QTreeWidget *tree;
    QPlainTextEdit *logEdit;
    QGroupBox *iconGroupBox;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QList<QIcon> *icons;

    QAction *delAction;
    QAction *editAction;
    QAction *addAction;
    QAction *restoreAction;
    QAction *quitAction;

    void createTrayIcon();
    void setIcon(int index);
    void showEventHandler();
    void reloadTreeList();
    void selectTreeItem();
    void addTreeItem(const QString id, const QString name, const QString protocol, const QString host, int port);
    void updateBtnStatus(bool stopped);

private slots:
    void btnImportClickHandler();
    void btnTestClickHandler();
    void btnStartClickHandler();
    void btnStopClickHandler();
    void btnSettingsClickHandler();
    void actDelHandler();
    void actEditHandler();
    void actAddHandler();
    void contextMenu(const QPoint &point);
    void networkAccessManagerFinished(QNetworkReply *reply);
    void treeItemDoubleClicked(QTreeWidgetItem *item, int column);
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // MAINDIALOG_H

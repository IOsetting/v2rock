#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QCheckBox>
#include <QGroupBox>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "v2rockconfig.h"

namespace Ui {
class SettingsGeneralTab;
}

class SettingsGeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsGeneralTab(QWidget *parent = 0);
    ~SettingsGeneralTab();
    void init(V2RockConfig *v2rockConfig);
    QString getSubscribeUrl() const;
    QString getV2executablePath() const;

    bool isSocksChecked() const;
    QString getSocksListen() const;
    int getSocksPort() const;

    bool isHttpChecked() const;
    QString getHttpListen() const;
    int getHttpPort() const;

private:
    Ui::SettingsGeneralTab *ui;
    QLineEdit *subscribeUrlEdit;
    QLineEdit *v2executablePathEdit;

    QCheckBox *httpCheckBox;
    QLineEdit *httpListenEdit;
    QLineEdit *httpPortEdit;

    QCheckBox *socksCheckBox;
    QLineEdit *socksListenEdit;
    QLineEdit *socksPortEdit;
};

#endif // GENERALTAB_H

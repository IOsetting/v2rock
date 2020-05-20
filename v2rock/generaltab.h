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
class GeneralTab;
}

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(QWidget *parent = 0);
    ~GeneralTab();
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
    Ui::GeneralTab *ui;
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

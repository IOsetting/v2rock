#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
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
    int getLocalSocks5Port() const;
    QString getV2executablePath() const;

private:
    Ui::GeneralTab *ui;
    QLineEdit *subscribeUrlEdit;
    QLineEdit *localSocks5PortEdit;
    QLineEdit *v2executablePathEdit;
};

#endif // GENERALTAB_H

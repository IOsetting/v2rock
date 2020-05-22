#include "settingsbypassiptab.h"
#include "ui_settingsbypassiptab.h"

SettingsBypassIpTab::SettingsBypassIpTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsBypassIpTab)
{
    ui->setupUi(this);
    this->bypassIpsEdit = new QPlainTextEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Bypass IPs")));
    mainLayout->addWidget(this->bypassIpsEdit);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

SettingsBypassIpTab::~SettingsBypassIpTab()
{
    delete ui;
}

void SettingsBypassIpTab::init(V2RockConfig *v2rockConfig)
{
    bypassIpsEdit->clear();
    foreach (const QString ip, v2rockConfig->getBypassIps()) {
        bypassIpsEdit->appendPlainText(ip);
    }
}

QList<QString> SettingsBypassIpTab::getBypassIps() const
{
    QString text = bypassIpsEdit->toPlainText();
    QStringList lines = text.split("\n");
    QList<QString> list;
    for (int i = 0; i < lines.size(); i++) {
        list.append(lines.at(i));
    }
    return list;
}

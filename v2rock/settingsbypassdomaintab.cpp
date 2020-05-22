#include "settingsbypassdomaintab.h"
#include "ui_settingsbypassdomaintab.h"

SettingsBypassDomainTab::SettingsBypassDomainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsBypassDomainTab)
{
    ui->setupUi(this);
    this->bypassDomainsEdit = new QPlainTextEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Bypass Domains")));
    mainLayout->addWidget(this->bypassDomainsEdit);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

SettingsBypassDomainTab::~SettingsBypassDomainTab()
{
    delete ui;
}

void SettingsBypassDomainTab::init(V2RockConfig *v2rockConfig)
{
    bypassDomainsEdit->clear();
    foreach (const QString domain, v2rockConfig->getBypassDomains()) {
        bypassDomainsEdit->appendPlainText(domain);
    }
}

QList<QString> SettingsBypassDomainTab::getBypassDomains() const
{
    QString text = bypassDomainsEdit->toPlainText();
    QStringList lines = text.split("\n");
    QList<QString> list;
    for (int i = 0; i < lines.size(); i++) {
        list.append(lines.at(i));
    }
    return list;
}

#include "bypassdomaintab.h"
#include "ui_bypassdomaintab.h"

ByPassDomainTab::ByPassDomainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ByPassDomainTab)
{
    ui->setupUi(this);
    this->bypassDomainsEdit = new QPlainTextEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Bypass Domains")));
    mainLayout->addWidget(this->bypassDomainsEdit);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

ByPassDomainTab::~ByPassDomainTab()
{
    delete ui;
}

void ByPassDomainTab::init(V2RockConfig *v2rockConfig)
{
    bypassDomainsEdit->clear();
    foreach (const QString domain, v2rockConfig->getBypassDomains()) {
        bypassDomainsEdit->appendPlainText(domain);
    }
}

QList<QString> ByPassDomainTab::getBypassDomains() const
{
    QString text = bypassDomainsEdit->toPlainText();
    QStringList lines = text.split("\n");
    QList<QString> list;
    for (int i = 0; i < lines.size(); i++) {
        list.append(lines.at(i));
    }
    return list;
}

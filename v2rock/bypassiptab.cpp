#include "bypassiptab.h"
#include "ui_bypassiptab.h"

ByPassIpTab::ByPassIpTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ByPassIpTab)
{
    ui->setupUi(this);
    this->bypassIpsEdit = new QPlainTextEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Bypass IPs")));
    mainLayout->addWidget(this->bypassIpsEdit);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

ByPassIpTab::~ByPassIpTab()
{
    delete ui;
}

void ByPassIpTab::init(V2RockConfig *v2rockConfig)
{
    bypassIpsEdit->clear();
    foreach (const QString ip, v2rockConfig->getBypassIps()) {
        bypassIpsEdit->appendPlainText(ip);
    }
}

QList<QString> ByPassIpTab::getBypassIps() const
{
    QString text = bypassIpsEdit->toPlainText();
    QStringList lines = text.split("\n");
    QList<QString> list;
    for (int i = 0; i < lines.size(); i++) {
        list.append(lines.at(i));
    }
    return list;
}

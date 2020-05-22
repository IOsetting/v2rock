#include "nodeeditdialog.h"
#include "ui_nodeeditdialog.h"

NodeEditDialog::NodeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeEditDialog)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget;
    generalTab = new NodeEditGeneralTab();
    tabWidget->addTab(generalTab, tr("General"));
    transportTab = new NodeEditTransportTab();
    tabWidget->addTab(transportTab, tr("Transport"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Edit Node"));
}

NodeEditDialog::~NodeEditDialog()
{
    delete generalTab;
    delete transportTab;
    delete tabWidget;
    delete buttonBox;
    delete ui;
}

void NodeEditDialog::accept()
{

}

void NodeEditDialog::reject()
{
    QDialog::reject();
}

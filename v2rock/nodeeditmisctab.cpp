#include "nodeeditmisctab.h"
#include "ui_nodeeditmisctab.h"

NodeEditMiscTab::NodeEditMiscTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditMiscTab)
{
    ui->setupUi(this);
}

NodeEditMiscTab::~NodeEditMiscTab()
{
    delete ui;
}

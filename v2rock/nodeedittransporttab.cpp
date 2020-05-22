#include "nodeedittransporttab.h"
#include "ui_nodeedittransporttab.h"

NodeEditTransportTab::NodeEditTransportTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditTransportTab)
{
    ui->setupUi(this);
}

NodeEditTransportTab::~NodeEditTransportTab()
{
    delete ui;
}

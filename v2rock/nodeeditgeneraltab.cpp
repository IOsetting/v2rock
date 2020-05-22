#include "nodeeditgeneraltab.h"
#include "ui_nodeeditgeneraltab.h"

NodeEditGeneralTab::NodeEditGeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditGeneralTab)
{
    ui->setupUi(this);
}

NodeEditGeneralTab::~NodeEditGeneralTab()
{
    delete ui;
}

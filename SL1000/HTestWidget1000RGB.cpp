#include "HTestWidget1000RGB_p.h"
#include "ui_HTestWidget1000RGB.h"

HTestWidget1000RGBPrivate::HTestWidget1000RGBPrivate()
{

}

HTestWidget1000RGB::HTestWidget1000RGB(QWidget *parent) :
    HTestWidget(*new HTestWidget1000RGBPrivate, parent),
    ui(new Ui::HTestWidget1000RGB)
{
    ui->setupUi(this);
}

HTestWidget1000RGB::~HTestWidget1000RGB()
{
    delete ui;
}

void HTestWidget1000RGB::init()
{

}

void HTestWidget1000RGB::createWidget()
{

}

void HTestWidget1000RGB::createMenu()
{

}

void HTestWidget1000RGB::createToolBar()
{

}

void HTestWidget1000RGB::initWidget()
{

}

void HTestWidget1000RGB::clearResult()
{

}

void HTestWidget1000RGB::exportExcel()
{

}

void HTestWidget1000RGB::handleAction(HActionType)
{

}


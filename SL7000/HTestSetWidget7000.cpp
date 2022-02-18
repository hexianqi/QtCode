#include "HTestSetWidget7000_p.h"
#include "ui_HTestSetWidget7000.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidget7000::HTestSetWidget7000(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget7000Private, parent),
    ui(new Ui::HTestSetWidget7000)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget7000::~HTestSetWidget7000()
{
    delete ui;
}

QString HTestSetWidget7000::typeName()
{
    return "HTestSetWidget7000";
}

QVariant HTestSetWidget7000::handleOperation(QString type, QVariant value)
{

}

void HTestSetWidget7000::handleAction(HActionType action)
{

}

bool HTestSetWidget7000::setTestState(bool b)
{

}

bool HTestSetWidget7000::adjustIntegralTime()
{

}

bool HTestSetWidget7000::adjustLuminousGears()
{

}

void HTestSetWidget7000::init()
{

}

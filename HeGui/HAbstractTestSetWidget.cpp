#include "HAbstractTestSetWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HAbstractTestSetWidgetPrivate::HAbstractTestSetWidgetPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HAbstractTestSetWidget::HAbstractTestSetWidget(QWidget *parent) :
    ITestSetWidget(parent),
    d_ptr(new HAbstractTestSetWidgetPrivate)
{
}

void HAbstractTestSetWidget::initialize(QVariantMap /*param*/)
{

}

HAbstractTestSetWidget::HAbstractTestSetWidget(HAbstractTestSetWidgetPrivate &p, QWidget *parent) :
    ITestSetWidget(parent),
    d_ptr(&p)
{
}

QVariant HAbstractTestSetWidget::handleOperation(QString /*type*/, QVariant /*value*/)
{
    return false;
}

bool HAbstractTestSetWidget::setData(QString type, QVariant value)
{
    if (d_ptr->datas.contains(type) && d_ptr->datas.value(type) == value)
        return false;
    d_ptr->datas[type] = value;
    emit dataChanged(type, value);
    return true;
}

QVariant HAbstractTestSetWidget::data(QString type)
{
    return d_ptr->datas.value(type);
}

bool HAbstractTestSetWidget::setTestState(bool b)
{
    if (d_ptr->testState == b)
        return false;
    d_ptr->testState = b;
    emit testStateChanged(b);
    return true;
}

bool HAbstractTestSetWidget::testState()
{
    return d_ptr->testState;
}

bool HAbstractTestSetWidget::setTestMode(int value)
{
    if (d_ptr->testMode == value)
        return false;
    d_ptr->testMode = value;
    emit testModeChanged(value);
    return true;
}

int HAbstractTestSetWidget::testMode()
{
    return d_ptr->testMode;
}

bool HAbstractTestSetWidget::setSaveMode(int value)
{
    if (d_ptr->saveMode == value)
        return false;
    d_ptr->saveMode = value;
    emit saveModeChanged(value);
    return true;
}

int HAbstractTestSetWidget::saveMode()
{
    return d_ptr->saveMode;
}

void HAbstractTestSetWidget::setTestData(QString type, QVariant value, HActionType action, ulong delay)
{
    if (d_ptr->testData->setData(type, value))
        d_ptr->model->addAction(action, delay);
}

HE_END_NAMESPACE

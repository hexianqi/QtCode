#include "HAbstractTestSetWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"

HE_GUI_BEGIN_NAMESPACE

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

HAbstractTestSetWidget::HAbstractTestSetWidget(HAbstractTestSetWidgetPrivate &p, QWidget *parent) :
    ITestSetWidget(parent),
    d_ptr(&p)
{
}

QVariant HAbstractTestSetWidget::handleOperation(QString /*type*/, QVariant /*value*/)
{
    return false;
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

HE_GUI_END_NAMESPACE

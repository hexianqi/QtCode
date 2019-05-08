#include "HAbstractTestDetailWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractTestDetailWidgetPrivate::HAbstractTestDetailWidgetPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HAbstractTestDetailWidget::HAbstractTestDetailWidget(QWidget *parent) :
    ITestDetailWidget(parent),
    d_ptr(new HAbstractTestDetailWidgetPrivate)
{
}

HAbstractTestDetailWidget::HAbstractTestDetailWidget(HAbstractTestDetailWidgetPrivate &p, QWidget *parent) :
    ITestDetailWidget(parent),
    d_ptr(&p)
{
}

HAbstractTestDetailWidget::~HAbstractTestDetailWidget()
{
    qDebug() << __func__;
}

HE_GUI_END_NAMESPACE

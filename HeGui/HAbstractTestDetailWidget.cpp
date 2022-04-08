#include "HAbstractTestDetailWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"

HE_BEGIN_NAMESPACE

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

HAbstractTestDetailWidget::~HAbstractTestDetailWidget() = default;

void HAbstractTestDetailWidget::initialize(QVariantMap /*param*/)
{

}

void HAbstractTestDetailWidget::refreshData(QString)
{

}

void HAbstractTestDetailWidget::refreshData(QStringList type)
{
    for (auto t : type)
        refreshData(t);
}

HE_END_NAMESPACE

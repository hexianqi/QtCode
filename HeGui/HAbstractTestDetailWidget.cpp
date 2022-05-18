#include "HAbstractTestDetailWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include <QtWidgets/QLineEdit>

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

void HAbstractTestDetailWidget::refreshWidget()
{
    for (auto i = d_ptr->lineEdits.begin(); i != d_ptr->lineEdits.end(); i++)
        i.value()->setText(d_ptr->testData->toString(i.key()));
}

void HAbstractTestDetailWidget::refreshData(QString type)
{
    if (d_ptr->lineEdits.contains(type))
        d_ptr->lineEdits.value(type)->setText(d_ptr->testData->toString(type));
}

void HAbstractTestDetailWidget::refreshData(QStringList type)
{
    for (auto t : type)
        refreshData(t);
}

void HAbstractTestDetailWidget::init()
{
    initHash();
    refreshWidget();
}

HE_END_NAMESPACE

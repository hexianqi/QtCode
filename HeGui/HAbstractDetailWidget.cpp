#include "HAbstractDetailWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/ITestData.h"
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractDetailWidgetPrivate::HAbstractDetailWidgetPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HAbstractDetailWidget::HAbstractDetailWidget(QWidget *parent)
    : IDetailWidget(parent), d_ptr(new HAbstractDetailWidgetPrivate)
{
}

HAbstractDetailWidget::HAbstractDetailWidget(HAbstractDetailWidgetPrivate &p, QWidget *parent)
    : IDetailWidget(parent), d_ptr(&p)
{
}

HAbstractDetailWidget::~HAbstractDetailWidget()
{
    qDebug() << __func__;
}

void HAbstractDetailWidget::initialize(QVariantMap /*param*/)
{
}

HE_GUI_END_NAMESPACE

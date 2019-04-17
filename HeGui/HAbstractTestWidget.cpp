#include "HAbstractTestWidget_p.h"
#include "ITestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractTestWidgetPrivate::HAbstractTestWidgetPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HAbstractTestWidget::HAbstractTestWidget(QWidget *parent) :
    ITestWidget(parent),
    d_ptr(new HAbstractTestWidgetPrivate)
{
}

HAbstractTestWidget::HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent) :
    ITestWidget(parent),
    d_ptr(&p)
{
}

HAbstractTestWidget::~HAbstractTestWidget()
{
    qDebug() << __func__;
}

void HAbstractTestWidget::initialize(QVariantMap /*param*/)
{
}

QVector<QMenu *> HAbstractTestWidget::menus()
{
    return d_ptr->menus;
}

QVector<QToolBar *> HAbstractTestWidget::toolBars()
{
    return d_ptr->toolBars;
}

void HAbstractTestWidget::start()
{
    connect(d_ptr->model, &IModel::actionFinished, this, &HAbstractTestWidget::handleAction);
}

void HAbstractTestWidget::stop()
{
    setTest(false);
    d_ptr->model->disconnect(this);
}

HE_GUI_END_NAMESPACE

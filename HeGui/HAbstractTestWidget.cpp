#include "HAbstractTestWidget_p.h"
#include "ITestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeController/IMemento.h"
#include <QtGui/QCloseEvent>

HE_BEGIN_NAMESPACE

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

void HAbstractTestWidget::initialize(QVariantMap /*param*/)
{

}

HAbstractTestWidget::~HAbstractTestWidget() = default;

HAbstractTestWidget::HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent) :
    ITestWidget(parent),
    d_ptr(&p)
{
}

QList<QMenu *> HAbstractTestWidget::menus()
{
    return d_ptr->menus;
}

QList<QToolBar *> HAbstractTestWidget::toolBars()
{
    return d_ptr->toolBars;
}

void HAbstractTestWidget::start()
{
    connect(d_ptr->model, &IModel::actionFinished, this, &HAbstractTestWidget::handleAction);
    if (d_ptr->memento)
        d_ptr->memento->restore();
}

void HAbstractTestWidget::stop()
{
    setTest(false);
    d_ptr->model->disconnect(this);
    if (d_ptr->memento)
        d_ptr->memento->save();
}

void HAbstractTestWidget::closeEvent(QCloseEvent *event)
{
    stop();
    event->accept();
}

bool HAbstractTestWidget::setTest(bool b)
{
    if (d_ptr->testSetWidget == nullptr)
        return false;
    return d_ptr->testSetWidget->setTestState(b);
}

void HAbstractTestWidget::handleAction(HActionType action)
{
    if (d_ptr->testSetWidget == nullptr)
        return;
    d_ptr->testSetWidget->handleAction(action);
}

HE_END_NAMESPACE

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

HAbstractTestWidget::HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent) :
    ITestWidget(parent),
    d_ptr(&p)
{
}

HAbstractTestWidget::~HAbstractTestWidget() = default;

void HAbstractTestWidget::initialize(QVariantMap /*param*/)
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

bool HAbstractTestWidget::start()
{
    if (d_ptr->running)
        return false;

    d_ptr->running = true;
    connect(d_ptr->model, &IModel::actionFinished, this, &HAbstractTestWidget::handleAction);
    restoreState();
    return true;
}

bool HAbstractTestWidget::stop()
{
    if (!d_ptr->running)
        return false;

    setTest(false);
    saveState();
    d_ptr->model->disconnect(this);
    d_ptr->running = false;
    return true;
}

void HAbstractTestWidget::closeEvent(QCloseEvent *event)
{
    stop();
    event->accept();
}

void HAbstractTestWidget::saveState()
{
    if (d_ptr->memento)
        d_ptr->memento->save();
}

void HAbstractTestWidget::restoreState()
{
    if (d_ptr->memento)
        d_ptr->memento->restore();
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

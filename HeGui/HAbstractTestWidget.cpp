#include "HAbstractTestWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include <QtGui/QCloseEvent>
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

HAbstractTestWidget::~HAbstractTestWidget() = default;

HAbstractTestWidget::HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent) :
    ITestWidget(parent),
    d_ptr(&p)
{
}

void HAbstractTestWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << __func__;
    stop();
    event->accept();
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
}

void HAbstractTestWidget::stop()
{
    setTest(false);
    d_ptr->model->disconnect(this);
}

HE_GUI_END_NAMESPACE

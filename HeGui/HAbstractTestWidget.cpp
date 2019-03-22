#include "HAbstractTestWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractTestWidgetPrivate::HAbstractTestWidgetPrivate()
{
    testing = false;
    model = HAppContext::getContextPointer<IModel>("IModel");
}

HAbstractTestWidget::HAbstractTestWidget(QWidget *parent)
    : ITestWidget(parent), d_ptr(new HAbstractTestWidgetPrivate)
{
}

HAbstractTestWidget::HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent)
    : ITestWidget(parent), d_ptr(&p)
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
    connect(d_ptr->model, &IModel::actionFinished, this, &HAbstractTestWidget::actionDone);
}

void HAbstractTestWidget::pause()
{
    setTesting(false);
    d_ptr->model->disconnect(this);
}

bool HAbstractTestWidget::setTesting(bool b)
{
    if (d_ptr->testing == b)
        return false;
    d_ptr->testing = b;
    return true;
}

void HAbstractTestWidget::startTest()
{
    setTesting(true);
}

void HAbstractTestWidget::stopTest()
{
    setTesting(false);
}

HE_GUI_END_NAMESPACE

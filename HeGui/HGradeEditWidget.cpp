#include "HGradeEditWidget_p.h"
#include "HParallelGradeWidget.h"
#include "HSequentialGradeWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IGrade.h"
#include "HePlugin/HSelectDialog.h"
#include <QtWidgets/QStackedLayout>

HE_BEGIN_NAMESPACE

HGradeEditWidgetPrivate::HGradeEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    widgets.insert("HParallelGrade", new HParallelGradeWidget);
    widgets.insert("HSequentialGrade", new HSequentialGradeWidget);
}

HGradeEditWidget::HGradeEditWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HGradeEditWidgetPrivate)
{
    init();
}

HGradeEditWidget::~HGradeEditWidget() = default;

void HGradeEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HGradeEditWidget::typeName()
{
    return "HGradeEditWidget";
}

QWidget *HGradeEditWidget::widget()
{
    return this;
}

IGrade *HGradeEditWidget::createData()
{
    QVariantMap option;
    option.insert(tr("并行分级"), "HParallelGrade");
    option.insert(tr("连续分级"), "HSequentialGrade");

    HSelectDialog dlg(this);
    dlg.setLabelText(tr("请选择分级类型："));
    dlg.setOptional(option);
    if (!dlg.exec())
        return nullptr;
    return d_ptr->factory->createGrade(dlg.currentData().toString());
}

void HGradeEditWidget::setData(IGrade *p)
{
    d_ptr->current = d_ptr->widgets.value(p->typeName());
    if (d_ptr->current)
    {
        d_ptr->current->setData(p);
        d_ptr->layout->setCurrentWidget(d_ptr->current);
    }
}

void HGradeEditWidget::clearData()
{
    for (auto w : d_ptr->widgets)
        w->clearData();
}

void HGradeEditWidget::saveData()
{
    if (d_ptr->current == nullptr)
        return;
    d_ptr->current->saveData();
}

void HGradeEditWidget::showData()
{
    if (d_ptr->current == nullptr)
        return;
    d_ptr->current->showData();
}

void HGradeEditWidget::init()
{
    d_ptr->layout = new QStackedLayout(this);
    for (auto w : d_ptr->widgets)
        d_ptr->layout->addWidget(w);
}

HE_END_NAMESPACE

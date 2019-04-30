#include "HGradeDetailWidget_p.h"
#include "HGradeEditWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeDetailWidget::HGradeDetailWidget(QWidget *parent) :
    HAbstractDataDetailWidget<IGrade>(*new HGradeDetailWidgetPrivate, parent)
{
    init();
}

HGradeDetailWidget::~HGradeDetailWidget()
{
    qDebug() << __func__;
}

void HGradeDetailWidget::initialize(QVariantMap /*param*/)
{
}

QString HGradeDetailWidget::typeName()
{
    return "HGradeDetailWidget";
}

void HGradeDetailWidget::init()
{
    Q_D(HGradeDetailWidget);
    d->widget = new HGradeEditWidget;
    auto layout = new QGridLayout(this);
    layout->addWidget(d->widget);
}

HE_GUI_END_NAMESPACE

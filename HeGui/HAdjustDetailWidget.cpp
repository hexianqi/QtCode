#include "HAdjustDetailWidget_p.h"
#include "HAdjustEditWidget.h"
#include "HAdjustEditDialog.h"
#include "HSimpleTestSetWidget.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustDetailWidget::HAdjustDetailWidget(QWidget *parent) :
    HAbstractDataDetailWidget<IAdjust>(*new HAdjustDetailWidgetPrivate, parent)
{
    init();
}

HAdjustDetailWidget::~HAdjustDetailWidget()
{
    qDebug() << __func__;
}

void HAdjustDetailWidget::initialize(QVariantMap /*param*/)
{
}

QString HAdjustDetailWidget::typeName()
{
    return "HAdjustDetailWidget";
}

void HAdjustDetailWidget::init()
{
    Q_D(HAdjustDetailWidget);
    d->actionEdit = new QAction(tr("编辑(&E)..."), this);
    d->widget = new HAdjustEditWidget;
    d->widget->setContextMenuPolicy(Qt::ActionsContextMenu);
    d->widget->addAction(d->actionEdit);
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(d->widget);
    connect(d->actionEdit, &QAction::triggered, this, &HAdjustDetailWidget::editData);
}

void HAdjustDetailWidget::editData()
{
    Q_D(HAdjustDetailWidget);
    if (d->data == nullptr)
        return;
    HAdjustEditDialog dlg(this);
    dlg.setTestSetWidget(new HSimpleTestSetWidget(this));
    dlg.setData(d->data);
    dlg.exec();
    d->widget->setData(d->data);
}

HE_GUI_END_NAMESPACE

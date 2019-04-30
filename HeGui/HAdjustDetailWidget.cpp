#include "HAdjustDetailWidget_p.h"
#include "HAdjustEditDialog.h"
#include "HSimpleTestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/IAdjust.h"
#include "HeData/IAdjustItem.h"
#include "HeData/IAdjustCollection.h"
#include "HePlugin/HEntireTableWidget.h"
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustDetailWidgetPrivate::HAdjustDetailWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HAdjustDetailWidget::HAdjustDetailWidget(QWidget *parent) :
    IItemDetailWidget(parent),
    d_ptr(new HAdjustDetailWidgetPrivate)
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

void HAdjustDetailWidget::start()
{
    if (d_ptr->adjusts != nullptr)
        emit sourceChanged(d_ptr->adjusts->keys(), d_ptr->adjusts->useIndex());
}

void HAdjustDetailWidget::importFile()
{
    if (d_ptr->adjusts->fileStream()->openFile())
        emit sourceChanged(d_ptr->adjusts->keys(), d_ptr->adjusts->useIndex());
}

void HAdjustDetailWidget::exportFile()
{
    d_ptr->adjusts->fileStream()->saveAsFile();
}

void HAdjustDetailWidget::addItem(QString name)
{
    auto item = d_ptr->factory->createAdjust("HAdjust");
    d_ptr->adjusts->insert(name, item);
    emit sourceChanged(d_ptr->adjusts->keys(), name);
}

void HAdjustDetailWidget::delItem(QString name)
{
    if (d_ptr->adjusts->remove(name) > 0)
        emit sourceChanged(d_ptr->adjusts->keys(), name);
}

void HAdjustDetailWidget::setCurrentItem(QString name)
{
    if (name.isEmpty() || !d_ptr->adjusts->contains(name))
    {
        clearData();
        return;
    }
    d_ptr->adjusts->setUseIndex(name);
    d_ptr->adjust = d_ptr->adjusts->value(name);
    if (d_ptr->adjust->isEmpty())
        editData();
    else
        showData();
}

void HAdjustDetailWidget::setData(IAdjustCollection *d)
{
    if (d_ptr->adjusts == d)
        return;
    d_ptr->adjusts = d;
    emit sourceChanged(d_ptr->adjusts->keys(), d_ptr->adjusts->useIndex());
}

void HAdjustDetailWidget::clearData()
{
    d_ptr->adjust = nullptr;
    d_ptr->tableWidget->clearContents();
    d_ptr->tableWidget->setRowCount(0);
}

void HAdjustDetailWidget::showData()
{
    int r = 0;
    d_ptr->tableWidget->setRowCount(d_ptr->adjust->size());
    for (auto key : d_ptr->adjust->keys())
    {
        d_ptr->tableWidget->setRow(r, d_ptr->adjust->item(key)->toStringList());
        r++;
    }
}

void HAdjustDetailWidget::editData()
{
    if (d_ptr->adjust == nullptr)
        return;
    HAdjustEditDialog dlg(this);
    dlg.setTestSetWidget(new HSimpleTestSetWidget(this));
    dlg.setData(d_ptr->adjust);
    dlg.exec();
    showData();
}

void HAdjustDetailWidget::init()
{
    d_ptr->tableWidget = new HEntireTableWidget;
    d_ptr->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("调整比率") << tr("测试值") << tr("标准值"));
    d_ptr->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    d_ptr->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto layout = new QGridLayout(this);
    layout->addWidget(d_ptr->tableWidget);
    resize(600, 400);
    connect(d_ptr->tableWidget, &HEntireTableWidget::doubleClicked, this, &HAdjustDetailWidget::editData);
}



HE_GUI_END_NAMESPACE

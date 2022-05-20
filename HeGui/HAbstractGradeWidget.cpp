#include "HAbstractGradeWidget_p.h"
#include "HGradeItemDialog.h"
#include "HGradeItem2DDialog.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include "HeData/IDataFactory.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HAbstractGradeWidgetPrivate::HAbstractGradeWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optional = HAppContext::getContextValue<QStringList>("GradeOptional");
}

HAbstractGradeWidget::HAbstractGradeWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractGradeWidgetPrivate)
{
}

HAbstractGradeWidget::HAbstractGradeWidget(HAbstractGradeWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HAbstractGradeWidget::~HAbstractGradeWidget()
{
}

void HAbstractGradeWidget::setData(IGrade *p)
{
    d_ptr->data = p;
    showData();
}

void HAbstractGradeWidget::clearData()
{
    d_ptr->data = nullptr;
}

bool HAbstractGradeWidget::saveData()
{
    if (!d_ptr->modified)
        return false;
    d_ptr->modified = false;
    return true;
}

bool HAbstractGradeWidget::showData()
{
    if (d_ptr->data == nullptr)
        return false;

    d_ptr->modified = false;
    d_ptr->selected = d_ptr->data != nullptr ? d_ptr->data->keys() : QStringList();
    d_ptr->unselected = HCoreHelper::unselected(d_ptr->optional, d_ptr->selected);

    QMap<int, IGradeItem *> map;
    for (auto v : d_ptr->data->values())
    {
        auto priority = v->data("[优先级]").toInt() * 100;
        while (map.contains(priority))
            priority++;
        map.insert(priority, v);
    }
    d_ptr->items = map.values();
    return true;
}

void HAbstractGradeWidget::insertGradeItem()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselected, type))
        return;

    auto className = type == "[色坐标]" ? "HGradeItem2D" : "HGradeItem";
    auto item = d_ptr->factory->createGradeItem(className);
    item->setData("[项类型]", type);
    d_ptr->data->insert(type, item);
    editGradeItem(type);
    showData();
}

void HAbstractGradeWidget::removeGradeItem()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selected, type))
        return;
    d_ptr->data->remove(type);
    showData();
}

void HAbstractGradeWidget::editGradeItem()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selected, type))
        return;
    if (!editGradeItem(type))
        return;
    showData();
}

bool HAbstractGradeWidget::editGradeItem(const QString &type)
{
    HAbstractGradeItemDialog *dlg;
    auto item = d_ptr->data->value(type);
    if (item->typeName() == "HGradeItem2D")
        dlg = new HGradeItem2DDialog(this);
    else
        dlg = new HGradeItemDialog(this);
    dlg->setData(item);
    return dlg->exec() == QDialog::Accepted;
}

HE_END_NAMESPACE

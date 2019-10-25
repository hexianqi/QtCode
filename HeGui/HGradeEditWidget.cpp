#include "HGradeEditWidget_p.h"
#include "ui_HGradeEditWidget.h"
#include "HGradeItemDialog.h"
#include "HGradeItem2DDialog.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeEditWidgetPrivate::HGradeEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("GradeOptionals");
}

HGradeEditWidget::HGradeEditWidget(QWidget *parent) :
    IDataEditWidget(parent),
    d_ptr(new HGradeEditWidgetPrivate),
    ui(new Ui::HGradeEditWidget)
{
    ui->setupUi(this);
}

HGradeEditWidget::~HGradeEditWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HGradeEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HGradeEditWidget::typeName()
{
    return "HGradeEditWidget";
}

IGrade *HGradeEditWidget::createData()
{
    return d_ptr->factory->createGrade("HParallelGrade");
}

void HGradeEditWidget::setData(IGrade *p)
{
    d_ptr->data = p;
    showData();
}

void HGradeEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(0));
}

void HGradeEditWidget::saveData()
{

}

void HGradeEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;

    d_ptr->selecteds = d_ptr->data != nullptr ? d_ptr->data->keys() : QStringList();
    d_ptr->unselecteds = HCoreHelper::unselected(d_ptr->optionals, d_ptr->selecteds);

    int count = 0;
    int total = 1;
    QMap<int, IGradeItem *> map;
    for (auto i : d_ptr->data->values())
    {
        auto priority = i->data("[优先级]").toInt();
        if (map.contains(priority))
            priority++;
        map.insert(priority, i);
        count = qMax(count, i->count());
        total *= i->count();
    }
    if (count == 0)
        total = 0;

    QStringList headers, types;
    for (auto item : map)
    {
        headers << item->headers();
        types << item->types();
    }

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(types);

    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(total));
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setItemDelegate(delegate);
    ui->tableWidget->setRowCount(count);
    for (int i = 0; i < count; i++)
    {
        QStringList l;
        for (auto item : map)
            l << item->level(i);
        ui->tableWidget->setRow(i, l);
    }
}

bool HGradeEditWidget::editData(QString type)
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

void HGradeEditWidget::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    auto className = type == "[色坐标]" ? "HGradeItem2D" : "HGradeItem";
    auto item = d_ptr->factory->createGradeItem(className);
    item->setData("[项类型]", type);
    d_ptr->data->insert(type, item);
    editData(type);
    showData();
}

void HGradeEditWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    d_ptr->data->remove(type);
    showData();
}

void HGradeEditWidget::on_pushButton_3_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    if (!editData(type))
        return;
    showData();
}

HE_GUI_END_NAMESPACE

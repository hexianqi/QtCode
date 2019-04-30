#include "HGradeDetailWidget_p.h"
#include "ui_HGradeDetailWidget.h"
#include "HGradeItemDialog.h"
#include "HGradeItem2DDialog.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IFileStream.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HeData/IGradeCollection.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeDetailWidgetPrivate::HGradeDetailWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("GradeOptionals");
}

HGradeDetailWidget::HGradeDetailWidget(QWidget *parent) :
    IItemDetailWidget(parent),
    d_ptr(new HGradeDetailWidgetPrivate),
    ui(new Ui::HGradeDetailWidget)
{
    ui->setupUi(this);
}

HGradeDetailWidget::~HGradeDetailWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HGradeDetailWidget::initialize(QVariantMap /*param*/)
{
}

QString HGradeDetailWidget::typeName()
{
    return "HGradeDetailWidget";
}

void HGradeDetailWidget::start()
{
    if (d_ptr->grades != nullptr)
        emit sourceChanged(d_ptr->grades->keys(), d_ptr->grades->useIndex());
}

void HGradeDetailWidget::importFile()
{
    if (d_ptr->grades->fileStream()->openFile())
        emit sourceChanged(d_ptr->grades->keys(), d_ptr->grades->useIndex());
}

void HGradeDetailWidget::exportFile()
{
    d_ptr->grades->fileStream()->saveAsFile();
}

void HGradeDetailWidget::addItem(QString name)
{
    auto item = d_ptr->factory->createGrade("HParallelGrade");
    d_ptr->grades->insert(name, item);
    emit sourceChanged(d_ptr->grades->keys(), name);
}

void HGradeDetailWidget::delItem(QString name)
{
    if (d_ptr->grades->remove(name) > 0)
        emit sourceChanged(d_ptr->grades->keys(), name);
}

void HGradeDetailWidget::setCurrentItem(QString name)
{
    if (name.isEmpty() || !d_ptr->grades->contains(name))
    {
        clearData();
        return;
    }
    d_ptr->grades->setUseIndex(name);
    d_ptr->grade = d_ptr->grades->value(name);
    showData();
}

void HGradeDetailWidget::setData(IGradeCollection *d)
{
    if (d_ptr->grades == d)
        return;
    d_ptr->grades = d;
    emit sourceChanged(d_ptr->grades->keys(), d_ptr->grades->useIndex());
}

void HGradeDetailWidget::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    auto className = type == "[色坐标]" ? "HGradeItem2D" : "HGradeItem";
    auto item = d_ptr->factory->createGradeItem(className);
    item->setData("[项类型]", type);
    d_ptr->grade->insert(type, item);
    editGradeItem(type);
    showData();
}

void HGradeDetailWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    d_ptr->grade->remove(type);
    showData();
}

void HGradeDetailWidget::on_pushButton_3_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    if (!editGradeItem(type))
        return;
    showData();
}

void HGradeDetailWidget::clearData()
{
    d_ptr->grade = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(0));
}

void HGradeDetailWidget::showData()
{
    d_ptr->selecteds = d_ptr->grade != nullptr ? d_ptr->grade->keys() : QStringList();
    d_ptr->unselecteds = d_ptr->optionals;
    for (auto s : d_ptr->selecteds)
        d_ptr->unselecteds.removeAll(s);

    int count = 0;
    int total = 1;
    QMap<int, IGradeItem *> map;
    for (auto i : d_ptr->grade->values())
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

bool HGradeDetailWidget::editGradeItem(QString type)
{
    HAbstractGradeItemDialog *dlg;
    auto item = d_ptr->grade->value(type);
    if (item->typeName() == "HGradeItem2D")
        dlg = new HGradeItem2DDialog(this);
    else
        dlg = new HGradeItemDialog(this);
    dlg->setData(item);
    return dlg->exec() == QDialog::Accepted;
}

HE_GUI_END_NAMESPACE

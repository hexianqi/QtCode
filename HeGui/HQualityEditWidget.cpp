#include "HQualityEditWidget_p.h"
#include "ui_HQualityEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include "HeData/IDataFactory.h"
#include "HeData/IQuality.h"
#include "HeData/IQualityItem.h"
#include "HeData/IQualityItemCollection.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtWidgets/QColorDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityEditWidgetPrivate::HQualityEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("QualityOptionals");
}

HQualityEditWidget::HQualityEditWidget(QWidget *parent) :
    IDataEditWidget(parent),
    d_ptr(new HQualityEditWidgetPrivate),
    ui(new Ui::HQualityEditWidget)
{
    ui->setupUi(this);
    init();
}

HQualityEditWidget::~HQualityEditWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HQualityEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HQualityEditWidget::typeName()
{
    return "HQualityEditWidget";
}

IQuality *HQualityEditWidget::createData()
{
    return d_ptr->factory->createQuality("HQuality");
}

void HQualityEditWidget::setData(IQuality *p)
{
    d_ptr->data = p;
    d_ptr->colorInvalidData = d_ptr->data->color(HQualityReport::InvalidData);
    d_ptr->colorDamage = d_ptr->data->color(HQualityReport::Damage);
    d_ptr->colorNoPass = d_ptr->data->color(HQualityReport::NoPass);
    d_ptr->colorPassing = d_ptr->data->color(HQualityReport::Passing);
    initSelected(IQuality::QualityDamage);
    initSelected(IQuality::QualityCriterion);
    showData();
}

void HQualityEditWidget::clearData()
{
    d_ptr->data = nullptr;
    d_ptr->colorInvalidData = Qt::white;
    d_ptr->colorDamage = Qt::white;
    d_ptr->colorNoPass = Qt::white;
    d_ptr->colorPassing = Qt::white;
    ui->tableWidget_11->clearContents();
    ui->tableWidget_11->setRowCount(0);
    ui->tableWidget_21->clearContents();
    ui->tableWidget_21->setRowCount(0);
    showPushButton();
}

void HQualityEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;
    d_ptr->data->setColor(HQualityReport::InvalidData, d_ptr->colorInvalidData);
    d_ptr->data->setColor(HQualityReport::Damage, d_ptr->colorDamage);
    d_ptr->data->setColor(HQualityReport::NoPass, d_ptr->colorNoPass);
    d_ptr->data->setColor(HQualityReport::Passing, d_ptr->colorPassing);
    saveTable(IQuality::QualityDamage);
    saveTable(IQuality::QualityCriterion);
}

void HQualityEditWidget::showData()
{
    showPushButton();
    showTable(IQuality::QualityDamage);
    showTable(IQuality::QualityCriterion);
}

void HQualityEditWidget::showPushButton()
{
    ui->pushButton_01->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);").arg(d_ptr->colorInvalidData.name()));
    ui->pushButton_02->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);").arg(d_ptr->colorDamage.name()));
    ui->pushButton_03->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);").arg(d_ptr->colorNoPass.name()));
    ui->pushButton_04->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);").arg(d_ptr->colorPassing.name()));
}

void HQualityEditWidget::initSelected(IQuality::QualityType type)
{
    d_ptr->selecteds[type] = d_ptr->data->itemCollection(type)->keys();
    d_ptr->unselecteds[type] = HCoreHelper::unselected(d_ptr->optionals, d_ptr->selecteds[type]);
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d_ptr->selecteds[type]);
    delegate->setOrientation(Qt::Vertical);
    auto widget = d_ptr->tableWidgets.value(type);
    widget->setItemDelegateForColumn(1, delegate);
    widget->setItemDelegateForColumn(2, delegate);
    widget->setRowCount(d_ptr->selecteds[type].size());
    if (type == IQuality::QualityDamage)
        ui->pushButton_12->setEnabled(!d_ptr->selecteds[type].isEmpty());
    else
        ui->pushButton_22->setEnabled(!d_ptr->selecteds[type].isEmpty());
}

void HQualityEditWidget::showTable(IQuality::QualityType type)
{
    auto collect = d_ptr->data->itemCollection(type);
    auto widget = d_ptr->tableWidgets.value(type);;
    int r = 0;
    for (auto key : collect->keys())
    {
        auto value = collect->item(key);
        auto item = widget->item(r, 0);
        item->setData(Qt::UserRole, key);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item = widget->item(r, 3);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setBackgroundColor(value->data("[不足颜色]").value<QColor>());
        item = widget->item(r, 4);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setBackgroundColor(value->data("[超出颜色]").value<QColor>());
        widget->setRow(r, value->toStringList());
        r++;
    }
}

void HQualityEditWidget::saveTable(IQuality::QualityType type)
{
    auto collect = d_ptr->data->itemCollection(type);
    auto widget = d_ptr->tableWidgets.value(type);
    for (int i = 0; i < widget->rowCount(); i++)
    {
        auto key = widget->item(i, 0)->data(Qt::UserRole).toString();
        auto value = collect->item(key);
        value->setData("[有效范围]", QPointF(widget->item(i, 1)->text().toDouble(), widget->item(i, 2)->text().toDouble()));
        value->setData("[不足颜色]", widget->item(i, 3)->backgroundColor());
        value->setData("[超出颜色]", widget->item(i, 4)->backgroundColor());
    }
}

void HQualityEditWidget::addItem(IQuality::QualityType type)
{
    QString t;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds[type], t))
        return;

    saveTable(type);
    auto item = d_ptr->factory->createQualityItem("HQualityItem");
    item->setData("[项类型]", t);
    item->restoreDefault();
    d_ptr->data->itemCollection(type)->insert(t, item);
    initSelected(type);
    showTable(type);
}

void HQualityEditWidget::removeItem(IQuality::QualityType type)
{
    QString t;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds[type], t))
        return;

    saveTable(type);
    d_ptr->data->itemCollection(type)->remove(t);
    initSelected(type);
    showTable(type);
}

void HQualityEditWidget::editColor(IQuality::QualityType type, int row, int column)
{
    if (d_ptr->data == nullptr || column < 2)
        return;
    auto item = d_ptr->tableWidgets.value(type)->item(row, column);
    QColorDialog dlg(item->backgroundColor(), this);
    if (dlg.exec())
    {
        item->setBackgroundColor(dlg.currentColor());
        item->setText(dlg.currentColor().name().toUpper());
    }
}

void HQualityEditWidget::on_pushButton_01_clicked()
{
    QColorDialog dlg(d_ptr->colorInvalidData, this);
    if (dlg.exec())
    {
        d_ptr->colorInvalidData = dlg.currentColor();
        ui->pushButton_01->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);\n").arg(d_ptr->colorInvalidData.name()));
    }
}

void HQualityEditWidget::on_pushButton_02_clicked()
{
    QColorDialog dlg(d_ptr->colorDamage, this);
    if (dlg.exec())
    {
        d_ptr->colorDamage = dlg.currentColor();
        ui->pushButton_02->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);\n").arg(d_ptr->colorDamage.name()));
    }
}

void HQualityEditWidget::on_pushButton_03_clicked()
{
    QColorDialog dlg(d_ptr->colorNoPass, this);
    if (dlg.exec())
    {
        d_ptr->colorNoPass = dlg.currentColor();
        ui->pushButton_03->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);\n").arg(d_ptr->colorNoPass.name()));
    }
}

void HQualityEditWidget::on_pushButton_04_clicked()
{
    QColorDialog dlg(d_ptr->colorPassing, this);
    if (dlg.exec())
    {
        d_ptr->colorPassing = dlg.currentColor();
        ui->pushButton_04->setStyleSheet(QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);\n").arg(d_ptr->colorPassing.name()));
    }
}

void HQualityEditWidget::on_pushButton_11_clicked()
{
    addItem(IQuality::QualityDamage);
}

void HQualityEditWidget::on_pushButton_12_clicked()
{
    removeItem(IQuality::QualityDamage);
}

void HQualityEditWidget::on_pushButton_21_clicked()
{
    addItem(IQuality::QualityCriterion);
}

void HQualityEditWidget::on_pushButton_22_clicked()
{
    removeItem(IQuality::QualityCriterion);
}

void HQualityEditWidget::on_tableWidget_11_cellDoubleClicked(int row, int column)
{
    editColor(IQuality::QualityDamage, row, column);
}

void HQualityEditWidget::on_tableWidget_21_cellDoubleClicked(int row, int column)
{
    editColor(IQuality::QualityCriterion, row, column);
}

void HQualityEditWidget::init()
{
    d_ptr->selecteds.insert(IQuality::QualityDamage, QStringList());
    d_ptr->selecteds.insert(IQuality::QualityCriterion, QStringList());
    d_ptr->unselecteds.insert(IQuality::QualityDamage, QStringList());
    d_ptr->unselecteds.insert(IQuality::QualityCriterion, QStringList());
    d_ptr->tableWidgets.insert(IQuality::QualityDamage, ui->tableWidget_11);
    d_ptr->tableWidgets.insert(IQuality::QualityCriterion, ui->tableWidget_21);
    ui->tableWidget_11->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("MIN") << tr("MAX") << tr("不足颜色") << tr("超出颜色")) ;
    ui->tableWidget_11->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_21->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("MIN") << tr("MAX") << tr("不足颜色") << tr("超出颜色")) ;
    ui->tableWidget_21->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    showPushButton();
}

HE_GUI_END_NAMESPACE

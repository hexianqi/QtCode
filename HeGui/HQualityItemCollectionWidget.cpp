#include "HQualityItemCollectionWidget_p.h"
#include "ui_HQualityItemCollectionWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include "HeData/IDataFactory.h"
#include "HeData/IQualityItem.h"
#include "HeData/IQualityItemCollection.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtWidgets/QColorDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityItemCollectionPrivate::HQualityItemCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("QualityOptionals");
}

HQualityItemCollectionWidget::HQualityItemCollectionWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HQualityItemCollectionPrivate),
    ui(new Ui::HQualityItemCollectionWidget)
{
    ui->setupUi(this);
    init();
}

HQualityItemCollectionWidget::~HQualityItemCollectionWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HQualityItemCollectionWidget::setData(IQualityItemCollection *p)
{
    d_ptr->data = p;
    initSelected();
}

void HQualityItemCollectionWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HQualityItemCollectionWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;

    int r = 0;
    for (auto key : d_ptr->data->keys())
    {
        auto value = d_ptr->data->item(key);
        auto item = ui->tableWidget->item(r, 0);
        item->setData(Qt::UserRole, key);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item = ui->tableWidget->item(r, 3);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setBackgroundColor(value->data("[不足颜色]").value<QColor>());
        item = ui->tableWidget->item(r, 4);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setBackgroundColor(value->data("[超出颜色]").value<QColor>());
        ui->tableWidget->setRow(r, value->toStringList());
        r++;
    }
}

void HQualityItemCollectionWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
        auto value = d_ptr->data->item(key);
        value->setData("[有效范围]", QPointF(ui->tableWidget->item(i, 1)->text().toDouble(), ui->tableWidget->item(i, 2)->text().toDouble()));
        value->setData("[不足颜色]", ui->tableWidget->item(i, 3)->backgroundColor());
        value->setData("[超出颜色]", ui->tableWidget->item(i, 4)->backgroundColor());
    }
}

void HQualityItemCollectionWidget::on_pushButton_1_clicked()
{
    QString t;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, t))
        return;

    saveData();
    auto item = d_ptr->factory->createQualityItem("HQualityItem");
    item->setData("[项类型]", t);
    item->restoreDefault();
    d_ptr->data->insert(t, item);
    initSelected();
    showData();
}

void HQualityItemCollectionWidget::on_pushButton_2_clicked()
{
    QString t;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, t))
        return;

    saveData();
    d_ptr->data->remove(t);
    initSelected();
    showData();
}

void HQualityItemCollectionWidget::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if (d_ptr->data == nullptr || column < 2)
        return;
    auto item = ui->tableWidget->item(row, column);
    QColorDialog dlg(item->backgroundColor(), this);
    if (dlg.exec())
    {
        item->setBackgroundColor(dlg.currentColor());
        item->setText(dlg.currentColor().name().toUpper());
    }
}

void HQualityItemCollectionWidget::init()
{
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("MIN") << tr("MAX") << tr("不足颜色") << tr("超出颜色")) ;
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

void HQualityItemCollectionWidget::initSelected()
{
    d_ptr->selecteds = d_ptr->data->keys();
    d_ptr->unselecteds = HCoreHelper::unselected(d_ptr->optionals, d_ptr->selecteds);
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d_ptr->selecteds);
    delegate->setOrientation(Qt::Vertical);
    ui->tableWidget->setItemDelegateForColumn(1, delegate);
    ui->tableWidget->setItemDelegateForColumn(2, delegate);
    ui->tableWidget->setRowCount(d_ptr->selecteds.size());
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
}

HE_GUI_END_NAMESPACE

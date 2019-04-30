#include "HAdjustEditDialog_p.h"
#include "ui_HAdjustEditDialog.h"
#include "ITestSetWidget.h"
#include "HSpecEnergyWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IAdjust.h"
#include "HeData/IAdjustItem.h"
#include "HeController/IModel.h"
#include "HeController/ITestData.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustEditDialogPrivate::HAdjustEditDialogPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    optionals = HAppContext::getContextValue<QStringList>("AdjustOptionals");
}

HAdjustEditDialog::HAdjustEditDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HAdjustEditDialogPrivate),
    ui(new Ui::HAdjustEditDialog)
{
    ui->setupUi(this);
    init();
}

HAdjustEditDialog::~HAdjustEditDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HeGui::HAdjustEditDialog::setData(IAdjust *p)
{
    d_ptr->data = p;
    initSelected();
    showData();
}

void HAdjustEditDialog::setTestSetWidget(ITestSetWidget *p)
{
    d_ptr->testSetWidget = p;
    ui->groupBox_3->layout()->addWidget(d_ptr->testSetWidget);
    connect(d_ptr->testSetWidget, &ITestSetWidget::testStateChanged, this, [&](bool b){ ui->groupBox_2->setEnabled(!b); });
}

void HAdjustEditDialog::done(int result)
{
    saveData();
    QDialog::done(result);
}

void HAdjustEditDialog::handleAction(HActionType action)
{
    if (action == ACT_GET_SPECTRUM)
    {
        d_ptr->energyWidget->refreshWidget();
        ui->tableWidget->setColumn(2, d_ptr->testData->toString(d_ptr->selecteds));
    }
    d_ptr->testSetWidget->handleAction(action);
}

void HAdjustEditDialog::initSelected()
{
    d_ptr->selecteds = d_ptr->data->keys();
    d_ptr->unselecteds = d_ptr->optionals;
    for (auto s : d_ptr->selecteds)
        d_ptr->unselecteds.removeAll(s);

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d_ptr->selecteds);
    delegate->setOrientation(Qt::Vertical);
    ui->tableWidget->setItemDelegateForColumn(2, delegate);
    ui->tableWidget->setItemDelegateForColumn(3, delegate);
    ui->tableWidget->setRowCount(d_ptr->selecteds.size());
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_4->setEnabled(!d_ptr->selecteds.isEmpty());
}

void HAdjustEditDialog::showData()
{
    int r = 0;
    for (auto key : d_ptr->data->keys())
    {
        auto item = ui->tableWidget->item(r, 0);
        item->setData(Qt::UserRole, key);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setRow(r, d_ptr->data->item(key)->toStringList());
        r++;
    }
}

void HAdjustEditDialog::saveData()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
        auto item = d_ptr->data->item(key);
        item->setData("[调整比率]", ui->tableWidget->item(i, 1)->text().toDouble());
        item->setData("[测试值]", ui->tableWidget->item(i, 2)->text().toDouble());
        item->setData("[标准值]", ui->tableWidget->item(i, 3)->text().toDouble());
    }
}

void HAdjustEditDialog::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    saveData();
    auto item = d_ptr->factory->createAdjustItem("HAdjustItem");
    item->setData("[项类型]", type);
    item->restoreDefault();
    d_ptr->data->insert(type, item);
    initSelected();
    showData();
}

void HAdjustEditDialog::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    saveData();
    d_ptr->data->remove(type);
    initSelected();
    showData();
}

void HAdjustEditDialog::on_pushButton_3_clicked()
{
    d_ptr->data->restoreDefault();
    showData();
}

void HAdjustEditDialog::on_pushButton_4_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto d1 = ui->tableWidget->item(i, 2)->text().toDouble();
        auto d2 = ui->tableWidget->item(i, 3)->text().toDouble();
        auto r = qFuzzyIsNull(d1) ? 100 : d2 / d1;
        ui->tableWidget->item(i, 1)->setText(toString("[调整比率]", r));
    }
}

void HAdjustEditDialog::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType("[调整比率]");
    d_ptr->energyWidget = new HSpecEnergyWidget;
    ui->groupBox_1->layout()->addWidget(d_ptr->energyWidget);
    ui->splitter_1->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(0,1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("调整比率") << tr("测试值") << tr("标准值"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setItemDelegateForColumn(1, delegate);
    connect(d_ptr->model, &IModel::actionFinished, this, &HAdjustEditDialog::handleAction);
}

HE_GUI_END_NAMESPACE

#include "HAdjustEditWidget_p.h"
#include "ui_HAdjustEditWidget.h"
#include "IGuiFactory.h"
#include "ITestSetWidget.h"
#include "HSpecEnergyWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IAdjust.h"
#include "HeData/IAdjustItem.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HeController/IModel.h"
#include <QtWidgets/QAction>

HE_BEGIN_NAMESPACE

HAdjustEditWidgetPrivate::HAdjustEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("AdjustOptionals");
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");

    auto f = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    auto t = HAppContext::getContextValue<QString>("AdjustSetWidgetType");
    if (t.isEmpty())
        t = "HAdjustSetWidget";
    energyWidget = new HSpecEnergyWidget;
    testSetWidget = f->createTestSetWidget(t);
}

HAdjustEditWidget::HAdjustEditWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAdjustEditWidgetPrivate),
    ui(new Ui::HAdjustEditWidget)
{
    ui->setupUi(this);
    init();
}

HAdjustEditWidget::~HAdjustEditWidget()
{
    disconnect(d_ptr->model, &IModel::actionFinished, this, &HAdjustEditWidget::handleAction);
    delete ui;
}

void HAdjustEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HAdjustEditWidget::typeName()
{
    return "HAdjustEditWidget";
}

QWidget *HAdjustEditWidget::widget()
{
    return this;
}

IAdjust *HAdjustEditWidget::createData()
{
    return d_ptr->factory->createAdjust("HAdjust");
}

void HAdjustEditWidget::setData(IAdjust *p)
{
    d_ptr->data = p;
    initSelected();
    showData();
}

void HAdjustEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HAdjustEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->verticalHeaderItem(i)->data(Qt::UserRole).toString();
        auto value = d_ptr->data->item(key);
        value->setData("[调整比率]", ui->tableWidget->item(i, 0)->text().toDouble());
        value->setData("[测试值]", ui->tableWidget->item(i, 1)->text().toDouble());
        value->setData("[标准值]", ui->tableWidget->item(i, 2)->text().toDouble());
    }
}

void HAdjustEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;

    int r = 0;
    for (const auto &key : d_ptr->data->keys())
    {
        auto item = new QTableWidgetItem;
        item->setData(Qt::UserRole, key);
        item->setData(Qt::DisplayRole, HCore::toCaption(key));
        ui->tableWidget->setVerticalHeaderItem(r, item);
        ui->tableWidget->setRow(r, d_ptr->data->item(key)->toStringList());
        r++;
    }
}

void HAdjustEditWidget::handleAction(HActionType action)
{
    d_ptr->testSetWidget->handleAction(action);
}

void HAdjustEditWidget::handleStateChanged(bool b)
{
    ui->groupBox_2->setEnabled(!b);
}

void HAdjustEditWidget::handleResultChanged()
{
    d_ptr->energyWidget->refreshWidget();
    ui->tableWidget->setColumn(1, d_ptr->testData->toString(d_ptr->selecteds));
}

void HAdjustEditWidget::on_pushButton_1_clicked()
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

void HAdjustEditWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    saveData();
    d_ptr->data->remove(type);
    initSelected();
    showData();
}

void HAdjustEditWidget::on_pushButton_3_clicked()
{
    d_ptr->data->restoreDefault();
    showData();
}

void HAdjustEditWidget::on_pushButton_4_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto d1 = ui->tableWidget->item(i, 1)->text().toDouble();
        auto d2 = ui->tableWidget->item(i, 2)->text().toDouble();
        auto r = qFuzzyIsNull(d1) ? 100 : 100 * d2 / d1;
        ui->tableWidget->item(i, 0)->setText(HCore::toString("[调整比率]", r));
    }
}

void HAdjustEditWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType("[调整比率]");
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("调整比率") << tr("测试值") << tr("标准值"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setItemDelegateForColumn(0, delegate);
    ui->groupBox_1->layout()->addWidget(d_ptr->energyWidget);
    ui->groupBox_3->layout()->addWidget(d_ptr->testSetWidget);
    ui->splitter_1->setStretchFactor(0, 1);
    ui->splitter_2->setStretchFactor(0, 1);
    connect(d_ptr->model, &IModel::actionFinished, this, &HAdjustEditWidget::handleAction);
    connect(d_ptr->testSetWidget, &ITestSetWidget::testStateChanged, this, &HAdjustEditWidget::handleStateChanged);
    connect(d_ptr->testSetWidget, &ITestSetWidget::resultChanged, this, &HAdjustEditWidget::handleResultChanged);
}

void HAdjustEditWidget::initSelected()
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
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_4->setEnabled(!d_ptr->selecteds.isEmpty());
}

HE_END_NAMESPACE

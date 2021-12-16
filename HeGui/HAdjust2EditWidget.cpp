#include "HAdjust2EditWidget_p.h"
#include "ui_HAdjust2EditWidget.h"
#include "IGuiFactory.h"
#include "ITestSetWidget.h"
#include "HSpecEnergyWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IAdjust2.h"
#include "HeData/IAdjustItemCollection.h"
#include "HeData/IAdjustItem.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HeController/IModel.h"
#include <QtCore/QStringListModel>

HE_BEGIN_NAMESPACE

HAdjust2EditWidgetPrivate::HAdjust2EditWidgetPrivate()
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

HAdjust2EditWidget::HAdjust2EditWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAdjust2EditWidgetPrivate),
    ui(new Ui::HAdjust2EditWidget)
{
    ui->setupUi(this);
    init();
}

HAdjust2EditWidget::~HAdjust2EditWidget()
{
    disconnect(d_ptr->model, &IModel::actionFinished, this, &HAdjust2EditWidget::handleAction);
    delete ui;
}

void HAdjust2EditWidget::initialize(QVariantMap /*param*/)
{
}

QString HAdjust2EditWidget::typeName()
{
    return "HAdjust2EditWidget";
}

QWidget *HAdjust2EditWidget::widget()
{
    return this;
}

IAdjust2 *HAdjust2EditWidget::createData()
{
    return d_ptr->factory->createAdjust2("HAdjust2");
}

void HAdjust2EditWidget::setData(IAdjust2 *p)
{
    d_ptr->data = p;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    showData();
}

void HAdjust2EditWidget::clearData()
{
    d_ptr->data = nullptr;
    setListModel(QStringList(), "");
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HAdjust2EditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;
    saveItem();
}

void HAdjust2EditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;
    setListModel(d_ptr->data->keys(), "");
}

void HAdjust2EditWidget::handleAction(HActionType action)
{
    d_ptr->testSetWidget->handleAction(action);
}

void HAdjust2EditWidget::handleStateChanged(bool b)
{
    ui->groupBox_2->setEnabled(!b);
}

void HAdjust2EditWidget::handleResultChanged()
{
    d_ptr->energyWidget->refreshWidget();
    ui->tableWidget->setColumn(1, d_ptr->testData->toString(d_ptr->selecteds));
}

void HAdjust2EditWidget::setCurrentIndex(QModelIndex index)
{
    d_ptr->currentIndex = index;
    saveItem();
    d_ptr->itemCollection = d_ptr->data->value(index.data().toString());
    initSelected();
    showItem();
}

void HAdjust2EditWidget::setListModel(const QStringList &names, const QString &name)
{
    d_ptr->listModel->setStringList(names);
    auto row = names.indexOf(name);
    auto index = d_ptr->listModel->hasIndex(row, 0) ? d_ptr->listModel->index(row) : d_ptr->listModel->index(0);
    ui->listView->setCurrentIndex(index);
    ui->groupBox_2->setEnabled(index.isValid());
    ui->pushButton_6->setEnabled(index.isValid());
}

void HAdjust2EditWidget::showItem()
{
    if (d_ptr->itemCollection == nullptr)
        return;

    int r = 0;
    ui->checkBox->setChecked(d_ptr->itemCollection->data("[使用]").toBool());
    ui->doubleSpinBox->setValue(d_ptr->itemCollection->data("[相关色温]").toDouble());
    for (const auto &key : d_ptr->itemCollection->keys())
    {
        auto item = new QTableWidgetItem;
        item->setData(Qt::UserRole, key);
        item->setData(Qt::DisplayRole, HCore::toCaption(key));
        ui->tableWidget->setVerticalHeaderItem(r, item);
        ui->tableWidget->setRow(r, d_ptr->itemCollection->item(key)->toStringList());
        r++;
    }
}

void HAdjust2EditWidget::saveItem()
{
    if (d_ptr->itemCollection == nullptr)
        return;

    d_ptr->itemCollection->setData("[使用]", ui->checkBox->isChecked());
    d_ptr->itemCollection->setData("[相关色温]", ui->doubleSpinBox->value());
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->verticalHeaderItem(i)->data(Qt::UserRole).toString();
        auto value = d_ptr->itemCollection->item(key);
        value->setData("[调整比率]", ui->tableWidget->item(i, 0)->text().toDouble());
        value->setData("[测试值]", ui->tableWidget->item(i, 1)->text().toDouble());
        value->setData("[标准值]", ui->tableWidget->item(i, 2)->text().toDouble());
    }
}

void HAdjust2EditWidget::clearItem()
{
    d_ptr->itemCollection = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HAdjust2EditWidget::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    saveItem();
    auto item = d_ptr->factory->createAdjustItem("HAdjustItem");
    item->setData("[项类型]", type);
    item->restoreDefault();
    d_ptr->itemCollection->insert(type, item);
    initSelected();
    showItem();
}

void HAdjust2EditWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    saveItem();
    d_ptr->itemCollection->remove(type);
    initSelected();
    showItem();
}

void HAdjust2EditWidget::on_pushButton_3_clicked()
{
    d_ptr->itemCollection->restoreDefault();
    showItem();
}

void HAdjust2EditWidget::on_pushButton_4_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto d1 = ui->tableWidget->item(i, 1)->text().toDouble();
        auto d2 = ui->tableWidget->item(i, 2)->text().toDouble();
        auto r = qFuzzyIsNull(d1) ? 100 : 100 * d2 / d1;
        ui->tableWidget->item(i, 0)->setText(HCore::toString("[调整比率]", r));
    }
}

void HAdjust2EditWidget::on_pushButton_5_clicked()
{
    QString name;
    if (!HPluginHelper::getInputText(this, tr("请输入名称："), name))
        return;

    auto item = d_ptr->factory->createAdjustItemCollection("HAdjustItemCollection");
    if (item == nullptr)
        return;
    d_ptr->data->insert(name, item);
    setListModel(d_ptr->data->keys(), name);
}

void HAdjust2EditWidget::on_pushButton_6_clicked()
{
    if (!d_ptr->currentIndex.isValid())
        return;
    auto name = d_ptr->currentIndex.data().toString();
    clearItem();
    if (d_ptr->data->remove(name) > 0)
        setListModel(d_ptr->data->keys(), name);
}

void HAdjust2EditWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType("[调整比率]");
    d_ptr->listModel = new QStringListModel(this);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("调整比率") << tr("测试值") << tr("标准值"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setItemDelegateForColumn(0, delegate);
    ui->groupBox_3->layout()->addWidget(d_ptr->testSetWidget);
    ui->groupBox_4->layout()->addWidget(d_ptr->energyWidget);
    ui->splitter_1->setStretchFactor(1, 1);
    ui->splitter_1->setStretchFactor(2, 1);
    ui->splitter_2->setStretchFactor(0, 1);
    ui->listView->setStyleSheet("QListView::item { height:25px }");
    ui->listView->setModel(d_ptr->listModel);
    HPluginHelper::initWidget("[色温]", ui->doubleSpinBox);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &HAdjust2EditWidget::setCurrentIndex);
    connect(d_ptr->model, &IModel::actionFinished, this, &HAdjust2EditWidget::handleAction);
    connect(d_ptr->testSetWidget, &ITestSetWidget::testStateChanged, this, &HAdjust2EditWidget::handleStateChanged);
    connect(d_ptr->testSetWidget, &ITestSetWidget::resultChanged, this, &HAdjust2EditWidget::handleResultChanged);
}

void HAdjust2EditWidget::initSelected()
{
    d_ptr->selecteds = d_ptr->itemCollection->keys();
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

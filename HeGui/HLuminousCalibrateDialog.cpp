#include "HLuminousCalibrateDialog_p.h"
#include "ui_HLuminousCalibrateDialog.h"
#include "HLuminousCalibrateItemWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/HLuminousCalibrate.h"
#include "HeData/HLuminousCalibrateCollection.h"
#include "HeData/ITestData.h"
#include "HeController/IModel.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HLuminousCalibrateDialogPrivate::HLuminousCalibrateDialogPrivate()
{
    calibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->luminousCalibrateCollection();
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
    model = HAppContext::getContextPointer<IModel>("IModel");
}

HLuminousCalibrateDialog::HLuminousCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HLuminousCalibrateDialogPrivate),
    ui(new Ui::HLuminousCalibrateDialog)
{
    ui->setupUi(this);
    init();
}

HLuminousCalibrateDialog::~HLuminousCalibrateDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HLuminousCalibrateDialog::on_treeWidget_itemSelectionChanged()
{
    auto value = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
    if ((d_ptr->module << 16) + d_ptr->index == value)
        return;

    auto module = (value >> 16) & 0xFF;
    auto index = value & 0xFF;

    setTest(false);
    if (d_ptr->module != module)
    {
        d_ptr->module = module;
        d_ptr->testData->setData("[光模块]", module);
        d_ptr->model->addAction(ACT_SET_LUMINOUS_MODULE);
    }

    d_ptr->index = index;
    ui->stackedWidget->setCurrentIndex(index);
    d_ptr->currentWidget = qobject_cast<HLuminousCalibrateItemWidget *>(ui->stackedWidget->currentWidget());
    d_ptr->testData->setData("[光测试类型]", d_ptr->currentWidget->type());
    d_ptr->model->addAction(ACT_SET_LUMINOUS_TYPE);
}

void HLuminousCalibrateDialog::on_pushButton_1_clicked()
{
    if (d_ptr->currentWidget != nullptr)
        d_ptr->currentWidget->saveData(d_ptr->gears);
}

void HLuminousCalibrateDialog::on_checkBox_clicked(bool b)
{
    setTest(b);
}

void HLuminousCalibrateDialog::on_doubleSpinBox_valueChanged(double value)
{
    d_ptr->testData->setData("[输出电流]", value);
    d_ptr->model->addAction(ACT_SET_OUTPUT_CURRENT);
}

void HLuminousCalibrateDialog::handleAction(HActionType action)
{
    switch (action)
    {
    case ACT_SET_OUTPUT_CURRENT:
        ui->doubleSpinBox->setValue(d_ptr->testData->data("[输出电流]").toDouble());
        break;
    case ACT_SET_LUMINOUS_GEARS:
        d_ptr->gears = d_ptr->testData->data("[光档位]").toInt();
        break;
    case ACT_GET_LUMINOUS_DATA:
        if (!d_ptr->test || d_ptr->currentWidget == nullptr)
            break;
        d_ptr->currentWidget->updateData(d_ptr->testData->data("[光采样值]").toDouble(), d_ptr->gears);
        d_ptr->model->addAction(ACT_GET_LUMINOUS_DATA, 300);
        break;
    }
}

void HLuminousCalibrateDialog::setGears(int value)
{
    if (d_ptr->gears == value)
        return;
    d_ptr->testData->setData("[光档位]", value);
    d_ptr->model->addAction(ACT_SET_LUMINOUS_GEARS);
}

void HLuminousCalibrateDialog::setTest(bool b)
{
    if (d_ptr->test == b)
        return;

    d_ptr->test = b;
    d_ptr->testData->setData("[电源模式]", b ? 1 : 0);
    d_ptr->model->addAction(ACT_SET_SOURCE_MODE);
    if (b)
        d_ptr->model->addAction(ACT_GET_LUMINOUS_DATA, 300);
}

void HLuminousCalibrateDialog::done(int result)
{
    disconnect(d_ptr->model, &IModel::actionFinished, this, &HLuminousCalibrateDialog::handleAction);
    QDialog::done(result);
}

QTreeWidgetItem *HLuminousCalibrateDialog::createItem(const QString &text, int value, QTreeWidgetItem *parent)
{
    auto item = new QTreeWidgetItem(parent);
    item->setText(0, text);
    item->setData(0, Qt::UserRole, value);
    return item;
}

void HLuminousCalibrateDialog::createItem(ILuminousCalibrate *data, int &value, QTreeWidgetItem *parent)
{
    for (auto type : data->keys())
    {
        createItem(HCore::toCaption(type), value, parent);
        addStackedWidget(data->value(type), type);
        value++;
    }
}

void HLuminousCalibrateDialog::addStackedWidget(ILuminousCalibrateItem *data, QString type)
{
    auto w = new HLuminousCalibrateItemWidget(this);
    w->setData(data, type);
    connect(w, &HLuminousCalibrateItemWidget::gearsChanged, this, &HLuminousCalibrateDialog::setGears);
    ui->stackedWidget->addWidget(w);
}

void HLuminousCalibrateDialog::init()
{
    auto value = 0;
    for (const auto &key : d_ptr->calibrate->keys())
    {
        auto parent = ui->treeWidget->invisibleRootItem();
        if (d_ptr->calibrate->size() > 1)
            parent = createItem(HCore::toCaption(key), value, parent);
        createItem(d_ptr->calibrate->value(key), value, parent);
        value += 0x00010000;
    }
    ui->treeWidget->setStyleSheet("QTreeWidget::item { height:25px }");
    ui->treeWidget->expandAll();
    ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0));
    ui->splitter->setStretchFactor(1, 10);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox);
    ui->doubleSpinBox->setValue(d_ptr->testData->data("[输出电流]").toDouble());
    connect(d_ptr->model, &IModel::actionFinished, this, &HLuminousCalibrateDialog::handleAction);
    setWindowTitle(tr("光参数定标"));
}

HE_GUI_END_NAMESPACE

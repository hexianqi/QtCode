#include "HElecCalibrateDialog_p.h"
#include "ui_HElecCalibrateDialog.h"
#include "HElecCalibrateItem1Widget.h"
#include "HElecCalibrateItem2Widget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include "HeData/IElecCalibrateItemCollection.h"
#include "HeData/ITestElec.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HElecCalibrateDialogPrivate::HElecCalibrateDialogPrivate()
{    
    calibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->elecCalibrateCollection();
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
    model = HAppContext::getContextPointer<IModel>("IModel");
}

HElecCalibrateDialog::HElecCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HElecCalibrateDialogPrivate),
    ui(new Ui::HElecCalibrateDialog)
{
    ui->setupUi(this);
    init();
}

HElecCalibrateDialog::~HElecCalibrateDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HElecCalibrateDialog::on_treeWidget_itemSelectionChanged()
{
    auto value = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
    if ((d_ptr->module << 16) + d_ptr->index == value)
        return;

    auto module = (value >> 16) & 0xFF;
    auto index = value & 0xFF;

    d_ptr->loop = false;
    if (d_ptr->module != module)
    {
        d_ptr->module = module;
        d_ptr->testElec->setModule(module);
        d_ptr->model->addAction(ACT_SET_ELEC_MODULE);
    }
    if (d_ptr->index != index)
    {
        d_ptr->index = index;
        if (d_ptr->currentWidget != nullptr)
            d_ptr->currentWidget->setLoop(false);
        ui->stackedWidget->setCurrentIndex(index);
        d_ptr->currentWidget = qobject_cast<HElecCalibrateItemWidget *>(ui->stackedWidget->currentWidget());
        d_ptr->testElec->setGears(d_ptr->currentWidget->type(), d_ptr->currentWidget->gears());
        d_ptr->model->addAction(ACT_SET_GEARS_OUTPUT_VOLTAGE + d_ptr->currentWidget->type());
    }
}

void HElecCalibrateDialog::on_pushButton_1_clicked()
{
    if (d_ptr->currentWidget != nullptr)
        d_ptr->currentWidget->saveData();
}

void HElecCalibrateDialog::handleAction(HActionType action)
{
    if (!d_ptr->loop || d_ptr->currentWidget == nullptr)
        return;

    switch (action)
    {
    case ACT_GET_MEASURED_VOLTAGE:
        d_ptr->currentWidget->updateData(d_ptr->testElec->data("[实测电压_F]").toDouble());
        d_ptr->model->addAction(action);
        break;
    case ACT_GET_MEASURED_CURRENT:
        d_ptr->currentWidget->updateData(d_ptr->testElec->data("[实测电流_F]").toDouble());
        d_ptr->model->addAction(action);
        break;
    case ACT_GET_REVERSE_CURRENT:
        d_ptr->currentWidget->updateData(d_ptr->testElec->data("[反向漏流_F]").toDouble());
        d_ptr->model->addAction(action);
        break;
    }
}

void HElecCalibrateDialog::setElec(HElecType type, double value)
{
    if (type == OutputVoltage)
    {
        d_ptr->testElec->setData("[输出电压_F]", value);        
        d_ptr->model->addAction(ACT_SET_OUTPUT_VOLTAGE);
    }
    if (type == OutputCurrent)
    {
        d_ptr->testElec->setData("[输出电流_F]", value);
        d_ptr->model->addAction(ACT_SET_OUTPUT_CURRENT);
    }
    if (type == ReverseVoltage)
    {
        d_ptr->testElec->setData("[反向电压_F]", value);
        d_ptr->model->addAction(ACT_SET_REVERSE_VOLTAGE);
    }
    if (type == MeasuredVoltage || type == MeasuredCurrent)
    {
        d_ptr->testElec->setParam(OutputCurrent, value);
        d_ptr->model->addAction(ACT_SET_OUTPUT_CURRENT);
    }
    if (type == ReverseCurrent)
    {
        d_ptr->testElec->setParam(ReverseVoltage, value);
        d_ptr->model->addAction(ACT_SET_REVERSE_VOLTAGE);
    }
    d_ptr->testElec->setData("[电源模式]", type == ReverseVoltage || type == ReverseCurrent ? 2 : 1);
    d_ptr->model->addAction(ACT_SET_SOURCE_MODE);
}

void HElecCalibrateDialog::setLoop(HElecType type, bool loop)
{
    d_ptr->loop = loop;
    if (loop)
    {
        if (type == MeasuredVoltage)
            d_ptr->model->addAction(ACT_GET_MEASURED_VOLTAGE);
        if (type == MeasuredCurrent)
            d_ptr->model->addAction(ACT_GET_MEASURED_CURRENT);
        if (type == ReverseCurrent)
            d_ptr->model->addAction(ACT_GET_REVERSE_CURRENT);
    }
}

void HElecCalibrateDialog::done(int result)
{
    disconnect(d_ptr->model, &IModel::actionFinished, this, &HElecCalibrateDialog::handleAction);
    QDialog::done(result);
}

QTreeWidgetItem *HElecCalibrateDialog::createItem(QString text, int value, QTreeWidgetItem *parent)
{
    auto item = new QTreeWidgetItem(parent);
    item->setText(0, text);
    item->setData(0, Qt::UserRole, value);
    return item;
}

void HElecCalibrateDialog::createItem(IElecCalibrate *data, HElecType type, int &value, QTreeWidgetItem *parent)
{
    auto collection = data->itemCollection(type);
    if (collection == nullptr || collection->size() == 0)
        return;

    HElecCalibrateItemWidget *w;
    int i = 0;
    auto p = collection->size() > 1 ? createItem(HCore::toCaption(data->toString(type)), value, parent) : parent;
    for (auto t : collection->keys())
    {
        createItem(HCore::toCaption(t), value, p);
        if (type == OutputVoltage || type == OutputCurrent || type == ReverseVoltage)
            w = new HElecCalibrateItem1Widget(this);
        else
            w = new HElecCalibrateItem2Widget(this);
        w->setData(collection->value(t), type, i);
        ui->stackedWidget->addWidget(w);
        connect(w, &HElecCalibrateItemWidget::elecChanged, this, &HElecCalibrateDialog::setElec);
        connect(w, &HElecCalibrateItemWidget::loopChanged, this, &HElecCalibrateDialog::setLoop);
        value++;
        i++;
    }
}

void HElecCalibrateDialog::init()
{
    auto value = 0;
    auto list = QList<HElecType>() << OutputVoltage << OutputCurrent
                                  << MeasuredVoltage << MeasuredCurrent
                                  << ReverseVoltage << ReverseCurrent;
    for (auto key : d_ptr->calibrate->keys())
    {
        auto item = d_ptr->calibrate->value(key);
        auto parent = ui->treeWidget->invisibleRootItem();
        if (d_ptr->calibrate->size() > 1)
            parent = createItem(HCore::toCaption(key), value, parent);
        for (auto type : list)
            createItem(item, type, value, parent);
        value += 0x00010000;
    }
    ui->treeWidget->expandAll();
    ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0));
    connect(d_ptr->model, &IModel::actionFinished, this, &HElecCalibrateDialog::handleAction);
}

HE_GUI_END_NAMESPACE

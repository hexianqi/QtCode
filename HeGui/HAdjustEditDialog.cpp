#include "HAdjustEditDialog_p.h"
#include "ui_HAdjustEditDialog.h"
#include "ITestSetWidget.h"
#include "HAdjustEditWidget.h"
#include "HSpecEnergyWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustEditDialogPrivate::HAdjustEditDialogPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
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
    d_ptr->editWidget->setData(p);
}

void HAdjustEditDialog::setTestSetWidget(ITestSetWidget *p)
{
    d_ptr->testSetWidget = p;
    ui->groupBox_3->layout()->addWidget(d_ptr->testSetWidget);
    connect(d_ptr->testSetWidget, &ITestSetWidget::testStateChanged, this, [=](bool b){ ui->groupBox_2->setEnabled(!b); });
}

void HAdjustEditDialog::done(int result)
{
    d_ptr->editWidget->saveData();
    QDialog::done(result);
}

void HAdjustEditDialog::handleAction(HActionType action)
{
    if (action == ACT_GET_SPECTRUM)
    {
        d_ptr->energyWidget->refreshWidget();
        d_ptr->editWidget->setTestData(d_ptr->testData->toString(d_ptr->editWidget->selecteds()));
    }
    d_ptr->testSetWidget->handleAction(action);
}

void HAdjustEditDialog::init()
{
    d_ptr->energyWidget = new HSpecEnergyWidget;
    d_ptr->editWidget = new HAdjustEditWidget;
    d_ptr->editWidget->setEnableEdit(false);
    ui->groupBox_1->layout()->addWidget(d_ptr->energyWidget);
    ui->groupBox_2->layout()->addWidget(d_ptr->editWidget);
    ui->splitter_1->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(0,1);
    connect(d_ptr->model, &IModel::actionFinished, this, &HAdjustEditDialog::handleAction);
}

HE_GUI_END_NAMESPACE

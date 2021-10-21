#include "HQualityEditWidget_p.h"
#include "ui_HQualityEditWidget.h"
#include "HQualityItemCollectionWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IQuality.h"
#include <QtWidgets/QColorDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityEditWidgetPrivate::HQualityEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    css = QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);");
}

HQualityEditWidget::HQualityEditWidget(QWidget *parent) :
    QWidget(parent),
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

QWidget *HQualityEditWidget::widget()
{
    return this;
}

IQuality *HQualityEditWidget::createData()
{
    return d_ptr->factory->createQuality("HQuality");
}

void HQualityEditWidget::setData(IQuality *p)
{
    d_ptr->data = p;
    d_ptr->colorInvalidData = d_ptr->data->color(InvalidData);
    d_ptr->colorDamage = d_ptr->data->color(Broken);
    d_ptr->colorNoPass = d_ptr->data->color(NoPass);
    d_ptr->colorPassing = d_ptr->data->color(Passing);
    d_ptr->widget1->setData(p->itemCollection(Damage));
    d_ptr->widget2->setData(p->itemCollection(Criterion));
    showData();
}

void HQualityEditWidget::clearData()
{
    d_ptr->data = nullptr;
    d_ptr->colorInvalidData = Qt::white;
    d_ptr->colorDamage = Qt::white;
    d_ptr->colorNoPass = Qt::white;
    d_ptr->colorPassing = Qt::white;
    d_ptr->widget1->clearData();
    d_ptr->widget2->clearData();
    showPushButton();
}

void HQualityEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;
    d_ptr->data->setColor(InvalidData, d_ptr->colorInvalidData);
    d_ptr->data->setColor(Broken, d_ptr->colorDamage);
    d_ptr->data->setColor(NoPass, d_ptr->colorNoPass);
    d_ptr->data->setColor(Passing, d_ptr->colorPassing);
    d_ptr->widget1->saveData();
    d_ptr->widget2->saveData();
}

void HQualityEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;
    d_ptr->widget1->showData();
    d_ptr->widget2->showData();
    showPushButton();
}

void HQualityEditWidget::showPushButton()
{
    ui->pushButton_01->setStyleSheet(d_ptr->css.arg(d_ptr->colorInvalidData.name()));
    ui->pushButton_02->setStyleSheet(d_ptr->css.arg(d_ptr->colorDamage.name()));
    ui->pushButton_03->setStyleSheet(d_ptr->css.arg(d_ptr->colorNoPass.name()));
    ui->pushButton_04->setStyleSheet(d_ptr->css.arg(d_ptr->colorPassing.name()));
}

void HQualityEditWidget::on_pushButton_01_clicked()
{
    QColorDialog dlg(d_ptr->colorInvalidData, this);
    if (dlg.exec())
    {
        d_ptr->colorInvalidData = dlg.currentColor();
        ui->pushButton_01->setStyleSheet(d_ptr->css.arg(d_ptr->colorInvalidData.name()));
    }
}

void HQualityEditWidget::on_pushButton_02_clicked()
{
    QColorDialog dlg(d_ptr->colorDamage, this);
    if (dlg.exec())
    {
        d_ptr->colorDamage = dlg.currentColor();
        ui->pushButton_02->setStyleSheet(d_ptr->css.arg(d_ptr->colorDamage.name()));
    }
}

void HQualityEditWidget::on_pushButton_03_clicked()
{
    QColorDialog dlg(d_ptr->colorNoPass, this);
    if (dlg.exec())
    {
        d_ptr->colorNoPass = dlg.currentColor();
        ui->pushButton_03->setStyleSheet(d_ptr->css.arg(d_ptr->colorNoPass.name()));
    }
}

void HQualityEditWidget::on_pushButton_04_clicked()
{
    QColorDialog dlg(d_ptr->colorPassing, this);
    if (dlg.exec())
    {
        d_ptr->colorPassing = dlg.currentColor();
        ui->pushButton_04->setStyleSheet(d_ptr->css.arg(d_ptr->colorPassing.name()));
    }
}

void HQualityEditWidget::init()
{
    d_ptr->widget1 = new HQualityItemCollectionWidget(this);
    d_ptr->widget2 = new HQualityItemCollectionWidget(this);
    ui->groupBox_1->layout()->addWidget(d_ptr->widget1);
    ui->groupBox_2->layout()->addWidget(d_ptr->widget2);
    showPushButton();
}

HE_GUI_END_NAMESPACE

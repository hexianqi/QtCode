#include "HElecCalibrateItem2Widget_p.h"
#include "ui_HElecCalibrateItem2Widget.h"
#include "HeCore/HCore.h"
#include "HeData/IElecCalibrateItem.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HElecCalibrateItem2Widget::HElecCalibrateItem2Widget(QWidget *parent) :
    HElecCalibrateItemWidget(*new HElecCalibrateItem2WidgetPrivate, parent),
    ui(new Ui::HElecCalibrateItem2Widget)
{
    ui->setupUi(this);
}

HElecCalibrateItem2Widget::~HElecCalibrateItem2Widget()
{
    qDebug() << __func__;
    delete ui;
}

void HElecCalibrateItem2Widget::setLoop(bool b)
{
    ui->checkBox_1->setChecked(b);
}

void HElecCalibrateItem2Widget::updateData(double value)
{
    Q_D(HElecCalibrateItem2Widget);
    if (ui->doubleSpinBox_1->hasFocus() || ui->doubleSpinBox_4->hasFocus())
        ui->doubleSpinBox_1->setValue(value);
    if (ui->doubleSpinBox_2->hasFocus() || ui->doubleSpinBox_5->hasFocus())
        ui->doubleSpinBox_2->setValue(value);
    ui->doubleSpinBox_3->setValue(value);
    ui->doubleSpinBox_6->setValue(d->data->toReal(value));
}

void HElecCalibrateItem2Widget::showData()
{
    Q_D(HElecCalibrateItem2Widget);
    auto poly = d->data->relation();
    auto type = d->data->data("[项类型]").toString();
    auto typeF = HCore::typeAddition(type, "F");
    auto typeR = HCore::typeAddition(type, "R");
    HPluginHelper::initWidget(typeF, ui->doubleSpinBox_1);
    HPluginHelper::initWidget(typeF, ui->doubleSpinBox_2);
    HPluginHelper::initWidget(typeF, ui->doubleSpinBox_3);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_4);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_5);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_6);
    ui->doubleSpinBox_1->setValue(poly[0].x());
    ui->doubleSpinBox_2->setValue(poly[1].x());
    ui->doubleSpinBox_4->setValue(poly[0].y());
    ui->doubleSpinBox_5->setValue(poly[1].y());
    if (d->type == MeasuredVoltage || d->type == MeasuredCurrent)
        HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_7);
    if (d->type == ReverseCurrent)
        HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_7);
}

void HElecCalibrateItem2Widget::saveData()
{
    Q_D(HElecCalibrateItem2Widget);
    auto p1 = QPointF(ui->doubleSpinBox_1->value(), ui->doubleSpinBox_4->value());
    auto p2 = QPointF(ui->doubleSpinBox_2->value(), ui->doubleSpinBox_5->value());
    d->data->setRelation(QPolygonF() << p1 << p2);
}

void HElecCalibrateItem2Widget::on_pushButton_1_clicked()
{
    Q_D(HElecCalibrateItem2Widget);
    emit elecChanged(d->type, ui->doubleSpinBox_7->value());
}

void HElecCalibrateItem2Widget::on_checkBox_1_clicked(bool checked)
{
    Q_D(HElecCalibrateItem2Widget);
    emit loopChanged(d->type, checked);
}

HE_GUI_END_NAMESPACE

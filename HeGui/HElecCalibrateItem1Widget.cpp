#include "HElecCalibrateItem1Widget_p.h"
#include "ui_HElecCalibrateItem1Widget.h"
#include "HeCore/HCore.h"
#include "HeData/IElecCalibrateItem.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HElecCalibrateItem1Widget::HElecCalibrateItem1Widget(QWidget *parent) :
    HElecCalibrateItemWidget(*new HElecCalibrateItem1WidgetPrivate, parent),
    ui(new Ui::HElecCalibrateItem1Widget)
{
    ui->setupUi(this);
}

HElecCalibrateItem1Widget::~HElecCalibrateItem1Widget()
{
    qDebug() << __func__;
    delete ui;
}

void HElecCalibrateItem1Widget::showData()
{
    Q_D(HElecCalibrateItem1Widget);
    auto poly = d->data->relation();
    auto type = d->data->data("[项类型]").toString();
    auto typeF = HCore::typeAddition(type, "F");
    auto typeR = HCore::typeAddition(type, "R");
    HPluginHelper::initWidget(typeF, ui->doubleSpinBox_1);
    HPluginHelper::initWidget(typeF, ui->doubleSpinBox_2);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_3);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_4);
    HPluginHelper::initWidget(typeR, ui->doubleSpinBox_5);
    ui->doubleSpinBox_1->setValue(poly[0].x());
    ui->doubleSpinBox_2->setValue(poly[1].x());
    ui->doubleSpinBox_3->setValue(poly[0].y());
    ui->doubleSpinBox_4->setValue(poly[1].y());
}

void HElecCalibrateItem1Widget::saveData()
{
    Q_D(HElecCalibrateItem1Widget);
    auto p1 = QPointF(ui->doubleSpinBox_1->value(), ui->doubleSpinBox_3->value());
    auto p2 = QPointF(ui->doubleSpinBox_2->value(), ui->doubleSpinBox_4->value());
    d->data->setRelation(QPolygonF() << p1 << p2);
}

void HElecCalibrateItem1Widget::on_pushButton_1_clicked()
{
    Q_D(HElecCalibrateItem1Widget);
    emit elecChanged(d->type, ui->doubleSpinBox_1->value());
}

void HElecCalibrateItem1Widget::on_pushButton_2_clicked()
{
    Q_D(HElecCalibrateItem1Widget);
    emit elecChanged(d->type, ui->doubleSpinBox_2->value());
}

void HElecCalibrateItem1Widget::on_pushButton_3_clicked()
{
    Q_D(HElecCalibrateItem1Widget);
    emit elecChanged(d->type, d->data->toFiction(ui->doubleSpinBox_5->value()));
}

HE_GUI_END_NAMESPACE

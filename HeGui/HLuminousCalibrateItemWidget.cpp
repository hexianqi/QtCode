#include "HLuminousCalibrateItemWidget_p.h"
#include "ui_HLuminousCalibrateItemWidget.h"
#include "HeCore/HCore.h"
#include "HeData/ILuminousCalibrateItem.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HLuminousCalibrateItemWidget::HLuminousCalibrateItemWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLuminousCalibrateItemWidgetPrivate),
    ui(new Ui::HLuminousCalibrateItemWidget)
{
    ui->setupUi(this);
}

HLuminousCalibrateItemWidget::~HLuminousCalibrateItemWidget()
{
    qDebug() << __func__;
    delete ui;
}

QString HLuminousCalibrateItemWidget::type()
{
    return d_ptr->type;
}

void HLuminousCalibrateItemWidget::setData(ILuminousCalibrateItem *p, QString type)
{
    d_ptr->data = p;
    d_ptr->type = type;
    d_ptr->types << p->data("[项类型]").toString();
    d_ptr->types << HCore::typeAddition(d_ptr->types.first(), "F");
    initWidget();
    showData();
}

void HLuminousCalibrateItemWidget::updateData(double value, int gears)
{
    auto text1 = HCore::toString(d_ptr->types.at(1), value);
    auto text2 = HCore::toString(d_ptr->types.at(0), d_ptr->data->toReal(value, gears));
    ui->lineEdit_1->setText(text1);
    ui->lineEdit_2->setText(text2);
    ui->tableWidget->item(gears, d_ptr->column)->setText(text1);
}

void HLuminousCalibrateItemWidget::showData()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QStringList list;
        auto poly = d_ptr->data->relation(i);
        for (int j = 0; j < poly.size(); j++)
            list << HCore::toString(d_ptr->types.at(1), poly[j].x()) << HCore::toString(d_ptr->types.at(0), poly[j].y());
        ui->tableWidget->setRow(i, list);
    }
    ui->lineEdit_1->setText(HCore::toString(d_ptr->types.at(1), 0.0));
    ui->lineEdit_2->setText(HCore::toString(d_ptr->types.at(0), 0.0));
}

void HLuminousCalibrateItemWidget::saveData(int gears)
{
    if (gears < 0 || gears >= ui->tableWidget->rowCount())
        return;

    double x, y;
    QPolygonF poly;
    for (int i = 0; i < ui->tableWidget->columnCount(); i += 2)
    {
        x = ui->tableWidget->item(gears, i)->text().toDouble();
        y = ui->tableWidget->item(gears, i+1)->text().toDouble();
        poly.append(QPointF(x, y));
    }
    d_ptr->data->setRelation(gears, poly);
}

void HLuminousCalibrateItemWidget::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow != previousRow)
        emit gearsChanged(currentRow);
    if (currentColumn != previousColumn)
        d_ptr->column = int(currentColumn / 2) * 2;
}

void HLuminousCalibrateItemWidget::initWidget()
{
    if (d_ptr->data->totalGears() > 0)
    {
        QStringList headers, types;
        for (int i = 0; i < d_ptr->data->relation(0).size(); i++)
        {
            headers << tr("采样值%1").arg(i+1) << tr("标准值%1").arg(i+1);
            types << d_ptr->types.at(1) << d_ptr->types.at(0);
        }
        auto delegate = new HDoubleSpinBoxDelegate(this);
        delegate->setType(types);
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setItemDelegate(delegate);
        ui->tableWidget->setRowCount(d_ptr->data->totalGears());
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    ui->label_003->setText(HCore::toUnit(d_ptr->types.at(0)));
}

HE_GUI_END_NAMESPACE

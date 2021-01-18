#include "HGradeItemDialog_p.h"
#include "ui_HGradeItemDialog.h"
#include "HeCore/HCore.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeItemDialog::HGradeItemDialog(QWidget *parent) :
    HAbstractGradeItemDialog(*new HGradeItemDialogPrivate, parent),
    ui(new Ui::HGradeItemDialog)
{
    ui->setupUi(this);
    init();
}

HGradeItemDialog::~HGradeItemDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HGradeItemDialog::on_spinBox_02_valueChanged(int value)
{
    Q_D(HGradeItemDialog);
    if (ui->checkBox_01->isChecked())
        return;
    auto previous = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(value);
    for (int i = previous; i < value; i++)
        ui->tableWidget->setRow(i, d->data->level(-1));
}

void HGradeItemDialog::on_checkBox_01_clicked(bool b)
{
    setAverageMode(b);
}

void HGradeItemDialog::on_pushButton_01_clicked()
{
    averageLevels();
    setAverageMode(false);
}

bool HGradeItemDialog::setAverageMode(bool b)
{
    Q_D(HGradeItemDialog);
    if (!HAbstractGradeItemDialog::setAverageMode(b))
        return false;

    if (b)
    {
        if (ui->tableWidget->rowCount() == 0)
            ui->tableWidget->insertRow(0, d->data->level(-1));
        else
            ui->tableWidget->setRowCount(1);
    }
    ui->checkBox_01->setChecked(b);
    ui->pushButton_01->setEnabled(b);
    return true;
}

void HGradeItemDialog::averageLevels()
{
    Q_D(HGradeItemDialog);
    auto count = ui->spinBox_02->value();
    if (count == 0)
        return;

    auto min =  ui->tableWidget->item(0, 0)->text().toDouble();
    auto max =  ui->tableWidget->item(0, 1)->text().toDouble();
    auto gap = (max - min) / count;
    ui->tableWidget->setRowCount(count);
    for (int i = 0; i < count; i++)
    {
        auto x1 = min + i * gap;
        auto x2 = min + (i + 1) * gap;
        ui->tableWidget->setRow(i, QStringList() << HCore::toString(d->type, x1) << HCore::toString(d->type, x2));
    }
}

void HGradeItemDialog::showData()
{
    Q_D(HGradeItemDialog);
    auto count = d->data->count();
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d->data->types());
    ui->spinBox_01->setValue(d->data->data("[优先级]").toInt());
    ui->spinBox_02->setValue(count);
    ui->tableWidget->setHorizontalHeaderLabels(d->data->headers());
    ui->tableWidget->setItemDelegate(delegate);
    ui->tableWidget->setRowCount(count);
    for (int i = 0; i < count; i++)
        ui->tableWidget->setRow(i, d->data->level(i));
}

void HGradeItemDialog::saveData()
{
    Q_D(HGradeItemDialog);
    QList<QPointF> list;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto x = ui->tableWidget->item(i, 0)->text().toDouble();
        auto y = ui->tableWidget->item(i, 1)->text().toDouble();
        list << QPointF(x, y);
    }
    d->data->setLevels(QVariant::fromValue(list));
    d->data->setData("[优先级]", ui->spinBox_01->value());
}

void HGradeItemDialog::init()
{
    HPluginHelper::initWidget("[优先级]", ui->spinBox_01);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_02);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

HE_GUI_END_NAMESPACE

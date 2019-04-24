#include "HGradeItem2DDialog_p.h"
#include "ui_HGradeItem2DDialog.h"
#include "HGradeIsothermDialog.h"
#include "HeCore/HCore.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HCIE1931Widget.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeItem2DDialog::HGradeItem2DDialog(QWidget *parent) :
    HAbstractGradeItemDialog(*new HGradeItem2DDialogPrivate, parent),
    ui(new Ui::HGradeItem2DDialog)
{
    ui->setupUi(this);
    init();
}

HGradeItem2DDialog::~HGradeItem2DDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HGradeItem2DDialog::on_spinBox_02_valueChanged(int value)
{
    Q_D(HGradeItem2DDialog);
    if (!ui->checkBox_01->isChecked())
    {
        ui->tableWidget->setRowCount(value);
        d->cieWidget->setGrade(getLevels());
    }
}

void HGradeItem2DDialog::on_checkBox_01_clicked(bool b)
{
    setAverageMode(b);
}

void HGradeItem2DDialog::on_pushButton_01_clicked()
{
    averageLevels();
    setAverageMode(false);
}

void HGradeItem2DDialog::on_pushButton_13_clicked()
{
    HGradeIsothermDialog dlg(this);
    if (dlg.exec())
        showLevels(dlg.levels());
}

void HGradeItem2DDialog::setGradeFocus()
{
    Q_D(HGradeItem2DDialog);
    QPolygonF poly;
    auto row = ui->tableWidget->currentRow();
    if (row < 0)
        return;

    for (int i = 0; i < ui->tableWidget->columnCount(); i += 2)
    {
        auto x =  ui->tableWidget->item(row, i)->text().toDouble();
        auto y =  ui->tableWidget->item(row, i + 1)->text().toDouble();
        poly << QPointF(x, y);
    }
    d->cieWidget->setGradeFocus(poly);
}

void HGradeItem2DDialog::replacePoint(QPointF point)
{
    Q_D(HGradeItem2DDialog);
    auto ranges = ui->tableWidget->selectedRanges();
    if (ranges.isEmpty())
        return;

    auto range = ranges.first();
    auto row = range.topRow();
    auto column = range.leftColumn() / 2 * 2;
    ui->tableWidget->item(row, column)->setText(toString(d->type, point.x()));
    ui->tableWidget->item(row, column + 1)->setText(toString(d->type, point.y()));
    setGradeFocus();
}

bool HGradeItem2DDialog::setAverageMode(bool b)
{
    if (!HAbstractGradeItemDialog::setAverageMode(b))
        return false;

    if (b)
        ui->tableWidget->setRowCount(1);
    ui->checkBox_01->setChecked(!b);
    ui->spinBox_03->setEnabled(b);
    ui->spinBox_04->setEnabled(b);
    ui->pushButton_01->setEnabled(b);
    return true;
}

void HGradeItem2DDialog::showData()
{
    Q_D(HGradeItem2DDialog);
    auto levels = d->data->levels().value<QList<QPolygonF>>();
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d->data->types());
    ui->spinBox_01->setValue(d->data->data("[优先级]").toInt());
    ui->tableWidget->setHorizontalHeaderLabels(d->data->headers());
    ui->tableWidget->setItemDelegate(delegate);
    connect(delegate, &HDoubleSpinBoxDelegate::editingFinished, this, &HGradeItem2DDialog::setGradeFocus);
    showLevels(levels);
}

void HGradeItem2DDialog::saveData()
{
    Q_D(HGradeItem2DDialog);
    d->data->setLevels(QVariant::fromValue(getLevels()));
    d->data->setData("[优先级]", ui->spinBox_01->value());
}

void HGradeItem2DDialog::averageLevels()
{
    int i,j,r,c,t;
    double x,y;
    QPolygonF p1,p2,p3;
    QList<QPolygonF> l;
    r = ui->spinBox_03->value();
    c = ui->spinBox_04->value();
    t = r *c;
    if (t == 0 || t > 99999)
        return;

    p1 = getLevels().first();
    for (i = 0; i < r; i++)
    {
        p2.clear();
        x = p1[0].x() + i * (p1[3].x() - p1[0].x()) / r;
        y = p1[0].y() + i * (p1[3].y() - p1[0].y()) / r;
        p2 << QPointF(x, y);
        x = p1[1].x() + i * (p1[2].x() - p1[1].x()) / r;
        y = p1[1].y() + i * (p1[2].y() - p1[1].y()) / r;
        p2 << QPointF(x, y);
        x = p1[1].x() + (i + 1) * (p1[2].x() - p1[1].x()) / r;
        y = p1[1].y() + (i + 1) * (p1[2].y() - p1[1].y()) / r;
        p2 << QPointF(x, y);
        x = p1[0].x() + (i + 1) * (p1[3].x() - p1[0].x()) / r;
        y = p1[0].y() + (i + 1) * (p1[3].y() - p1[0].y()) / r;
        p2 << QPointF(x, y);
        for (j = 0; j < c; j++)
        {
            p3.clear();
            x = p2[0].x() + j * (p2[1].x() - p2[0].x()) / c;
            y = p2[0].y() + j * (p2[1].y() - p2[0].y()) / c;
            p3 << QPointF(x, y);
            x = p2[0].x() + (j + 1) * (p2[1].x() - p2[0].x()) / c;
            y = p2[0].y() + (j + 1) * (p2[1].y() - p2[0].y()) / c;
            p3 << QPointF(x, y);
            x = p2[3].x() + (j + 1) * (p2[2].x() - p2[3].x()) / c;
            y = p2[3].y() + (j + 1) * (p2[2].y() - p2[3].y()) / c;
            p3 << QPointF(x, y);
            x = p2[3].x() + j * (p2[2].x() - p2[3].x()) / c;
            y = p2[3].y() + j * (p2[2].y() - p2[3].y()) / c;
            p3 << QPointF(x, y);
            l << p3;
        }
    }
    showLevels(l);
}

QList<QPolygonF> HGradeItem2DDialog::getLevels()
{
    QList<QPolygonF> l;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QPolygonF p;
        for (int j = 0; j <ui->tableWidget->columnCount(); j += 2)
        {
            auto x =  ui->tableWidget->item(i, j)->text().toDouble();
            auto y =  ui->tableWidget->item(i, j + 1)->text().toDouble();
            p << QPointF(x, y);
        }
        l << p;
    }
    return l;
}

void HGradeItem2DDialog::showLevels(QList<QPolygonF> value)
{
    Q_D(HGradeItem2DDialog);
    auto count = value.size();
    ui->tableWidget->setRowCount(count);
    for (int i = 0; i < count; i++)
    {
        QStringList text;
        for (int j = 0; j < value[i].size(); j++)
            text << toString(d->type, value[i][j].x()) << toString(d->type, value[i][j].y());
        ui->tableWidget->setRow(i, text);
    }
    d->cieWidget->setGrade(value);
    ui->spinBox_02->setValue(count);
}

void HGradeItem2DDialog::init()
{
    Q_D(HGradeItem2DDialog);
    HPluginHelper::initWidget("[优先级]", ui->spinBox_01);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_02);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_03);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_04);
    d->cieWidget = new HCIE1931Widget;
    d->cieWidget->setMinimumSize(QSize(420, 420));
    ui->splitter->addWidget(d->cieWidget);
    connect(d->cieWidget, &HCIE1931Widget::mouseDoubleClicked, this, &HGradeItem2DDialog::replacePoint);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &HGradeItem2DDialog::setGradeFocus);
}

HE_GUI_END_NAMESPACE


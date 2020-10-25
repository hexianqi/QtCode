#include "HSequentialGradeWidget_p.h"
#include "ui_HSequentialGradeWidget.h"
#include "HeCore/HCore.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "QXlsx/xlsxdocument.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSequentialGradeWidget::HSequentialGradeWidget(QWidget *parent) :
    HAbstractGradeWidget(*new HSequentialGradeWidgetPrivate, parent),
    ui(new Ui::HSequentialGradeWidget)
{
    ui->setupUi(this);
    init();
}

HSequentialGradeWidget::~HSequentialGradeWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HSequentialGradeWidget::clearData()
{
    HAbstractGradeWidget::clearData();
    ui->tableWidget_1->clear();
    ui->spinBox_1->setValue(0);
}

bool HSequentialGradeWidget::saveData()
{
    Q_D(HSequentialGradeWidget);
    if (!HAbstractGradeWidget::saveData())
        return false;

    int i, j, size, n = 1;
    bool b1, b2;
    double x, y;
    QStringList signature;
    for (i = 0; i < ui->tableWidget_1->rowCount(); i++)
        signature << ui->tableWidget_1->item(i, 0)->text();
    d->data->setData("[特征码]", signature);
    for (auto item : d->items)
    {
        size = item->headers().size();
        if (size == 2)
        {
            QList<QPointF> list;
            for (i = 0; i < ui->tableWidget_1->rowCount(); i++)
            {
                x = ui->tableWidget_1->item(i, n)->text().toDouble(&b1);
                y = ui->tableWidget_1->item(i, n + 1)->text().toDouble(&b2);
                if (!b1 || !b2)
                    break;
                list << QPointF(x, y);
            }
            item->setLevels(QVariant::fromValue(list));
        }
        else
        {
            QList<QPolygonF> list;
            for (i = 0; i < ui->tableWidget_1->rowCount(); i++)
            {
                QPolygonF poly;
                for (j = 0; j < size; j += 2)
                {
                    x = ui->tableWidget_1->item(i, n + j)->text().toDouble(&b1);
                    y = ui->tableWidget_1->item(i, n + j + 1)->text().toDouble(&b2);
                    if (!b1 || !b2)
                        break;
                    poly << QPointF(x, y);
                }
                if (j < size)
                    break;
                list << poly;
            }
            item->setLevels(QVariant::fromValue(list));
        }
        n += size;
    }
    return true;
}

bool HSequentialGradeWidget::showData()
{
    Q_D(HSequentialGradeWidget);
    if (!HAbstractGradeWidget::showData())
        return false;

    auto signature = d->data->data("[特征码]").toStringList();
    auto total = signature.size();
    QStringList headers, types;
    headers << HCore::toCaption("[特征码]");
    for (auto item : d->items)
    {
        total = qMax(total, item->count());
        headers << item->headers();
        types << item->types();
    }

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(types);
    delegate->setOrigin(QPoint(1, 0));
    connect(delegate, &HDoubleSpinBoxDelegate::editingFinished, this, [=]{ d_ptr->modified = true; });
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->tableWidget_1->setHorizontalHeaderLabels(headers);
    ui->tableWidget_1->setItemDelegate(delegate);
    ui->spinBox_1->setValue(total);

    for (int i = 0; i < ui->tableWidget_1->rowCount(); i++)
    {
        QStringList list;
        list.append(i < signature.size() ? signature.at(i) : "");
        for (auto item : d_ptr->items)
            list << item->level(i);
        ui->tableWidget_1->setRow(i, list);
    }
    return true;
}

void HSequentialGradeWidget::on_pushButton_1_clicked()
{
    insertGradeItem();
}

void HSequentialGradeWidget::on_pushButton_2_clicked()
{
    removeGradeItem();
}

void HSequentialGradeWidget::on_pushButton_3_clicked()
{
    editGradeItem();
}

void HSequentialGradeWidget::on_pushButton_4_clicked()
{
    saveData();
}

void HSequentialGradeWidget::on_spinBox_1_valueChanged(int value)
{
    ui->tableWidget_1->setRowCount(value);
}

void HSequentialGradeWidget::exportExcel()
{
    auto fileName = QFileDialog::getSaveFileName(this, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return;

    auto model = ui->tableWidget_1->model();
    int i, j;
    QXlsx::Document doc(this);
    doc.write(5, 1, tr("BIN"));
    for (j = 0; j < model->columnCount(); j++)
        doc.write(5, j + 2, model->headerData(j, Qt::Horizontal));
    for (i = 0; i < model->rowCount(); i++)
        doc.write(i + 6, 1, model->headerData(i, Qt::Vertical));

    for (i = 0; i < model->rowCount(); i++)
    {
        for (j = 0; j < model->columnCount(); j++)
        {
            auto index = model->index(i, j);
            if (!index.isValid())
                continue;
            doc.write(i + 6, j + 2, index.data().toString());
        }
    }
    doc.saveAs(fileName);
}

void HSequentialGradeWidget::importExcel()
{
    auto fileName = QFileDialog::getOpenFileName(this, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return;

    auto model = ui->tableWidget_1->model();
    QXlsx::Document doc(fileName, this);
    if (!doc.isLoadPackage())
        return;
    auto range = doc.dimension();
    auto rowCount = range.rowCount();
    auto colCount = range.columnCount();
    if (rowCount < 6 || colCount < 2)
        return;

    for (int i = 6; i <= rowCount; i++)
    {
        for (int j = 2; j <= colCount; j++)
        {
            auto cell = doc.cellAt(i, j);
            auto index = model->index(i - 6, j - 2);
            if (!index.isValid() || cell == nullptr)
                continue;
            model->setData(index, cell->value());
        }
    }
}

void HSequentialGradeWidget::init()
{
    Q_D(HSequentialGradeWidget);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_1);
    d->actionExport = new QAction(tr("导出表(&E)"), this);
    d->actionImport = new QAction(tr("导入表(&I)"), this);
    ui->tableWidget_1->setExportImport(false);
    ui->tableWidget_1->addAction(d->actionExport);
    ui->tableWidget_1->addAction(d->actionImport);
    connect(d->actionExport, &QAction::triggered, this, &HSequentialGradeWidget::exportExcel);
    connect(d->actionImport, &QAction::triggered, this, &HSequentialGradeWidget::importExcel);
    connect(ui->tableWidget_1, &HTableWidget::contentChanged, this, [=] { d_ptr->modified = true; });
}

HE_GUI_END_NAMESPACE

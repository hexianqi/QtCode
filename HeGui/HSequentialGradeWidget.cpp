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

HE_BEGIN_NAMESPACE

HSequentialGradeWidget::HSequentialGradeWidget(QWidget *parent) :
    HAbstractGradeWidget(*new HSequentialGradeWidgetPrivate, parent),
    ui(new Ui::HSequentialGradeWidget)
{
    ui->setupUi(this);
    init();
}

HSequentialGradeWidget::~HSequentialGradeWidget()
{
    delete ui;
}

void HSequentialGradeWidget::clearData()
{
    HAbstractGradeWidget::clearData();
    ui->tableWidget_1->clear();
    ui->tableWidget_1->setRowCount(0);
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
    connect(delegate, &HDoubleSpinBoxDelegate::closeEditor, this, &HSequentialGradeWidget::setModified);
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->tableWidget_1->setHorizontalHeaderLabels(headers);
    ui->tableWidget_1->setItemDelegate(delegate);
    ui->tableWidget_1->setRowCount(total);
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

void HSequentialGradeWidget::on_pushButton_5_clicked()
{
    ui->tableWidget_1->setRowCount(ui->spinBox_1->value());
}

void HSequentialGradeWidget::exportExcel()
{
    auto fileName = QFileDialog::getSaveFileName(this, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return;

    auto model = ui->tableWidget_1->model();
    int i, j;
    QXlsx::Document doc(this);
    doc.write(5, 1, "BIN");
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
    doc.write(i, 1, "200");
    doc.write(i + 1, 1, "400");
    doc.saveAs(fileName);
}

void HSequentialGradeWidget::importExcel()
{
    auto fileName = QFileDialog::getOpenFileName(this, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return;

    int i, j;
    QXlsx::Document doc(fileName, this);
    if (!doc.isLoadPackage())
        return;
    auto range = doc.dimension();
    auto t = range.firstRow();
    auto b = range.lastRow();
    auto l = range.firstColumn();
    auto r = range.lastColumn();
    for (i = range.firstRow(); i <= range.lastRow(); i++)
    {
        for (j = range.firstColumn(); j <= range.lastColumn(); j++)
        {
            auto cell = doc.cellAt(i, j);
            if (cell == nullptr)
                continue;
            if (cell->value().toString().trimmed().compare("BIN", Qt::CaseInsensitive) == 0)
                l = j + 1;
        }
    }

    int pre = 0;
    int cur = 0;
    for (i = t; i <= range.lastRow(); i++)
    {
        auto cell = doc.cellAt(i, l - 1);
        if (cell == nullptr)
            continue;
        cur = cell->value().toInt();
        if (pre == 1 && cur == 2)
            t = i - 1;
        if (pre == 200 && cur == 400)
        {
            b = i - 2;
            break;
        }
        pre = cur;
    }

    ui->spinBox_1->setValue(b - t + 1);
    ui->tableWidget_1->setRowCount(b - t + 1);
    for (i = t; i <= b; i++)
    {
        for (j = l; j <= r; j++)
        {
            auto cell = doc.cellAt(i, j);
            if (cell == nullptr)
                continue;
            ui->tableWidget_1->item(i - t, j - l)->setData(Qt::DisplayRole, cell->value());
        }
    }
    setModified();
}

void HSequentialGradeWidget::setModified()
{
    Q_D(HSequentialGradeWidget);
    d->modified = true;
}

void HSequentialGradeWidget::init()
{
    Q_D(HSequentialGradeWidget);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_1);
    d->actionExport = new QAction(tr("导出表(&E)"), this);
    d->actionImport = new QAction(tr("导入表(&I)"), this);
    ui->tableWidget_1->setActionContain(HTableWidget::ActionCopy | HTableWidget::ActionPaste);
    ui->tableWidget_1->addAction(d->actionExport);
    ui->tableWidget_1->addAction(d->actionImport);
    connect(d->actionExport, &QAction::triggered, this, &HSequentialGradeWidget::exportExcel);
    connect(d->actionImport, &QAction::triggered, this, &HSequentialGradeWidget::importExcel);
    connect(ui->tableWidget_1, &HTableWidget::contentChanged, this, &HSequentialGradeWidget::setModified);
}

HE_END_NAMESPACE

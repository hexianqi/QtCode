#include "HParallelGradeWidget_p.h"
#include "ui_HParallelGradeWidget.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HParallelGradeWidget::HParallelGradeWidget(QWidget *parent) :
    HAbstractGradeWidget(*new HParallelGradeWidgetPrivate, parent),
    ui(new Ui::HParallelGradeWidget)
{
    ui->setupUi(this);
    init();
}

HParallelGradeWidget::~HParallelGradeWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HParallelGradeWidget::clearData()
{
    HAbstractGradeWidget::clearData();
    ui->tableWidget_1->clear();
    ui->tableWidget_2->clear();
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(0));
}

bool HParallelGradeWidget::saveData()
{
    Q_D(HParallelGradeWidget);
    if (!HAbstractGradeWidget::saveData())
        return false;

    int i, j, size, n = 0;
    bool b1, b2;
    double x, y;
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

bool HParallelGradeWidget::showData()
{
    Q_D(HParallelGradeWidget);
    if (!HAbstractGradeWidget::showData())
        return false;

    int max = 0, total = 1;
    QStringList headers, types;
    for (auto item : d->items)
    {
        max = qMax(max, item->count());
        total *= item->count();
        headers << item->headers();
        types << item->types();
    }
    if (max == 0)
        total = 0;

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(types);
    connect(delegate, &HDoubleSpinBoxDelegate::editingFinished, this, [=]{ d_ptr->modified = true; });
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(total));
    ui->tableWidget_1->setHorizontalHeaderLabels(headers);
    ui->tableWidget_1->setItemDelegate(delegate);
    ui->tableWidget_1->setRowCount(max);
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);
    ui->tableWidget_2->setItemDelegate(delegate);
    ui->tableWidget_2->setRowCount(total);
    showConfig();
    showPreview();
    return true;
}

void HParallelGradeWidget::showConfig()
{
    for (int i = 0; i < ui->tableWidget_1->rowCount(); i++)
    {
        QStringList list;
        for (auto item : d_ptr->items)
            list << item->level(i);
        ui->tableWidget_1->setRow(i, list);
    }
}

void HParallelGradeWidget::showPreview()
{
    int i, j, k, m, n;
    for (i = 0; i < ui->tableWidget_2->rowCount(); i ++)
    {
        for (j = 0; j < ui->tableWidget_2->columnCount(); j++)
            ui->tableWidget_2->setSpan(i, j, 1, 1);
    }

    m = 1;
    n = ui->tableWidget_2->columnCount();
    for (k = d_ptr->items.size() - 1; k >= 0; k--)
    {
        auto item = d_ptr->items.at(k);
        auto c = item->count();
        auto h = item->headers().size();
        n -= h;
        for (i = 0; i < ui->tableWidget_2->rowCount(); i += m)
        {
            if (m > 1)
            {
                for (j = 0; j < h; j++)
                    ui->tableWidget_2->setSpan(i, j + n, m, 1);
            }
            ui->tableWidget_2->setRow(i, n, item->level((i / m) % c));
        }
        m *= c;
    }
}

void HParallelGradeWidget::on_pushButton_1_clicked()
{
    insertGradeItem();
}

void HParallelGradeWidget::on_pushButton_2_clicked()
{
    removeGradeItem();
}

void HParallelGradeWidget::on_pushButton_3_clicked()
{
    editGradeItem();
}

void HParallelGradeWidget::on_pushButton_4_clicked()
{
    saveData();
    showPreview();
}

void HParallelGradeWidget::init()
{
    connect(ui->tableWidget_1, &HTableWidget::contentChanged, this, [=] { d_ptr->modified = true; });
}

HE_GUI_END_NAMESPACE

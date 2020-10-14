#include "HGradeEditWidget_p.h"
#include "ui_HGradeEditWidget.h"
#include "HGradeItemDialog.h"
#include "HGradeItem2DDialog.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IGrade.h"
#include "HeData/IGradeItem.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeEditWidgetPrivate::HGradeEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("GradeOptionals");
}

HGradeEditWidget::HGradeEditWidget(QWidget *parent) :
    IDataEditWidget(parent),
    d_ptr(new HGradeEditWidgetPrivate),
    ui(new Ui::HGradeEditWidget)
{
    ui->setupUi(this);
}

HGradeEditWidget::~HGradeEditWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HGradeEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HGradeEditWidget::typeName()
{
    return "HGradeEditWidget";
}

IGrade *HGradeEditWidget::createData()
{
    return d_ptr->factory->createGrade("HParallelGrade");
}

void HGradeEditWidget::setData(IGrade *p)
{
    d_ptr->data = p;
    showData();
}

void HGradeEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget_1->clear();
    ui->tableWidget_2->clear();
    ui->label_001->setText(tr("<font color=#FF0000>总分级数目： %1</font>").arg(0));
}

void HGradeEditWidget::saveData()
{
    if (!d_ptr->modified)
        return;

    int i, j, size, n = 0;
    bool b1, b2;
    double x, y;
    for (auto item : d_ptr->items)
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
    d_ptr->modified = false;
}

void HGradeEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;

    int max = 0, total = 1;
    d_ptr->modified = false;
    d_ptr->selecteds = d_ptr->data != nullptr ? d_ptr->data->keys() : QStringList();
    d_ptr->unselecteds = HCoreHelper::unselected(d_ptr->optionals, d_ptr->selecteds);

    QMap<int, IGradeItem *> map;
    for (auto v : d_ptr->data->values())
    {
        auto priority = v->data("[优先级]").toInt() * 100;
        while (map.contains(priority))
            priority++;
        map.insert(priority, v);
        max = qMax(max, v->count());
        total *= v->count();
    }
    if (max == 0)
        total = 0;
    d_ptr->items = map.values();

    QStringList headers, types;
    for (auto item : d_ptr->items)
    {
        headers << item->headers();
        types << item->types();
    }
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
}

bool HGradeEditWidget::editData(const QString &type)
{
    HAbstractGradeItemDialog *dlg;
    auto item = d_ptr->data->value(type);
    if (item->typeName() == "HGradeItem2D")
        dlg = new HGradeItem2DDialog(this);
    else
        dlg = new HGradeItemDialog(this);
    dlg->setData(item);
    return dlg->exec() == QDialog::Accepted;
}

void HGradeEditWidget::showConfig()
{
    for (int i = 0; i < ui->tableWidget_1->rowCount(); i++)
    {
        QStringList list;
        for (auto item : d_ptr->items)
            list << item->level(i);
        ui->tableWidget_1->setRow(i, list);
    }
}

void HGradeEditWidget::showPreview()
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

void HGradeEditWidget::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    auto className = type == "[色坐标]" ? "HGradeItem2D" : "HGradeItem";
    auto item = d_ptr->factory->createGradeItem(className);
    item->setData("[项类型]", type);
    d_ptr->data->insert(type, item);
    editData(type);
    showData();
}

void HGradeEditWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    d_ptr->data->remove(type);
    showData();
}

void HGradeEditWidget::on_pushButton_3_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    if (!editData(type))
        return;
    showData();
}

void HGradeEditWidget::on_pushButton_4_clicked()
{
    saveData();
    showPreview();
}

HE_GUI_END_NAMESPACE

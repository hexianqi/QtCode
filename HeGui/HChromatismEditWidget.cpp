#include "HChromatismEditWidget_p.h"
#include "ui_HChromatismEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeAlgorithm/HSpecHelper.h"
#include "HeData/IDataFactory.h"
#include "HeData/IChromatism.h"
#include "HeData/IChromatismItem.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtCore/QUuid>
#include <QtCore/QDebug>

HE_ALGORITHM_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

HChromatismEditWidgetPrivate::HChromatismEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HChromatismEditWidget::HChromatismEditWidget(QWidget *parent) :
    IDataEditWidget(parent),
    d_ptr(new HChromatismEditWidgetPrivate),
    ui(new Ui::HChromatismEditWidget)
{
    ui->setupUi(this);
    init();
}

HChromatismEditWidget::~HChromatismEditWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HChromatismEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HChromatismEditWidget::typeName()
{
    return "HChromatismEditWidget";
}

IChromatism *HChromatismEditWidget::createData()
{
    return d_ptr->factory->createChromatism("HChromatism");
}

void HChromatismEditWidget::setData(IChromatism *p)
{
    d_ptr->data = p;
    showData();
}

void HChromatismEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HChromatismEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
        auto item = d_ptr->data->item(key);
        item->setData("[使用]", ui->tableWidget->item(i, 0)->checkState() == Qt::Checked);
        item->setData("[标题]", ui->tableWidget->item(i, 0)->text());
        item->setData("[相关色温]", ui->tableWidget->item(i, 1)->text().toDouble());
        item->setData("[标准Sdcm]", ui->tableWidget->item(i, 2)->text().toDouble());

        item->setData("[中心点]", QPointF(ui->tableWidget->item(i, 3)->text().toDouble(), ui->tableWidget->item(i, 4)->text().toDouble()));
        item->setData("[参数G]", QVariantList() << ui->tableWidget->item(i, 5)->text().toDouble() * 10000
                                                << ui->tableWidget->item(i, 6)->text().toDouble() * 10000
                                                << ui->tableWidget->item(i, 7)->text().toDouble() * 10000);
        item->setData("[轴A]", ui->tableWidget->item(i, 8)->text().toDouble() * 0.0001);
        item->setData("[轴B]", ui->tableWidget->item(i, 9)->text().toDouble() * 0.0001);
        item->setData("[旋转角]", ui->tableWidget->item(i, 10)->text().toDouble());
        item->setData("[测试点]", item->data("[中心点]"));
        item->setData("[测试Sdcm]", 0);
    }
}

void HChromatismEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;

    ui->pushButton_2->setEnabled(!d_ptr->data->isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->data->isEmpty());
    ui->pushButton_4->setEnabled(!d_ptr->data->isEmpty());
    ui->tableWidget->setRowCount(d_ptr->data->size());

    int r = 0;
    for (auto key : d_ptr->data->keys())
    {
        showTable(r, key, d_ptr->data->item(key));
        r++;
    }
}

void HChromatismEditWidget::on_pushButton_1_clicked()
{
    auto type = QUuid::createUuid().toString();
    auto item = d_ptr->factory->createChromatismItem("HChromatismItem");
    item->setData("[项类型]", type);
    d_ptr->data->insert(type, item);

    auto row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    showTable(row, type, item);
}

void HChromatismEditWidget::on_pushButton_2_clicked()
{
    auto row = ui->tableWidget->currentRow();
    if (row < 0)
        return;
    d_ptr->data->remove(ui->tableWidget->item(row, 0)->data(Qt::UserRole).toString());
    ui->tableWidget->removeRow(row);
    ui->pushButton_2->setEnabled(!d_ptr->data->isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->data->isEmpty());
    ui->pushButton_4->setEnabled(!d_ptr->data->isEmpty());
}

void HChromatismEditWidget::on_pushButton_3_clicked()
{
    auto row = ui->tableWidget->currentRow();
    if (row < 0)
        return;

    auto a = QVector<double>() << ui->tableWidget->item(row, 8)->text().toDouble() * 0.0001
                               << ui->tableWidget->item(row, 9)->text().toDouble() * 0.0001
                               << ui->tableWidget->item(row, 10)->text().toDouble();
    auto g = HSpecHelper::abt2g(a);
    ui->tableWidget->item(row, 5)->setText(HCore::toString("[参数G]", g[0] * 0.0001));
    ui->tableWidget->item(row, 6)->setText(HCore::toString("[参数G]", g[1] * 0.0001));
    ui->tableWidget->item(row, 7)->setText(HCore::toString("[参数G]", g[2] * 0.0001));
}

void HChromatismEditWidget::on_pushButton_4_clicked()
{
    auto row = ui->tableWidget->currentRow();
    if (row < 0)
        return;

    auto g = QVector<double>() << ui->tableWidget->item(row, 5)->text().toDouble() * 10000
                               << ui->tableWidget->item(row, 6)->text().toDouble() * 10000
                               << ui->tableWidget->item(row, 7)->text().toDouble() * 10000;
    auto a = HSpecHelper::g2abt(g);
    ui->tableWidget->item(row, 8)->setText(HCore::toString("[轴A]", a[0] * 10000));
    ui->tableWidget->item(row, 9)->setText(HCore::toString("[轴B]", a[1] * 10000));
    ui->tableWidget->item(row, 10)->setText(HCore::toString("[旋转角]", a[2] * 10000));
}

void HChromatismEditWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(QStringList() << "[色温]" << "[色容差]" << "[色坐标x]" << "[色坐标y]"
                      << "[参数G]" << "[参数G]" << "[参数G]" << "[轴A]" << "[轴B]" << "[旋转角]");
    delegate->setOrigin(QPoint(1,0));
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("标题") << tr("相关色温") << tr("色容差") << tr("x") << tr("y")
                                               << tr("g11(*10000)") << tr("g12(*10000)") << tr("g22(*10000)")
                                               << tr("a(*0.0001)") << tr("b(*0.0001)") << tr("θ"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setItemDelegate(delegate);
}

void HChromatismEditWidget::showTable(int row, QString key, IChromatismItem *value)
{
    QList<double> g;
    for (auto v : value->data("[参数G]").toList())
        g << v.toDouble();
    auto list =  QStringList() << value->data("[标题]").toString()
                               << HCore::toString("[色温]", value->data("[相关色温]"))
                               << HCore::toString("[色容差]", value->data("[标准Sdcm]"))
                               << HCore::toString("[色坐标x]", value->data("[中心点]").toPointF().x())
                               << HCore::toString("[色坐标y]", value->data("[中心点]").toPointF().y())
                               << HCore::toString("[参数G]", g[0] * 0.0001)
                               << HCore::toString("[参数G]", g[1] * 0.0001)
                               << HCore::toString("[参数G]", g[2] * 0.0001)
                               << HCore::toString("[轴A]", value->data("[轴A]").toDouble() * 10000)
                               << HCore::toString("[轴B]", value->data("[轴B]").toDouble() * 10000)
                               << HCore::toString("[旋转角]", value->data("[旋转角]"));
    auto item = ui->tableWidget->item(row, 0);
    item->setData(Qt::UserRole, key);
    item->setCheckState(value->data("[使用]").toBool() ? Qt::Checked : Qt::Unchecked);
    ui->tableWidget->setRow(row, list);
}

HE_GUI_END_NAMESPACE

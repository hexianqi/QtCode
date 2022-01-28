#include "HLocationEditWidget_p.h"
#include "ui_HLocationEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"

HE_BEGIN_NAMESPACE

HLocationEditWidgetPrivate::HLocationEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HLocationEditWidget::HLocationEditWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLocationEditWidgetPrivate),
    ui(new Ui::HLocationEditWidget)
{
    ui->setupUi(this);
    init();
}

HLocationEditWidget::~HLocationEditWidget()
{
    delete ui;
}

void HLocationEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HLocationEditWidget::typeName()
{
    return "HLocationEditWidget";
}

QWidget *HLocationEditWidget::widget()
{
    return this;
}

ILocation *HLocationEditWidget::createData()
{
    return d_ptr->factory->createLocation("HLocation");
}

void HLocationEditWidget::setData(ILocation *p)
{
//    d_ptr->data = p;
//    showData();
}

void HLocationEditWidget::clearData()
{
//    d_ptr->data = nullptr;
//    ui->tableWidget->clearContents();
//    ui->tableWidget->setRowCount(0);
}

void HLocationEditWidget::saveData()
{
//    if (d_ptr->data == nullptr)
//        return;

//    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
//    {
//        auto key = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
//        auto item = d_ptr->data->item(key);
//        item->setData("[使用]", ui->tableWidget->item(i, 0)->checkState() == Qt::Checked);
//        item->setData("[标题]", ui->tableWidget->item(i, 0)->text());
//        item->setData("[相关色温]", ui->tableWidget->item(i, 1)->text().toDouble());
//        item->setData("[标准Sdcm]", ui->tableWidget->item(i, 2)->text().toDouble());

//        item->setData("[中心点]", QVariantList() << ui->tableWidget->item(i, 3)->text().toDouble() << ui->tableWidget->item(i, 4)->text().toDouble());
//        item->setData("[参数G]", QVariantList() << ui->tableWidget->item(i, 5)->text().toDouble() * 10000
//                                                << ui->tableWidget->item(i, 6)->text().toDouble() * 10000
//                                                << ui->tableWidget->item(i, 7)->text().toDouble() * 10000);
//        item->setData("[轴A]", ui->tableWidget->item(i, 8)->text().toDouble() * 0.0001);
//        item->setData("[轴B]", ui->tableWidget->item(i, 9)->text().toDouble() * 0.0001);
//        item->setData("[旋转角]", ui->tableWidget->item(i, 10)->text().toDouble());
//        item->setData("[测试点]", item->data("[中心点]"));
//        item->setData("[测试Sdcm]", 0);
//    }
}

void HLocationEditWidget::showData()
{
//    if (d_ptr->data == nullptr)
//        return;

//    ui->pushButton_2->setEnabled(!d_ptr->data->isEmpty());
//    ui->pushButton_3->setEnabled(!d_ptr->data->isEmpty());
//    ui->pushButton_4->setEnabled(!d_ptr->data->isEmpty());
//    ui->tableWidget->setRowCount(d_ptr->data->size());

//    int r = 0;
//    for (const auto &key : d_ptr->data->keys())
//    {
//        showTable(r, key, d_ptr->data->item(key));
//        r++;
//    }
}

void HLocationEditWidget::on_pushButton_1_clicked()
{
//    auto type = QUuid::createUuid().toString();
//    auto item = d_ptr->factory->createChromatismItem("HChromatismItem");
//    item->setData("[项类型]", type);
//    d_ptr->data->insert(type, item);

//    auto row = ui->tableWidget->rowCount();
//    ui->tableWidget->insertRow(row);
//    ui->pushButton_2->setEnabled(true);
//    ui->pushButton_3->setEnabled(true);
//    ui->pushButton_4->setEnabled(true);
//    showTable(row, type, item);
}

void HLocationEditWidget::on_pushButton_2_clicked()
{
//    auto row = ui->tableWidget->currentRow();
//    if (row < 0)
//        return;
//    d_ptr->data->remove(ui->tableWidget->item(row, 0)->data(Qt::UserRole).toString());
//    ui->tableWidget->removeRow(row);
//    ui->pushButton_2->setEnabled(!d_ptr->data->isEmpty());
//    ui->pushButton_3->setEnabled(!d_ptr->data->isEmpty());
//    ui->pushButton_4->setEnabled(!d_ptr->data->isEmpty());
}

void HLocationEditWidget::on_pushButton_3_clicked()
{
//    auto row = ui->tableWidget->currentRow();
//    if (row < 0)
//        return;

//    auto a = QVector<double>() << ui->tableWidget->item(row, 8)->text().toDouble() * 0.0001
//                               << ui->tableWidget->item(row, 9)->text().toDouble() * 0.0001
//                               << ui->tableWidget->item(row, 10)->text().toDouble();
//    auto g = HSpecHelper::abt2g(a);
//    ui->tableWidget->item(row, 5)->setText(HCore::toString("[参数G]", g[0] * 0.0001));
//    ui->tableWidget->item(row, 6)->setText(HCore::toString("[参数G]", g[1] * 0.0001));
//    ui->tableWidget->item(row, 7)->setText(HCore::toString("[参数G]", g[2] * 0.0001));
}

void HLocationEditWidget::on_pushButton_4_clicked()
{
//    auto row = ui->tableWidget->currentRow();
//    if (row < 0)
//        return;

//    auto g = QVector<double>() << ui->tableWidget->item(row, 5)->text().toDouble() * 10000
//                               << ui->tableWidget->item(row, 6)->text().toDouble() * 10000
//                               << ui->tableWidget->item(row, 7)->text().toDouble() * 10000;
//    auto a = HSpecHelper::g2abt(g);
//    ui->tableWidget->item(row, 8)->setText(HCore::toString("[轴A]", a[0] * 10000));
//    ui->tableWidget->item(row, 9)->setText(HCore::toString("[轴B]", a[1] * 10000));
//    ui->tableWidget->item(row, 10)->setText(HCore::toString("[旋转角]", a[2] * 10000));
}

void HLocationEditWidget::init()
{
//    auto delegate = new HDoubleSpinBoxDelegate(this);
//    delegate->setType(QStringList() << "[色温]" << "[色容差]" << "[色坐标x]" << "[色坐标y]" << "[参数G]" << "[参数G]" << "[参数G]" << "[轴A]" << "[轴B]" << "[旋转角]");
//    delegate->setOrigin(QPoint(1,0));
//    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("标题") << tr("相关色温") << tr("色容差") << tr("x") << tr("y")
//                                                             << tr("g11(*10000)") << tr("g12(*10000)") << tr("g22(*10000)")
//                                                             << tr("a(*0.0001)") << tr("b(*0.0001)") << tr("θ"));
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
//    ui->tableWidget->setItemDelegate(delegate);
}

HE_END_NAMESPACE

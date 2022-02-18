#include "HLocationEditWidget_p.h"
#include "ui_HLocationEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/ILocation.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HSpinBoxDelegate.h"

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
    d_ptr->data = p;
    showData();
}

void HLocationEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->spinBox_01->blockSignals(true);
    ui->spinBox_04->blockSignals(true);
    ui->spinBox_01->setValue(0);
    ui->spinBox_04->setValue(0);
    ui->spinBox_01->blockSignals(false);
    ui->spinBox_04->blockSignals(false);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
}

void HLocationEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;

    int i,j;
    QVector<QVector<int>> layout;
    auto row = ui->tableWidget->rowCount();
    auto col = ui->tableWidget->columnCount();
    for (i = 0; i < row; i++)
    {
        QVector<int> v;
        for (j = 0; j < col; j++)
            v << ui->tableWidget->item(i, j)->text().toInt();
        layout << v;
    }
    d_ptr->data->setData("[行数]", row);
    d_ptr->data->setData("[列数]", col);
    d_ptr->data->setLayout(layout);
}

void HLocationEditWidget::showData()
{
    if (d_ptr->data == nullptr)
        return;
    int i,j;
    QString text;
    auto row = d_ptr->data->data("[行数]").toInt();
    auto col = d_ptr->data->data("[列数]").toInt();
    auto layout = d_ptr->data->layout();
    ui->spinBox_01->blockSignals(true);
    ui->spinBox_04->blockSignals(true);
    ui->spinBox_01->setValue(row);
    ui->spinBox_04->setValue(col);
    ui->spinBox_01->blockSignals(false);
    ui->spinBox_04->blockSignals(false);
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            text = (i >= layout.size() || j >= layout.at(i).size()) ? "0" : QString::number(layout.at(i).at(j));
            ui->tableWidget->item(i, j)->setText(text);
        }
    }
}

void HLocationEditWidget::on_spinBox_1_valueChanged(int value)
{
    int i,j;
    auto row = ui->tableWidget->rowCount();
    auto col = ui->tableWidget->columnCount();
    ui->tableWidget->setRowCount(value);
    for (i = row; i < value; i++)
    {
        for (j = 0; j < col; j++)
            ui->tableWidget->item(i, j)->setText("0");
    }
}

void HLocationEditWidget::on_spinBox_2_valueChanged(int value)
{
    int i,j;
    auto row = ui->tableWidget->rowCount();
    auto col = ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(value);
    for (j = col; j < value; j++)
    {
        for (i = 0; i < row; i++)
            ui->tableWidget->item(i, j)->setText("0");
    }
}

void HLocationEditWidget::on_pushButton_1_clicked()
{
    auto row = ui->tableWidget->rowCount();
    auto col = ui->tableWidget->columnCount();
    if (row < 1 || col < 1)
        return;

    int i,j;
    auto rf = ui->spinBox_02->value();
    auto rt = ui->spinBox_03->value();
    auto cf = ui->spinBox_05->value();
    auto ct = ui->spinBox_06->value();
    auto text = QString::number(ui->spinBox_07->value());

    if (rf > rt)
        qSwap(rf, rt);
    if (cf > ct)
        qSwap(cf, ct);

    for (i = rf; i <= rt && i < row; i++)
    {
        for (j = cf; j <= ct && j < col; j++)
            ui->tableWidget->item(i, j)->setText(text);
    }
}

void HLocationEditWidget::init()
{
    auto delegate = new HSpinBoxDelegate(this);
    delegate->setType("[布局数值]");
    ui->tableWidget->setItemDelegate(delegate);
    HPluginHelper::initWidget("[布局行数]", ui->spinBox_01);
    HPluginHelper::initWidget("[布局行数]", ui->spinBox_02);
    HPluginHelper::initWidget("[布局行数]", ui->spinBox_03);
    HPluginHelper::initWidget("[布局列数]", ui->spinBox_04);
    HPluginHelper::initWidget("[布局列数]", ui->spinBox_05);
    HPluginHelper::initWidget("[布局列数]", ui->spinBox_06);
    HPluginHelper::initWidget("[布局数值]", ui->spinBox_07);
}

HE_END_NAMESPACE

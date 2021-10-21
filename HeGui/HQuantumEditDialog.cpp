#include "HQuantumEditDialog_p.h"
#include "ui_HQuantumEditDialog.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQuantumEditDialog::HQuantumEditDialog(QWidget *parent) :
    HAbstractTestDataEditDialog(*new HQuantumEditDialogPrivate, parent),
    ui(new Ui::HQuantumEditDialog)
{
    ui->setupUi(this);
    init();
}

HQuantumEditDialog::~HQuantumEditDialog()
{
    qDebug() << __func__;
    delete ui;
}

QString HQuantumEditDialog::typeName()
{
    return "HQuantumEditDialog";
}

void HQuantumEditDialog::setData(ITestData *)
{
}

void HQuantumEditDialog::showData()
{
    Q_D(HQuantumEditDialog);
    auto b = d->data0->data("[自动查找波段]").toBool();
    auto blue = d->data0->data("[蓝光范围]").toPointF();
    auto yellow = d->data0->data("[荧光范围]").toPointF();
    ui->checkBox->setChecked(b);
    ui->doubleSpinBox_01->setValue(blue.x());
    ui->doubleSpinBox_02->setValue(blue.y());
    ui->doubleSpinBox_03->setValue(yellow.x());
    ui->doubleSpinBox_04->setValue(yellow.y());
}

void HQuantumEditDialog::saveData()
{
    Q_D(HQuantumEditDialog);
    auto b1 = ui->doubleSpinBox_01->value();
    auto b2 = ui->doubleSpinBox_02->value();
    auto y1 = ui->doubleSpinBox_03->value();
    auto y2 = ui->doubleSpinBox_04->value();
    if (b1 > b2)
        qSwap(b1, b2);
    if (y1 > y2)
        qSwap(y1, y2);
    d->data0->setData("[自动查找波段]", ui->checkBox->isChecked());
    d->data0->setData("[蓝光范围]", QPointF(b1, b2));
    d->data0->setData("[荧光范围]", QPointF(y1, y2));
}

void HQuantumEditDialog::init()
{
    HPluginHelper::initWidget("[光谱波长]", ui->doubleSpinBox_01);
    HPluginHelper::initWidget("[光谱波长]", ui->doubleSpinBox_02);
    HPluginHelper::initWidget("[光谱波长]", ui->doubleSpinBox_03);
    HPluginHelper::initWidget("[光谱波长]", ui->doubleSpinBox_04);
    setWindowTitle(tr("光量子配置"));
    showData();
}

HE_GUI_END_NAMESPACE

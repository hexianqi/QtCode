#include "HSpecSettingDialog_p.h"
#include "ui_HSpecSettingDialog.h"
#include "HePlugin/HPluginHelper.h"
#include "HeData/HSpecSetting.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecSettingDialog::HSpecSettingDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSpecSettingDialogPrivate),
    ui(new Ui::HSpecSettingDialog)
{
    ui->setupUi(this);
    init();
}

HSpecSettingDialog::~HSpecSettingDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecSettingDialog::setData(HSpecSetting *p)
{
    d_ptr->data = p;
    showData();
}

void HSpecSettingDialog::on_pushButton_1_clicked()
{
    d_ptr->data->restoreDefault();
    showData();
}

void HSpecSettingDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HSpecSettingDialog::showData()
{
    auto pel = d_ptr->data->data("[光谱保留像元]").toPoint();
    auto time = d_ptr->data->data("[积分时间范围]").toPointF();
    auto wave = d_ptr->data->data("[光谱波长范围]").toPointF();
    auto sample = d_ptr->data->data("[光谱采样范围]").toPointF();
    ui->spinBox_101->setValue(d_ptr->data->data("[光谱采样延时]").toInt());
    ui->spinBox_102->setValue(d_ptr->data->data("[光谱平均次数]").toInt());
    ui->spinBox_201->setValue(pel.x());
    ui->spinBox_202->setValue(pel.y());
    ui->spinBox_203->setValue(d_ptr->data->data("[光谱平滑帧数]").toInt());
    ui->spinBox_204->setValue(d_ptr->data->data("[光谱平滑次数]").toInt());
    ui->spinBox_205->setValue(d_ptr->data->data("[光谱平滑范围]").toInt());
    ui->doubleSpinBox_101->setValue(time.x());
    ui->doubleSpinBox_102->setValue(time.y());
    ui->doubleSpinBox_103->setValue(wave.x());
    ui->doubleSpinBox_104->setValue(wave.y());
    ui->doubleSpinBox_105->setValue(sample.x());
    ui->doubleSpinBox_106->setValue(sample.y());
    ui->doubleSpinBox_107->setValue(d_ptr->data->data("[标准色温]").toDouble());
    ui->doubleSpinBox_201->setValue(d_ptr->data->data("[光谱固定暗底]").toDouble());
    ui->doubleSpinBox_202->setValue(d_ptr->data->data("[光谱左右暗底]").toDouble());
}

void HSpecSettingDialog::saveData()
{
    d_ptr->data->setData("[光谱采样延时]", ui->spinBox_101->value());
    d_ptr->data->setData("[光谱平均次数]", ui->spinBox_102->value());
    d_ptr->data->setData("[光谱保留像元]", QPoint(ui->spinBox_201->value(), ui->spinBox_202->value()));
    d_ptr->data->setData("[光谱平滑帧数]", ui->spinBox_203->value());
    d_ptr->data->setData("[光谱平滑次数]", ui->spinBox_204->value());
    d_ptr->data->setData("[光谱平滑范围]", ui->spinBox_205->value());
    d_ptr->data->setData("[积分时间范围]", QPointF(ui->doubleSpinBox_101->value(), ui->doubleSpinBox_102->value()));
    d_ptr->data->setData("[光谱波长范围]", QPointF(ui->doubleSpinBox_103->value(), ui->doubleSpinBox_104->value()));
    d_ptr->data->setData("[光谱采样范围]", QPointF(ui->doubleSpinBox_105->value(), ui->doubleSpinBox_106->value()));
    d_ptr->data->setData("[标准色温]",     ui->doubleSpinBox_107->value());
    d_ptr->data->setData("[光谱固定暗底]", ui->doubleSpinBox_201->value());
    d_ptr->data->setData("[光谱左右暗底]", ui->doubleSpinBox_202->value());
}

void HSpecSettingDialog::init()
{
    HPluginHelper::initWidget("[光谱采样延时]", ui->spinBox_101);
    HPluginHelper::initWidget("[光谱平均次数]", ui->spinBox_102);
    HPluginHelper::initWidget("[光谱保留像元]", ui->spinBox_201);
    HPluginHelper::initWidget("[光谱保留像元]", ui->spinBox_202);
    HPluginHelper::initWidget("[光谱平滑帧数]", ui->spinBox_203);
    HPluginHelper::initWidget("[光谱平滑次数]", ui->spinBox_204);
    HPluginHelper::initWidget("[光谱平滑范围]", ui->spinBox_205);
    HPluginHelper::initWidget("[积分时间]",     ui->doubleSpinBox_101);
    HPluginHelper::initWidget("[积分时间]",     ui->doubleSpinBox_102);
    HPluginHelper::initWidget("[光谱波长]",     ui->doubleSpinBox_103);
    HPluginHelper::initWidget("[光谱波长]",     ui->doubleSpinBox_104);
    HPluginHelper::initWidget("[光谱采样]",     ui->doubleSpinBox_105);
    HPluginHelper::initWidget("[光谱采样]",     ui->doubleSpinBox_106);
    HPluginHelper::initWidget("[标准色温]",     ui->doubleSpinBox_107);
    HPluginHelper::initWidget("[光谱固定暗底]", ui->doubleSpinBox_201);
    HPluginHelper::initWidget("[光谱左右暗底]", ui->doubleSpinBox_202);
    ui->splitter->setStretchFactor(1, 1);
    setWindowTitle(tr("光谱参数设置"));
}

HE_GUI_END_NAMESPACE

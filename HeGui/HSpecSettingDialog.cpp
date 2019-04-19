#include "HSpecSettingDialog_p.h"
#include "ui_HSpecSettingDialog.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include "HeData/HSpecSetting.h"
#include <QtCore/QDebug>

HE_CORE_USE_NAMESPACE

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
    auto integralTime = d_ptr->data->data("[积分时间范围]").toPointF();
    ui->lineEdit_1001->setText(toString("[积分时间]", integralTime.x()));
    ui->lineEdit_1002->setText(toString("[积分时间]", integralTime.y()));
    auto wave = d_ptr->data->data("[光谱波长范围]").toPointF();
    ui->lineEdit_1003->setText(toString("[光谱波长]", wave.x()));
    ui->lineEdit_1004->setText(toString("[光谱波长]", wave.y()));
    auto sample = d_ptr->data->data("[光谱采样范围]").toPointF();
    ui->lineEdit_1005->setText(toString("[光谱采样]", sample.x()));
    ui->lineEdit_1006->setText(toString("[光谱采样]", sample.y()));
    ui->lineEdit_1007->setText(toString("[光谱采样延时]", d_ptr->data->data("[光谱采样延时]")));
    ui->lineEdit_1008->setText(toString("[光谱平均次数]", d_ptr->data->data("[光谱平均次数]")));
    ui->lineEdit_1009->setText(toString("[标准色温]", d_ptr->data->data("[标准色温]")));
    auto pel = d_ptr->data->data("[光谱保留像元]").toPoint();
    ui->lineEdit_2001->setText(toString("[光谱保留像元]", pel.x()));
    ui->lineEdit_2002->setText(toString("[光谱保留像元]", pel.y()));
    ui->lineEdit_2003->setText(toString("[光谱固定暗底]", d_ptr->data->data("[光谱固定暗底]")));
    ui->lineEdit_2004->setText(toString("[光谱左右暗底差]", d_ptr->data->data("[光谱左右暗底差]")));
    ui->lineEdit_2005->setText(toString("[光谱平滑帧数]", d_ptr->data->data("[光谱平滑帧数]")));
    ui->lineEdit_2006->setText(toString("[光谱平滑次数]", d_ptr->data->data("[光谱平滑次数]")));
    ui->lineEdit_2007->setText(toString("[光谱平滑范围]", d_ptr->data->data("[光谱平滑范围]")));
}

void HSpecSettingDialog::saveData()
{
    QPoint p1;
    QPointF p2;
    p2.setX(ui->lineEdit_1001->text().toDouble());
    p2.setY(ui->lineEdit_1002->text().toDouble());
    d_ptr->data->setData("[积分时间范围]", p2);
    p2.setX(ui->lineEdit_1003->text().toDouble());
    p2.setY(ui->lineEdit_1004->text().toDouble());
    d_ptr->data->setData("[光谱波长范围]", p2);
    p2.setX(ui->lineEdit_1005->text().toDouble());
    p2.setY(ui->lineEdit_1006->text().toDouble());
    d_ptr->data->setData("[光谱采样范围]", p2);
    d_ptr->data->setData("[光谱采样延时]", ui->lineEdit_1007->text().toInt());
    d_ptr->data->setData("[光谱平均次数]", ui->lineEdit_1008->text().toInt());
    d_ptr->data->setData("[标准色温]", ui->lineEdit_1009->text().toDouble());
    p1.setX(ui->lineEdit_2001->text().toInt());
    p1.setY(ui->lineEdit_2002->text().toInt());
    d_ptr->data->setData("[光谱保留像元]", p1);
    d_ptr->data->setData("[光谱固定暗底]", ui->lineEdit_2003->text().toDouble());
    d_ptr->data->setData("[光谱左右暗底差]", ui->lineEdit_2004->text().toDouble());
    d_ptr->data->setData("[光谱平滑帧数]", ui->lineEdit_2005->text().toInt());
    d_ptr->data->setData("[光谱平滑次数]", ui->lineEdit_2006->text().toInt());
    d_ptr->data->setData("[光谱平滑范围]", ui->lineEdit_2007->text().toInt());
}

void HSpecSettingDialog::init()
{
    QValidator *v[12];
    v[0] = toFormatInfo("[积分时间]")->toDoubleValidator(this);
    v[1] = toFormatInfo("[光谱波长]")->toDoubleValidator(this);
    v[2] = toFormatInfo("[光谱采样]")->toDoubleValidator(this);
    v[3] = toFormatInfo("[光谱采样延时]")->toIntValidator(this);
    v[4] = toFormatInfo("[光谱平均次数]")->toIntValidator(this);
    v[5] = toFormatInfo("[标准色温]")->toDoubleValidator(this);
    v[6] = toFormatInfo("[光谱保留像元]")->toIntValidator(this);
    v[7] = toFormatInfo("[光谱固定暗底]")->toDoubleValidator(this);
    v[8] = toFormatInfo("[光谱左右暗底差]")->toDoubleValidator(this);
    v[9] = toFormatInfo("[光谱平滑帧数]")->toIntValidator(this);
    v[10] = toFormatInfo("[光谱平滑次数]")->toIntValidator(this);
    v[11] = toFormatInfo("[光谱平滑范围]")->toIntValidator(this);
    ui->lineEdit_1001->setValidator(v[0]);
    ui->lineEdit_1002->setValidator(v[0]);
    ui->lineEdit_1003->setValidator(v[1]);
    ui->lineEdit_1004->setValidator(v[1]);
    ui->lineEdit_1005->setValidator(v[2]);
    ui->lineEdit_1006->setValidator(v[2]);
    ui->lineEdit_1007->setValidator(v[3]);
    ui->lineEdit_1008->setValidator(v[4]);
    ui->lineEdit_1009->setValidator(v[5]);
    ui->lineEdit_2001->setValidator(v[6]);
    ui->lineEdit_2002->setValidator(v[6]);
    ui->lineEdit_2003->setValidator(v[7]);
    ui->lineEdit_2004->setValidator(v[8]);
    ui->lineEdit_2005->setValidator(v[9]);
    ui->lineEdit_2006->setValidator(v[10]);
    ui->lineEdit_2007->setValidator(v[11]);
    ui->splitter->setStretchFactor(1, 1);
    setWindowTitle(tr("光谱参数设置"));
}

HE_GUI_END_NAMESPACE

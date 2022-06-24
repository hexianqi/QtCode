#include "HSpecPrintSettingDialog_p.h"
#include "ui_HSpecPrintSettingDialog.h"
#include "HeData/IPrintTemplate.h"

HE_BEGIN_NAMESPACE

HSpecPrintSettingDialog::HSpecPrintSettingDialog(QWidget *parent) :
    HAbstractPrintSettingDialog(*new HSpecPrintSettingDialogPrivate, parent),
    ui(new Ui::HSpecPrintSettingDialog)
{
    ui->setupUi(this);
    init();
}

HSpecPrintSettingDialog::~HSpecPrintSettingDialog()
{
    delete ui;
}

QString HSpecPrintSettingDialog::typeName()
{
    return "HSpecPrintSettingDialog";
}

void HSpecPrintSettingDialog::showData()
{
    Q_D(HSpecPrintSettingDialog);
    auto data = d->printTemplate->param();
    ui->lineEdit_1->setText(data.value("Header").toString());
    ui->lineEdit_2->setText(data.value("Title").toString());
    ui->checkBox_1->setChecked(data.value("DrawHeader").toBool());
    ui->checkBox_2->setChecked(data.value("DrawLogo").toBool());
    ui->checkBox_3->setChecked(data.value("DrawRibbon").toBool());
    ui->checkBox_4->setChecked(data.value("DrawChromatism").toBool());
}

void HSpecPrintSettingDialog::saveData()
{
    Q_D(HSpecPrintSettingDialog);
    auto data = d->printTemplate->param();
    data["Header"] = ui->lineEdit_1->text();
    data["Title"] = ui->lineEdit_2->text();
    data["DrawHeader"] = ui->checkBox_1->isChecked();
    data["DrawLogo"] = ui->checkBox_2->isChecked();
    data["DrawRibbon"] = ui->checkBox_3->isChecked();
    data["DrawChromatism"] = ui->checkBox_4->isChecked();
    d->printTemplate->setParam(data);
}

void HSpecPrintSettingDialog::init()
{
    setWindowTitle(tr("光谱打印配置"));
}

HE_END_NAMESPACE

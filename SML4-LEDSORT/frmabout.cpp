#include "frmabout.h"
#include "ui_frmabout.h"
#include "unitpublic.h"
#include "qmessagebox.h"
#include "qsettings.h"

Frmabout::Frmabout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frmabout)
{
    ui->setupUi(this);
    this->setWindowTitle("关于，软件注册");
    if(unitpublic::giregstauts==1){
        ui->lbabout->setText("SML分光机测试软件V1.0\r\n软件已注册！");
        ui->edtcode->setText(unitpublic::gsregcode);
        ui->edtcode->setReadOnly(true);
        ui->btnreg->setEnabled(false);
    }else {
        ui->lbabout->setText("SML分光机测试软件V1.0\r\n软件未注册！");
        ui->edtcode->setText("");
        ui->edtcode->setReadOnly(false);
        ui->btnreg->setEnabled(true);
    }
    ui->edtsn->setText(unitpublic::gssoftsn);
    ui->edtsn->setReadOnly(true);   //只读
}

Frmabout::~Frmabout()
{
    delete ui;
}

void Frmabout::on_toolButton_2_clicked()
{
    this->close();
}

void Frmabout::on_btnreg_clicked()
{   //注册
    if(unitpublic::softisreg(ui->edtcode->text())==1){
        unitpublic::giregstauts = 1;
        unitpublic::gsregcode = ui->edtcode->text();
        QSettings settings(unitpublic::gsCurPath+"/ledsort.cfg",QSettings::IniFormat); //
        settings.setValue("system/regcode",unitpublic::gsregcode);   //修改配置文件，设置将要打开的工程文件名称
        QMessageBox::information(NULL,"提示","注册成功！");
    }else
    {
        unitpublic::giregstauts = 0;
        QMessageBox::information(NULL,"提示","注册失败！");
    }
}

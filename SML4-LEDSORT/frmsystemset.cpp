#include "frmsystemset.h"
#include "ui_frmsystemset.h"
//生成二维码
#include "unitpublic.h"
#include "unitprofile.h"
#include "qmessagebox.h"

Frmsystemset::Frmsystemset(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frmsystemset)
{
    ui->setupUi(this);
    itag = iindex;
    this->setGeometry(0,0,parent->geometry().width(),parent->geometry().height());          //填充整个父窗口
    if(unitprofile::basesetpara[itag].auto_print)
        ui->cbautoprint->setCheckState(Qt::Checked);
    else
        ui->cbautoprint->setCheckState(Qt::Unchecked);
    ui->spnsize->setValue(unitprofile::basesetpara[itag].qrcode_size);
    ui->spmaxcount->setValue(unitprofile::basesetpara[itag].bin_maxcount);

    ui->spsotbit->setValue(unitprofile::basesetpara[itag].sot_bit); //SOT输入端口号
    ui->cbsottype->setCurrentIndex(unitprofile::basesetpara[itag].sot_type);    //SOT信号有效电平
    ui->cbbinbit->setCurrentIndex(unitprofile::basesetpara[itag].eot_binout);
    ui->speotbit->setValue(unitprofile::basesetpara[itag].eot_bit);
    ui->cbeottype->setCurrentIndex(unitprofile::basesetpara[itag].eot_type);
}

Frmsystemset::~Frmsystemset()
{
    delete ui;
}

//  槽函数，接收主页面保存系统设置参数
void Frmsystemset::msavesysset(int iindex)
{
    if(itag == iindex){
        if((ui->cbbinbit->currentIndex()==0)&&(ui->speotbit->value()<8)){   //bin,bit0-7
            QMessageBox::warning(NULL,"提示","保存失败，EOT信号输出端口与BIN号端口冲突，请重新设置！");
            return;
        }
        if((ui->cbbinbit->currentIndex()==1)&&(ui->speotbit->value()>7)){   //bin,bit8-15
            QMessageBox::warning(NULL,"提示","保存失败，EOT信号输出端口与BIN号端口冲突，请重新设置！");
            return;
        }
        if(ui->cbautoprint->checkState() == Qt::Checked)
            unitprofile::basesetpara[itag].auto_print  = true;
        else
            unitprofile::basesetpara[itag].auto_print  = false;
        unitprofile::basesetpara[itag].bin_maxcount = ui->spmaxcount->value();
        unitprofile::basesetpara[itag].qrcode_size = ui->spnsize->value();

        unitprofile::basesetpara[itag].sot_bit = ui->spsotbit->value();
        unitprofile::basesetpara[itag].sot_type = ui->cbsottype->currentIndex();
        unitprofile::basesetpara[itag].eot_binout = ui->cbbinbit->currentIndex();
        unitprofile::basesetpara[itag].eot_bit=ui->speotbit->value();
        unitprofile::basesetpara[itag].eot_type=ui->cbeottype->currentIndex();

        unitprofile::saveprofile(unitpublic::gscurprofile);
//        unitpublic::testcmd[itag] = CMD_TEST_INIT;    //初始化导入参数
        unitpublic::filedb2memdb(itag);
        QMessageBox::information(NULL,"提示","当前测试工位系统参数保存完成！");
    }
}

void Frmsystemset::on_toolButton_13_clicked()
{
    QString text="123456";
    unitpublic::getbinpara(itag,ui->spbinid->value(),text);     //获取该BIN号对应的分级参数
    text = text + QString("COUNT:%1\r").arg(ui->spmaxcount->value());   //数量
    ui->lbqrcode->setFixedSize(ui->spnsize->value(),ui->spnsize->value());  //设置二维码图片尺寸大小
    QPixmap pmap = unitpublic::createQRCode(text,ui->spnsize->value());     //生成二维码图片
    ui->lbqrcode->setPixmap(pmap);      //显示预览二维码图片
    ui->memcode->setText(text);
    pmap.save(QString("%1//QRcode_bin%2.jpg").arg(unitpublic::gsCurPath).arg(ui->spbinid->value()));    //二维码图片保存
}

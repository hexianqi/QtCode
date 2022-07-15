#include "fmoptstatus.h"
#include "ui_fmoptstatus.h"
#include <qpixmapcache.h>
#include "unitpublic.h"

FmOptStatus::FmOptStatus(QString ltext,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FmOptStatus)
{
    ui->setupUi(this);
    ui->lbtext->setText(ltext);
    QPixmapCache::clear();
    QImage imageset;
    imageset.load(":/new/prefix1/res/pic/qnone.png");     //初始化，联机状态未知
    ui->lblamp1->setPixmap(QPixmap::fromImage(imageset));
    ui->lblamp2->setPixmap(QPixmap::fromImage(imageset));
    ui->lblamp3->setPixmap(QPixmap::fromImage(imageset));
    ui->lblamp4->setPixmap(QPixmap::fromImage(imageset));
}

FmOptStatus::~FmOptStatus()
{
    delete ui;
}


//设置连接状态指示灯颜色，联机-绿色，掉线-红色
//传入参数：iindex，光谱仪或测试机设备编号
//         bcon，连接状态，true-联机，false-掉线
void FmOptStatus::setConStatus(qint8 iindex,bool bcon)
{
    QPixmapCache::clear();
    QImage imageset;
    if(bcon){
        imageset.load(":/new/prefix1/res/pic/qgreen.png");     //初始化，联机状态未知
    }else{
        imageset.load(":/new/prefix1/res/pic/qred.png");     //初始化，联机状态未知
    }
    switch (iindex) {
    case ST_INDEX_1:{
        ui->lblamp1->setPixmap(QPixmap::fromImage(imageset));   //如不进行Qlabel与图片的大小调整及适配，直接执行这条语句即可
        break;
    }
    case ST_INDEX_2:{
        ui->lblamp2->setPixmap(QPixmap::fromImage(imageset));
        break;
    }
    case ST_INDEX_3:{
        ui->lblamp3->setPixmap(QPixmap::fromImage(imageset));
        break;
    }
    case ST_INDEX_4:{
        ui->lblamp4->setPixmap(QPixmap::fromImage(imageset));
        break;
    }

    }
}

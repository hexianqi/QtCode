#include "frmtestdata.h"
#include "ui_frmtestdata.h"
#include "qstandarditemmodel.h"
#include "unitpublic.h"
#include "unitprofile.h"
#include "qdebug.h"
#include "qsqlquery.h"
#include "qsqlerror.h"

Frmtestdata::Frmtestdata(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frmtestdata)
{
    ui->setupUi(this);
    itag = iindex;

    this->setGeometry(0,0,parent->geometry().width(),parent->geometry().height());          //填充整个父窗口
    ui->gbbin->setGeometry(this->geometry().width()-180,0,180,this->geometry().height());   //分BIN区域
    ui->tvbin->setGeometry(0,16,ui->gbbin->geometry().width(),this->geometry().height()-16);
    ui->gbtongji->setGeometry(0,0,this->geometry().width()-ui->gbbin->geometry().width(),180);  //统计分析数据区域
    ui->tvtongji->setGeometry(0,0,ui->gbtongji->geometry().width(),ui->gbtongji->geometry().height());
    ui->gbdata->setGeometry(0,182,this->geometry().width()-ui->gbbin->geometry().width(),this->geometry().height()-182);    //测试结果数据区域
    ui->tvtestdata->setGeometry(0,0,ui->gbdata->geometry().width(),ui->gbdata->geometry().height());
    tvDispInit();   //初始化列表数据
}

Frmtestdata::~Frmtestdata()
{
    delete ui;
}

void Frmtestdata::mupdatetestdata(int iindex)
{
    if(itag == iindex)
    {
        tvDispInit();
    }
}

//数据列表显示初始化，定义列字段标题、列数量等
//不同的测试工位，取对应工位的测试设置参数进行初始化显示
void Frmtestdata::tvDispInit()
{
    modeltj = new QStandardItemModel(); //初始化统计分析列表
    modeltj->setColumnCount(6); //显示6列
    ui->tvtongji->setModel(modeltj);
    ui->tvtongji->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    ui->tvtongji->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tvtongji->verticalHeader()->setDefaultSectionSize(20);  //行高
    ui->tvtongji->horizontalHeader()->hide();   //不显示列头
    ui->tvtongji->verticalHeader()->hide();     //不显示行号

    ui->tvtongji->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //表头信息显示居左
    modeltj->setItem(0,0,new QStandardItem("LED类型"));
    ui->tvtongji->setColumnWidth(0,80);
    modeltj->setItem(0,1,new QStandardItem(lstledtype[unitprofile::basesetpara[itag].led_type]));
    ui->tvtongji->setColumnWidth(1,350);
    modeltj->setItem(0,2,new QStandardItem("测试时间"));
    ui->tvtongji->setColumnWidth(2,80);
    modeltj->setItem(0,3,new QStandardItem("38ms"));
    ui->tvtongji->setColumnWidth(3,80);
    modeltj->setItem(0,4,new QStandardItem("测试状态"));
    ui->tvtongji->setColumnWidth(4,80);
    modeltj->setItem(0,5,new QStandardItem("暂停测试！"));
    ui->tvtongji->setColumnWidth(5,180);
    modeltj->setItem(1,0,new QStandardItem("工程文件"));
    modeltj->setItem(1,1,new QStandardItem(unitpublic::gscurprofile));
    modeltj->setItem(1,2,new QStandardItem("累计产量"));
    modeltj->setItem(1,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].sumcount)));
    modeltj->setItem(2,2,new QStandardItem("有效产量"));
    modeltj->setItem(2,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].valcount)));
    modeltj->setItem(3,2,new QStandardItem("UPH(K/H)"));
    modeltj->setItem(3,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].uph,'f',2)));
    modeltj->setItem(1,4,new QStandardItem("IO卡状态"));
    modeltj->setItem(1,5,new QStandardItem("打开失败"));

    modeltj->item(0,0)->setData(QColor(255, 255, 0), Qt::BackgroundRole);//设置该行列的背景颜色
    modeltj->item(1,0)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(0,2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(1,2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(2,2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(3,2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(0,4)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(1,4)->setData(QColor(255, 255, 0), Qt::BackgroundRole);
    modeltj->item(1,5)->setData(QColor(255, 0, 0), Qt::BackgroundRole);

    modeldata = new QStandardItemModel();
    ui->tvtestdata->setModel(modeldata);
    //ui->tvtestdata->verticalHeader()->setVisible(false);     //不显示左侧序列号标题
    ui->tvtestdata->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: black;"          //文字颜色
                                                     "font:bold 11pt;"      //字体大小
                                                     "padding-left: 12px;"
                                                     "border: 1px solid #6c6c6c;}");

    ui->tvtestdata->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    ui->tvtestdata->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    //表头信息显示居左
    ui->tvtestdata->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tvtestdata->verticalHeader()->setDefaultSectionSize(20);
        //设置列宽不可变
    //ui->tvtestdata->horizontalHeader()->setStretchLastSection(true); //设置最后一列填充整个表头
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //均分所有列，宽度
    ui->tvtestdata->horizontalHeader()->hide();   //不显示列头
    ui->tvtestdata->setAlternatingRowColors(true);  //隔行换色
    ui->tvtestdata->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn); //滚动条
    switch (unitprofile::basesetpara->led_type) {
    case 0:{iledcount = 1;break;}    //单晶
    case 1:{iledcount = 2;break;}    //双晶
    default: {iledcount = 3;break;} //三晶
    }

    for (int i=0;i<4;i++) {
        modeldata->setItem(1,i,new QStandardItem("测试项目"));
        modeldata->setItem(2,i,new QStandardItem("最大值"));
        modeldata->setItem(3,i,new QStandardItem("最小值"));
        modeldata->setItem(4,i,new QStandardItem("平均值"));
        modeldata->setItem(5,i,new QStandardItem("NG数量"));
        modeldata->setItem(6,i,new QStandardItem("NG占比"));
    }
    int icolbegin = 0;
    for (int k=0;k<iledcount;k++){  //晶片数量
        icolbegin = modeldata->columnCount();      //初始3列
        for (int i=0;i<TESTITEM_COUNT;i++) {    //测试参数数量
            modeldata->setItem(0,k*TESTITEM_COUNT+i+4,new QStandardItem(QString("晶片%1").arg(k+1)));     //第一行，显示晶片序号
            modeldata->setItem(1,k*TESTITEM_COUNT+i+4,new QStandardItem(lstTestItemName[i]));           //第二行，显示测试项目名称
            if(unitprofile::testitempara[itag][k][i].test_enable){  //是否显示该列
                ui->tvtestdata->horizontalHeader()->showSection(k*TESTITEM_COUNT+i+4);
            }else{
                ui->tvtestdata->horizontalHeader()->hideSection(k*TESTITEM_COUNT+i+4);
            }
        }
        ui->tvtestdata->setSpan(0,icolbegin,1,modeldata->columnCount()-icolbegin);    //合并"晶1/2/3"列，即从第0行、第icolbegin列开始的1行model->columnCount()-icolbegin列
    }
    for (int i=0;i<modeldata->columnCount();i++) {
        modeldata->setItem(7,i,new QStandardItem(""));  //增加一空行,作为测试数据与最值统计数据的分隔
        ui->tvtestdata->setColumnWidth(i,45);
        modeldata->item(7,i)->setData(QColor(80, 100, 80), Qt::BackgroundRole);  //空行背景色
    }
    modeldata->setItem(8,0,new QStandardItem("ID"));        //前4列显示的内容
    modeldata->setItem(8,1,new QStandardItem("BIN"));
    modeldata->setItem(8,2,new QStandardItem("POL"));
    modeldata->setItem(8,3,new QStandardItem("测试结果"));
    ui->tvtestdata->setColumnWidth(0,45);
    ui->tvtestdata->setColumnWidth(1,40);
    ui->tvtestdata->setColumnWidth(2,40);
    ui->tvtestdata->setColumnWidth(3,60);
    ui->tvtestdata->setSpan(0,0,1,4);
    ui->tvtestdata->setSpan(1,0,1,4);
    ui->tvtestdata->setSpan(2,0,1,4);
    ui->tvtestdata->setSpan(3,0,1,4);
    ui->tvtestdata->setSpan(4,0,1,4);
    ui->tvtestdata->setSpan(5,0,1,4);
    ui->tvtestdata->setSpan(6,0,1,4);
    ui->tvtestdata->setSpan(7,0,1,modeldata->columnCount());//合并整个空行
    for (int i=0;i<maxrowcount;i++) {  //最多显示800行数据，为了保证桌面显示刷新效率，避免过多数据导致测试效率低
        for (int k=0;k<modeldata->columnCount();k++) {
            modeldata->setItem(9+i,k,new QStandardItem(""));
        }
    }

    modelbin = new QStandardItemModel();
    modelbin->setColumnCount(3);  //列数量根据该工位选择的测试参数确定，比如VF/IR/IV/CIE_X/CIE_Y/CCT/Ra/WD/WP，表示有9个测试对象
    modelbin->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("BIN"));         //为什么用fromLocal8Bit会乱码，
    modelbin->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("数量"));
    modelbin->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("占比%"));
    ui->tvbin->setModel(modelbin);
    ui->tvbin->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //表头信息显示居左
    ui->tvbin->verticalHeader()->hide();
    ui->tvbin->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    ui->tvbin->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
//    ui->tvbin->setSortingEnabled(true); //允许排序，则标题块上会出现一个上下三角的小图标
    ui->tvbin->verticalHeader()->setDefaultSectionSize(18);
    ui->tvbin->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                           "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    for (int i=0;i<256;i++) {
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant(i+1),Qt::EditRole);
        modelbin->setItem(i,0,item);        //按数值排序，注意BIN号是从1开始
        ui->tvbin->setColumnWidth(0,35);
        QStandardItem *item1 = new QStandardItem;
        item1->setData(QVariant(0),Qt::EditRole);
        modelbin->setItem(i,1,item1);        //按数值排序
        ui->tvbin->setColumnWidth(1,70);
        QStandardItem *item2 = new QStandardItem;
        item2->setData(QVariant(0),Qt::EditRole);
        modelbin->setItem(i,2,item2);        //按数值排序
        ui->tvbin->setColumnWidth(2,55);
    }
}

void Frmtestdata::mteststatus(int iindex,int istatus)
{
    if(iindex == itag){
        if(istatus == 1){   //测试中...
            modeltj->setData(modeltj->index(0,5),QString("测试中...%1").arg(unitpublic::iruntime[itag]));
        }else
        {               //暂停测试！
            modeltj->setData(modeltj->index(0,5),"暂停测试！");
        }
    }
}

void Frmtestdata::mtesttime(int iindex,int itesttime)
{
    if(iindex == itag){
        modeltj->setData(modeltj->index(0,3),QString::number(itesttime)+" ms"); //现实测试耗时，包括数据显示、存储等时间
    }
}
//显示测试结果，线程中发出信号，槽函数
void Frmtestdata::mtestdata(int iindex)
{
    if(iindex == itag){
        //1.刷新系统信息

        //2.显示统计数据//lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};，注意列数量与测试参数对应
        for (int i=0;i<iledcount;i++){
            //最大值
            modeldata->setData(modeldata->index(2,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VF")].maxdata,'f',3));
            modeldata->setData(modeldata->index(2,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VFL")].maxdata,'f',3));
            modeldata->setData(modeldata->index(2,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IR")].maxdata,'f',3));
            modeldata->setData(modeldata->index(2,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IV")].maxdata,'f',2));
            modeldata->setData(modeldata->index(2,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WD")].maxdata,'f',1));
            modeldata->setData(modeldata->index(2,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WP")].maxdata,'f',1));
            modeldata->setData(modeldata->index(2,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("Ra")].maxdata,'f',1));
            modeldata->setData(modeldata->index(2,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CCT")].maxdata,'f',0));
            modeldata->setData(modeldata->index(2,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_x")].maxdata,'f',4));
            modeldata->setData(modeldata->index(2,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_y")].maxdata,'f',4));
            modeldata->setData(modeldata->index(2,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("SDCM")].maxdata,'f',0));
            modeldata->setData(modeldata->index(2,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("R9")].maxdata,'f',1));
            //最小值
            modeldata->setData(modeldata->index(3,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VF")].mindata,'f',3));
            modeldata->setData(modeldata->index(3,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VFL")].mindata,'f',3));
            modeldata->setData(modeldata->index(3,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IR")].mindata,'f',3));
            modeldata->setData(modeldata->index(3,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IV")].mindata,'f',2));
            modeldata->setData(modeldata->index(3,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WD")].mindata,'f',1));
            modeldata->setData(modeldata->index(3,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WP")].mindata,'f',1));
            modeldata->setData(modeldata->index(3,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("Ra")].mindata,'f',1));
            modeldata->setData(modeldata->index(3,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CCT")].mindata,'f',0));
            modeldata->setData(modeldata->index(3,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_x")].mindata,'f',4));
            modeldata->setData(modeldata->index(3,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_y")].mindata,'f',4));
            modeldata->setData(modeldata->index(3,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("SDCM")].mindata,'f',0));
            modeldata->setData(modeldata->index(3,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("R9")].mindata,'f',1));
            //平均值
            modeldata->setData(modeldata->index(4,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VF")].avgdata,'f',3));
            modeldata->setData(modeldata->index(4,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VFL")].avgdata,'f',3));
            modeldata->setData(modeldata->index(4,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IR")].avgdata,'f',3));
            modeldata->setData(modeldata->index(4,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IV")].avgdata,'f',2));
            modeldata->setData(modeldata->index(4,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WD")].avgdata,'f',1));
            modeldata->setData(modeldata->index(4,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WP")].avgdata,'f',1));
            modeldata->setData(modeldata->index(4,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("Ra")].avgdata,'f',1));
            modeldata->setData(modeldata->index(4,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CCT")].avgdata,'f',0));
            modeldata->setData(modeldata->index(4,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_x")].avgdata,'f',4));
            modeldata->setData(modeldata->index(4,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_y")].avgdata,'f',4));
            modeldata->setData(modeldata->index(4,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("SDCM")].avgdata,'f',0));
            modeldata->setData(modeldata->index(4,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("R9")].avgdata,'f',1));
            //NG数量
            modeldata->setData(modeldata->index(5,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VF")].ngcount));
            modeldata->setData(modeldata->index(5,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VFL")].ngcount));
            modeldata->setData(modeldata->index(5,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IR")].ngcount));
            modeldata->setData(modeldata->index(5,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IV")].ngcount));
            modeldata->setData(modeldata->index(5,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WD")].ngcount));
            modeldata->setData(modeldata->index(5,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WP")].ngcount));
            modeldata->setData(modeldata->index(5,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("Ra")].ngcount));
            modeldata->setData(modeldata->index(5,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CCT")].ngcount));
            modeldata->setData(modeldata->index(5,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_x")].ngcount));
            modeldata->setData(modeldata->index(5,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_y")].ngcount));
            modeldata->setData(modeldata->index(5,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("SDCM")].ngcount));
            modeldata->setData(modeldata->index(5,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("R9")].ngcount));
            //NG比例
            modeldata->setData(modeldata->index(6,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VF")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("VFL")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IR")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("IV")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WD")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("WP")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("Ra")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CCT")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_x")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("CIE_y")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("SDCM")].ngpercent,'f',2));
            modeldata->setData(modeldata->index(6,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatasumpkg[itag][i][lstTestItemName.indexOf("R9")].ngpercent,'f',2));
        }
        //3.显示测试流水数据，从第10行开始，
        for (int k=modeldata->rowCount();k>9;k--) { //整体向下移动，此方法比insertrow结合removerow的效率要高很多，不会导致界面卡顿
            for (int m=0;m<modeldata->columnCount();m++) {
                modeldata->setData(modeldata->index(k,m),modeldata->data(modeldata->index(k-1,m)));
            }
        }   //第9行总是显示最新的数据
        //qDebug()<<unitpublic::lsttestdatapkg[itag][0].testdataid;

        modeldata->setData(modeldata->index(9,0),QString::number(unitpublic::lsttestdatapkg[itag][0].testdataid));  //该LED测试总信息都在晶1数据存储
        modeldata->setData(modeldata->index(9,1),QString::number(unitpublic::lsttestdatapkg[itag][0].binid)); //BIN号
        modeldata->setData(modeldata->index(9,2),unitpublic::lsttestdatapkg[itag][0].pol);
        int testresult = 0;
        if (unitpublic::lsttestdatapkg[itag][0].testresult){
            modeldata->setData(modeldata->index(9,3),"OK");
            testresult = 1;
        }else{
            modeldata->setData(modeldata->index(9,3),"NG");
        }

        for (int i=0;i<iledcount;i++) {//lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
            modeldata->setData(modeldata->index(9,4+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].VF,'f',3));
            modeldata->setData(modeldata->index(9,5+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].VFL,'f',3));
            modeldata->setData(modeldata->index(9,6+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].IR,'f',3));
            modeldata->setData(modeldata->index(9,7+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].IV,'f',2));
            modeldata->setData(modeldata->index(9,8+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].WD,'f',1));
            modeldata->setData(modeldata->index(9,9+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].WP,'f',1));
            modeldata->setData(modeldata->index(9,10+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].Ra,'f',1));
            modeldata->setData(modeldata->index(9,11+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].CCT,'f',0));
            modeldata->setData(modeldata->index(9,12+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].CIE_x,'f',4));
            modeldata->setData(modeldata->index(9,13+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].CIE_y,'f',4));
            modeldata->setData(modeldata->index(9,14+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].SDCM,'f',0));
            modeldata->setData(modeldata->index(9,15+i*TESTITEM_COUNT),QString::number(unitpublic::lsttestdatapkg[itag][i].R9,'f',1));

        }
        //保存测试结果到mysql数据库
        QStringList lstsql;
        lstsql.clear();
        QString sdelete = QString("delete from testdata where dtime<=DATE_SUB(NOW(),INTERVAL 15 MINUTE) and station_id=%1").arg(itag);       //先删除15分钟以上的历史数据，转移到bak数据库
        lstsql.append(sdelete); //注意，这里的delete语句在线程中执行时，可能会导致跨线程死锁问题，导致“线程执行mysql语句失败！[MySQL][ODBC 8.0(a) Driver][mysqld-5.7.17-log]Deadlock found when trying to get lock; try restarting transaction QODBC3: Unable to execute statement”
                                //解决方案是给testdata表增加索引即可，刚好为了适配后面的校准页面中查询最近15分钟内的数据，所以把索引建在dtime字段上
        QString s1 = "insert into testdata (project_file,station_id,bin_id,";
                s1 = s1 + "VF1,VFL1,IR1,IV1,WD1,WP1,Ra1,CCT1,CIE_x1,CIE_y1,SDCM1,R91,";
                s1 = s1 + "VF2,VFL2,IR2,IV2,WD2,WP2,Ra2,CCT2,CIE_x2,CIE_y2,SDCM2,R92,";
                s1 = s1 + "VF3,VFL3,IR3,IV3,WD3,WP3,Ra3,CCT3,CIE_x3,CIE_y3,SDCM3,R93,testresult)";
        QString ssql = QString("%1 values ('%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,%36,%37,%38,%39,%40,%41)")
                        .arg(s1)    //insert into
                        .arg(unitpublic::gscurprofile)                      //工程文件
                        .arg(itag)                                          //测试工位
                        .arg(unitpublic::lsttestdatapkg[itag][0].binid)     //BIN号
                .arg(unitpublic::lsttestdatapkg[itag][0].VF)
                .arg(unitpublic::lsttestdatapkg[itag][0].VFL)
                .arg(unitpublic::lsttestdatapkg[itag][0].IR)
                .arg(unitpublic::lsttestdatapkg[itag][0].IV)
                .arg(unitpublic::lsttestdatapkg[itag][0].WD)
                .arg(unitpublic::lsttestdatapkg[itag][0].WP)
                .arg(unitpublic::lsttestdatapkg[itag][0].Ra)
                .arg(unitpublic::lsttestdatapkg[itag][0].CCT)
                .arg(unitpublic::lsttestdatapkg[itag][0].CIE_x)
                .arg(unitpublic::lsttestdatapkg[itag][0].CIE_y)
                .arg(unitpublic::lsttestdatapkg[itag][0].SDCM)
                .arg(unitpublic::lsttestdatapkg[itag][0].R9)
                .arg(unitpublic::lsttestdatapkg[itag][1].VF)
                .arg(unitpublic::lsttestdatapkg[itag][1].VFL)
                .arg(unitpublic::lsttestdatapkg[itag][1].IR)
                .arg(unitpublic::lsttestdatapkg[itag][1].IV)
                .arg(unitpublic::lsttestdatapkg[itag][1].WD)
                .arg(unitpublic::lsttestdatapkg[itag][1].WP)
                .arg(unitpublic::lsttestdatapkg[itag][1].Ra)
                .arg(unitpublic::lsttestdatapkg[itag][1].CCT)
                .arg(unitpublic::lsttestdatapkg[itag][1].CIE_x)
                .arg(unitpublic::lsttestdatapkg[itag][1].CIE_y)
                .arg(unitpublic::lsttestdatapkg[itag][1].SDCM)
                .arg(unitpublic::lsttestdatapkg[itag][1].R9)
                .arg(unitpublic::lsttestdatapkg[itag][2].VF)
                .arg(unitpublic::lsttestdatapkg[itag][2].VFL)
                .arg(unitpublic::lsttestdatapkg[itag][2].IR)
                .arg(unitpublic::lsttestdatapkg[itag][2].IV)
                .arg(unitpublic::lsttestdatapkg[itag][2].WD)
                .arg(unitpublic::lsttestdatapkg[itag][2].WP)
                .arg(unitpublic::lsttestdatapkg[itag][2].Ra)
                .arg(unitpublic::lsttestdatapkg[itag][2].CCT)
                .arg(unitpublic::lsttestdatapkg[itag][2].CIE_x)
                .arg(unitpublic::lsttestdatapkg[itag][2].CIE_y)
                .arg(unitpublic::lsttestdatapkg[itag][2].SDCM)
                .arg(unitpublic::lsttestdatapkg[itag][2].R9)
                .arg(testresult);                                   //测试结果
        lstsql.append(ssql);        //插入testdata
        ssql.replace("testdata","testdata_bak");
        lstsql.append(ssql);        //插入历史备份表，所有数据都保存在bak表中

        mysqlThread *mysqlt = new mysqlThread(itag,&lstsql);  //线程中执行数据库操作
        connect(mysqlt,SIGNAL(finished()),mysqlt,SLOT(deleteLater()));  //线程执行完毕后自动释放内存
        mysqlt->start();    //mysql数据处理耗时大概20-30ms时间不等，且需要通过字段 dtime 建索引，加快删除、插入速度
                    //而30ms左右的时间是可以跟LED光色电的测试过程以及机构运动平行处理的，提高UPH值

        //4.显示工位统计信息
        modeltj->setItem(1,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].sumcount)));
        modeltj->setItem(2,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].valcount)));
        modeltj->setItem(3,3,new QStandardItem(QString::number(unitpublic::lststationsumpkg[itag].uph,'f',2)));
        //5.显示各BIN统计数据

        for (int i=0;i<256;i++) {
            modelbin->setData(modelbin->index(i,0),QString::number(i+1));        //BIN号
            modelbin->setData(modelbin->index(i,1),QString::number(unitpublic::lststationsumpkg[itag].bincount[i]));        //该BIN计数
            modelbin->setData(modelbin->index(i,2),QString::number(unitpublic::lststationsumpkg[itag].binpercent[i],'f',2));    //该BIN占比
        }
        modelbin->sort(1,Qt::DescendingOrder);   //按数量倒序排序
    }
}

//槽函数，测试复位，点击“测试复位”时，清空测试流水表、初始化统计信息
void Frmtestdata::mtestreset(int iindex)
{
    if(iindex == itag){
        for (int i=0;i<maxrowcount;i++) {  //最多显示800行数据，为了保证桌面显示刷新效率，避免过多数据导致测试效率低
            for (int k=0;k<modeldata->columnCount();k++) {
                modeldata->setData(modeldata->index(9+i,k),""); //清空流水数据
            }
        }
        for (int k=2;k<7;k++) {
            for (int i=0;i<iledcount;i++){
                    //清空各测试项统计数据
                modeldata->setData(modeldata->index(k,4+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,5+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,6+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,7+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,8+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,9+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,10+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,11+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,12+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,13+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,14+i*TESTITEM_COUNT),"");
                modeldata->setData(modeldata->index(k,15+i*TESTITEM_COUNT),"");
            }
        }
        for (int iledindex=0;iledindex<LED_COUNT;iledindex++) {     //各测试项统计数据初始化
            for(int iitemindex=0;iitemindex<TESTITEM_COUNT;iitemindex++){
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].avgdata = 0;
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].maxdata = 0;
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].mindata = 99999999;
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].ngcount = 0;
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].sumdata = 0;
                unitpublic::lsttestdatasumpkg[itag][iledindex][iitemindex].ngpercent = 0;
            }
        }
        //清除各工位统计数据
        unitpublic::lststationsumpkg[itag].uph = 0;
        unitpublic::lststationsumpkg[itag].sumcount = 0;    //累计产量
        unitpublic::lststationsumpkg[itag].valcount = 0;    //有效产量
        modeltj->setData(modeltj->index(1,3),"0");      //该工位统计数据初始化
        modeltj->setData(modeltj->index(2,3),"0");
        modeltj->setData(modeltj->index(3,3),"0");
        //清空各BIN计数
        for (int i=0;i<256;i++) {
            modelbin->setData(modelbin->index(i,0),QString::number(i+1));        //BIN号
            modelbin->setData(modelbin->index(i,1),"0");        //该BIN计数
            unitpublic::lststationsumpkg[itag].bincount[i] = 0;
            modelbin->setData(modelbin->index(i,2),"0.00");    //该BIN占比
            unitpublic::lststationsumpkg[itag].binpercent[i] = 0;
        }

    }
}

//mysql数据处理线程
mysqlThread::mysqlThread(int iindex, QStringList *sql, QObject * parent)
{
    itag = iindex;
    lstsql.clear();
    for(int i=0;i<sql->count();i++)
        lstsql.append(sql->at(i));
}

mysqlThread::~mysqlThread()
{

}

void mysqlThread::run()
{
    //1.数据库先建普通索引，两个字段：dtime,station_id
    //2.采用事物处理，避免多线程利用同一个连接池处理事物，包含主线程在内建立5个连接池，各自使用自己的连接池
    //3.线程执行完mysql数据处理后，自动结束并释放内存
    QSqlQuery mysql(unitpublic::dblstmysql[itag]);
    unitpublic::dblstmysql[itag].transaction();  //开始事务
    for (int i=0;i<lstsql.count();i++) {
        if(!mysql.exec(lstsql.at(i)))      //1.先删除testdata实时测试结果30分钟以前的历史数据；2.将测试结果插入testdata数据表；3.测试流水数据插入MySQL，testdata_bak表
          unitpublic::gpwritelog("线程执行mysql语句失败！"+mysql.lastError().text());
    }                                   //目的是为了保证校准页面导入实测值的效率，当数据量非常大时会影响查询速度
    unitpublic::dblstmysql[itag].commit();   //提交事务
}

//接收线程信号，返回IO板卡状态
void Frmtestdata::mp32status(int iindex,int istatus)
{
    if(itag == iindex){
    if(istatus==1){
        modeltj->setData(modeltj->index(1,5),"打开成功！");
        modeltj->item(1,5)->setData(QColor(255, 255, 255), Qt::BackgroundRole);
    }else{
        modeltj->setData(modeltj->index(1,5),"打开失败！");
        modeltj->item(1,5)->setData(QColor(255, 0, 0), Qt::BackgroundRole);
    }
    }
}

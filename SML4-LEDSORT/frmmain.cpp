#include "frmmain.h"
#include "ui_frmmain.h"
#include <QMessageBox>
#include "QDesktopWidget"
#include "unitpublic.h"
#include <qpixmapcache.h>
#include <qtimer.h>
#include "fmoptstatus.h"
#include <qtoolbar.h>
#include <windows.h>
#include <QCloseEvent>
#include "frmcie1931.h"
#include "unitprofile.h"
#include "frmedtkey.h"
#include "regmanage.h"
#include "frmabout.h"
#include "qsqlquery.h"
#include "qsqlerror.h"

extern "C"    //因为是C版的dll文件，在C++中引入其头文件要加extern "C" {},注意
{
    #include "semielectricitydll.h" //电源dll
}
extern "C"
{
    #include "semispectrumerdll.h"  //光谱仪dll
}

FrmCIE1931* frmmain::frmcie1931_1 = NULL;       //把窗口定义为全局变量，方便在窗体释放时讲指针清空，在FrmCIE1931的析构函数中完成
FrmCIE1931* frmmain::frmcie1931_2 = NULL;
FrmCIE1931* frmmain::frmcie1931_3 = NULL;
FrmCIE1931* frmmain::frmcie1931_4 = NULL;

FrmSpecCurve* frmmain::frmspec_1 = NULL;    //同上
FrmSpecCurve* frmmain::frmspec_2 = NULL;    //同上
FrmSpecCurve* frmmain::frmspec_3 = NULL;    //同上
FrmSpecCurve* frmmain::frmspec_4 = NULL;    //同上

frmmain::frmmain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::frmmain)
{
    ui->setupUi(this);
    unitpublic::gsCurPath = QCoreApplication::applicationDirPath();       //获取当前程序所在路径
    unitpublic::readsyspara(unitpublic::gsCurPath+"/ledsort.cfg");      //读系统配置文件

    if(unitpublic::stenable[ST_INDEX_1])
    {ui->btnz1->setVisible(true);}else{ui->btnz1->setVisible(false);};  //配置是否启用各测试工位，不启用则不显示该工站
    if(unitpublic::stenable[ST_INDEX_2])
    {ui->btnz2->setVisible(true);}else{ui->btnz2->setVisible(false);};
    if(unitpublic::stenable[ST_INDEX_3])
    {ui->btnz3->setVisible(true);}else{ui->btnz3->setVisible(false);};
    if(unitpublic::stenable[ST_INDEX_4])
    {ui->btnz4->setVisible(true);}else{ui->btnz4->setVisible(false);};

    QFileInfo fileInfo(unitpublic::gscurprofile);
    if(!fileInfo.isFile()){
        QMessageBox::information(NULL,"提示","工程文件不存在，请检查配置文件是否正确！\n\r"+unitpublic::gscurprofile);
        QApplication *app;
        app->exit(0);
        this->close();
    }

    unitprofile::readprofile(unitpublic::gscurprofile); //读工程文件

    this->setWindowFlags(Qt::FramelessWindowHint);  //隐藏标题栏，即无边框，注意“Qt”大小写，否则编译不通过，在窗体设计界面：鼠标点击左上角右键可以选择“移除状态栏”“移除标题栏”，实现无边框
    this->setWindowState(Qt::WindowMaximized);      //默认最大化
    MainwindowsDispInit();      //初始化主窗口显示布局
//    TestdataWindowDispInit();   //测试结果数据列表显示初始化

    filezipTimer = new QTimer();    //定义一个时钟
    filezipTimer->setInterval(1000);	//1s，事件触发间隔时间
    connect(filezipTimer, SIGNAL(timeout()), this, SLOT(onUpdateTime()));   //连接信号槽
    filezipTimer->start();  //时钟开启

    if(unitpublic::gsuser=="admin"){    //管理员登录
        ui->btnledset->setEnabled(true);
        ui->btnbinset->setEnabled(true);
        ui->btnverify->setEnabled(true);
        ui->btnsystemset->setEnabled(true);
    }else
    if(unitpublic::gsuser=="engineer"){    //工程师登录
        ui->btnledset->setEnabled(false);
        ui->btnbinset->setEnabled(true);    //可设置分级参数
        ui->btnverify->setEnabled(true);    //可设置校准参数
        ui->btnsystemset->setEnabled(false);

    }else{
        ui->btnledset->setEnabled(false);
        ui->btnbinset->setEnabled(false);
        ui->btnverify->setEnabled(true);    //只可设置校准参数
        ui->btnsystemset->setEnabled(false);
    }
    testthreadinit();       //线程初始化
    QSqlQuery mysql(unitpublic::dbmysql);
    if(!mysql.exec("delete from testdata")){     //清空临时数据表，testdata只保存最近15分钟的数据，程序启动时，默认先清空
        unitpublic::gpwritelog("程序启动初始化，清空testdata临时表数据失败"+mysql.lastError().text());
    }

    Regmanage *regm = new Regmanage(this);
    QString s1 = regm->getCpuId() + regm->getDiskNum();     //CPU序号+硬盘序号
    unitpublic::getsoftsn(s1);
    unitpublic::softisreg(unitpublic::gsregcode);    //判断软件是否注册


}

//屏幕布局显示初始化
void frmmain::MainwindowsDispInit()
{
    qint32 idw = QApplication::desktop()->width();  //获取屏幕宽度
    qint32 idh = QApplication::desktop()->availableGeometry().height(); //桌面有效区域的高度，即去掉了系统“任务栏高度”

    QToolBar *tbtop = addToolBar(tr("4工位总菜单栏"));
    tbtop->setMovable(false);
    tbtop->setStyleSheet("background-color: rgb(224, 255, 255);");  //设置工具栏背景色
    tbtop->setMinimumSize(0,80);        //上方菜单工具栏
    tbtop->setGeometry(0,0,idw,80);
    this->addToolBarBreak();        //换行，保证2个工具栏处于上下两行
    QToolBar *tbleft = addToolBar(tr("单工位分菜单栏"));
    tbleft->setMovable(false);
    tbleft->setStyleSheet("background-color: rgb(255, 255, 255);");  //设置工具栏背景色
    tbleft->setMinimumSize(0,60);
    tbleft->setGeometry(0,0,idw,60);

    ui->btnall->setMinimumSize(80,70);      //设置按钮
    tbtop->addWidget(ui->btnall);       //全部开始、暂停
    ui->btnz1->setMinimumSize(80,70);
    tbtop->addWidget(ui->btnz1);        //1号工位
    ui->btnz2->setMinimumSize(80,70);
    tbtop->addWidget(ui->btnz2);        //2号工位
    ui->btnz3->setMinimumSize(80,70);
    tbtop->addWidget(ui->btnz3);        //3号工位
    ui->btnz4->setMinimumSize(80,70);
    tbtop->addWidget(ui->btnz4);        //4号工位
    ui->lbcount1->setMinimumSize(100,16);   //1号工位测试计数
    tbtop->addWidget(ui->lbcount1);
    ui->lbcount2->setMinimumSize(100,16);   //2号工位测试计数
    tbtop->addWidget(ui->lbcount2);
    ui->lbcount3->setMinimumSize(100,16);   //3号工位测试计数
    tbtop->addWidget(ui->lbcount3);
    ui->lbcount4->setMinimumSize(100,16);   //4号工位测试计数
    tbtop->addWidget(ui->lbcount4);
    ui->lbcount1->setText("");  //暂时先隐藏，每个区的测试数据显示页面有该工位的总数量
    ui->lbcount2->setText("");
    ui->lbcount3->setText("");
    ui->lbcount4->setText("");
    //初始化企业logo图片
    ui->lblogo->setGeometry((idw-210)/2,4,210,72);  //lblogo空间尺寸大小210,72
    QPixmapCache::clear();
    QImage imageset;
    imageset.load(":/new/prefix1/res/pic/logo.jpg");
    ui->lblogo->setMinimumSize(240,70);
    ui->lblogo->setPixmap(QPixmap::fromImage(imageset));   //如不进行Qlabel与图片的大小调整及适配，直接执行这条语句即可
    tbtop->addWidget(ui->lblogo);
    ui->lbproject->setMinimumSize(450,16);  //当前工程名，大小可调整
    ui->lbproject->setText(""); //setText("当前工程名！");
    tbtop->addWidget(ui->lbproject);
    ui->btnuser->setMinimumSize(80,70); //切换用户
    tbtop->addWidget(ui->btnuser);
    ui->btnabout->setMinimumSize(80,70);    //关于、帮助
    tbtop->addWidget(ui->btnabout);
    ui->btnclose->setMinimumSize(80,70);    //退出系统
    tbtop->addWidget(ui->btnclose);

    //设置右边菜单工具栏
    tbleft->addWidget(ui->btnauto);         //自动测试
    tbleft->addWidget(ui->btnstep);         //单步测试
    //tbleft->addWidget(ui->btncontinue);     //连续测试，连续测试跟自动运行是一样的功能
    tbleft->addWidget(ui->btnreset);        //复位清空
    tbleft->addSeparator();                 //分隔线
    tbleft->addSeparator();
    tbleft->addWidget(ui->btnsedu);         //显示色品图
    tbleft->addWidget(ui->btnquxian);       //显示能量曲线
    tbleft->addSeparator();
    tbleft->addSeparator();
    tbleft->addWidget(ui->btntestdisp);     //自动测试页面
    tbleft->addWidget(ui->btnledset);      //产品设置
    tbleft->addWidget(ui->btnbinset);       //分级设置
    tbleft->addWidget(ui->btnverify);       //参数校准
    tbleft->addWidget(ui->btnsystemset);     //系统设置
    tbleft->addSeparator();
    tbleft->addSeparator();
//    tbleft->addWidget(ui->btnnew);      //新建，暂时不用
    tbleft->addWidget(ui->btnopen);     //打开
    tbleft->addWidget(ui->btnsave);     //保存
    tbleft->addWidget(ui->btnsaveas);    //另存
//    tbleft->addWidget(ui->btnreback);    //恢复
    tbleft->addSeparator();
    tbleft->addSeparator();
    ui->cbmachine->setChecked(true);    //默认联机测试
    tbleft->addWidget(ui->cbmachine);   //是否连接测试运行

    //初始化底部状态栏
    ui->stbar->setMinimumSize(0,30);
    ui->lbuser->setMinimumWidth(200);   //当前登录用户
    ui->lbuser->setText("当前登录用户："+unitpublic::gsuser);
    ui->stbar->addWidget(ui->lbuser);           //运行状态提示

    fmrunstatus = new FmOptStatus("工位运行状态：");
    fmrunstatus->show();
    fmoptstatus = new FmOptStatus("光谱连接状态：");     //光谱仪连接状态
    fmoptstatus->show();
    fmdcstatus = new FmOptStatus("电源连接状态：");     //测试机连接状态
    fmdcstatus->show();
    ui->stbar->addWidget(fmrunstatus,1);
    ui->stbar->addWidget(fmoptstatus,1);
    ui->stbar->addWidget(fmdcstatus,1);
    ui->stbar->addPermanentWidget(ui->lbdtime,0);   //时钟显示


    qint32 i1=tbtop->geometry().height();
    qint32 i2=ui->stbar->geometry().height();
    qint32 i3=tbleft->geometry().height();
    ui->wdclient->setGeometry(1,1,idw,idh-i1-i2-i3-1); //设置子窗口显示位置，每个工作站的 主显示界面
    //注意，之前是用QFrame，结果发现在子窗口中的按钮或下来输入框，鼠标带你上去在有些区域内点击没反应，替换成QWidget容器就好了
    //所以按钮不建议放在QFrame中
    frmtestdata_1 = new Frmtestdata(ST_INDEX_1,ui->wdclient);   //工位1，测试数据显示页面
    frmtestdata_2 = new Frmtestdata(ST_INDEX_2,ui->wdclient);   //工位2
    frmtestdata_3 = new Frmtestdata(ST_INDEX_3,ui->wdclient);   //工位3
    frmtestdata_4 = new Frmtestdata(ST_INDEX_4,ui->wdclient);   //工位4
    connect(this,SIGNAL(testreset(int)),frmtestdata_1,SLOT(mtestreset(int)));
    connect(this,SIGNAL(testreset(int)),frmtestdata_2,SLOT(mtestreset(int)));
    connect(this,SIGNAL(testreset(int)),frmtestdata_3,SLOT(mtestreset(int)));
    connect(this,SIGNAL(testreset(int)),frmtestdata_4,SLOT(mtestreset(int)));
    frmbaseset_1 = new FrmBaseSet(ST_INDEX_1,ui->wdclient);   //工位1，基本设置窗口显示页面
    frmbaseset_2 = new FrmBaseSet(ST_INDEX_2,ui->wdclient);   //工位2
    frmbaseset_3 = new FrmBaseSet(ST_INDEX_3,ui->wdclient);   //工位3
    frmbaseset_4 = new FrmBaseSet(ST_INDEX_4,ui->wdclient);   //工位4
    connect(this,SIGNAL(savebaseset(int)),frmbaseset_1,SLOT(savebaseset(int)));
    connect(this,SIGNAL(savebaseset(int)),frmbaseset_2,SLOT(savebaseset(int)));
    connect(this,SIGNAL(savebaseset(int)),frmbaseset_3,SLOT(savebaseset(int)));
    connect(this,SIGNAL(savebaseset(int)),frmbaseset_4,SLOT(savebaseset(int)));

    connect(frmbaseset_1,SIGNAL(updatetestdata(int)),frmtestdata_1,SLOT(mupdatetestdata(int)));  //基本参数修改后，刷新重置主测试页面
    connect(frmbaseset_2,SIGNAL(updatetestdata(int)),frmtestdata_2,SLOT(mupdatetestdata(int)));
    connect(frmbaseset_3,SIGNAL(updatetestdata(int)),frmtestdata_3,SLOT(mupdatetestdata(int)));
    connect(frmbaseset_4,SIGNAL(updatetestdata(int)),frmtestdata_4,SLOT(mupdatetestdata(int)));

    frmbinset_1 = new FrmBinSet(ST_INDEX_1,ui->wdclient);    //工位1，分BIN设置窗口
    frmbinset_2 = new FrmBinSet(ST_INDEX_2,ui->wdclient);
    frmbinset_3 = new FrmBinSet(ST_INDEX_3,ui->wdclient);
    frmbinset_4 = new FrmBinSet(ST_INDEX_4,ui->wdclient);
    connect(this,SIGNAL(savebinset(int)),frmbinset_1,SLOT(savebinset(int)));
    connect(this,SIGNAL(savebinset(int)),frmbinset_2,SLOT(savebinset(int)));
    connect(this,SIGNAL(savebinset(int)),frmbinset_3,SLOT(savebinset(int)));
    connect(this,SIGNAL(savebinset(int)),frmbinset_4,SLOT(savebinset(int)));

    connect(frmbaseset_1,SIGNAL(updatebinpara(int)),frmbinset_1,SLOT(mupdatebinpara(int))); //基本参数修改后，通知分级参数设置页面刷新页面
    connect(frmbaseset_2,SIGNAL(updatebinpara(int)),frmbinset_2,SLOT(mupdatebinpara(int)));
    connect(frmbaseset_3,SIGNAL(updatebinpara(int)),frmbinset_3,SLOT(mupdatebinpara(int)));
    connect(frmbaseset_4,SIGNAL(updatebinpara(int)),frmbinset_4,SLOT(mupdatebinpara(int)));

    frmverify_1 = new Frmverify(ST_INDEX_1,ui->wdclient);   //工位1，校准页面
    frmverify_2 = new Frmverify(ST_INDEX_2,ui->wdclient);
    frmverify_3 = new Frmverify(ST_INDEX_3,ui->wdclient);
    frmverify_4 = new Frmverify(ST_INDEX_4,ui->wdclient);
    connect(this,SIGNAL(savevfyset(int)),frmverify_1,SLOT(msavevfyset(int)));
    connect(this,SIGNAL(savevfyset(int)),frmverify_2,SLOT(msavevfyset(int)));
    connect(this,SIGNAL(savevfyset(int)),frmverify_3,SLOT(msavevfyset(int)));
    connect(this,SIGNAL(savevfyset(int)),frmverify_4,SLOT(msavevfyset(int)));

    connect(frmbaseset_1,SIGNAL(updatevfypara(int)),frmverify_1,SLOT(mupdatevfypara(int)));  //基本参数修改保存后，通知校准设置刷新页面
    connect(frmbaseset_2,SIGNAL(updatevfypara(int)),frmverify_2,SLOT(mupdatevfypara(int)));
    connect(frmbaseset_3,SIGNAL(updatevfypara(int)),frmverify_3,SLOT(mupdatevfypara(int)));
    connect(frmbaseset_4,SIGNAL(updatevfypara(int)),frmverify_4,SLOT(mupdatevfypara(int)));

    frmsystemset_1 = new Frmsystemset(ST_INDEX_1,ui->wdclient); //工位1，系统设置
    frmsystemset_2 = new Frmsystemset(ST_INDEX_2,ui->wdclient);
    frmsystemset_3 = new Frmsystemset(ST_INDEX_3,ui->wdclient);
    frmsystemset_4 = new Frmsystemset(ST_INDEX_4,ui->wdclient);
    connect(this,SIGNAL(savesysset(int)),frmsystemset_1,SLOT(msavesysset(int)));
    connect(this,SIGNAL(savesysset(int)),frmsystemset_2,SLOT(msavesysset(int)));
    connect(this,SIGNAL(savesysset(int)),frmsystemset_3,SLOT(msavesysset(int)));
    connect(this,SIGNAL(savesysset(int)),frmsystemset_4,SLOT(msavesysset(int)));

    FrmClientChange();
}

frmmain::~frmmain()
{
    delete ui;
}

//时钟事件，每1秒触发一次
void frmmain::onUpdateTime()
{
    ui->lbdtime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); //实时显示当前系统时间
    for (int i=0;i<ST_COUNT;i++) {
        if(!unitpublic::stenable[i]) continue;
        if(!unitpublic::mthdsuspended[i]){   // 运行时计秒
            unitpublic::iruntime[i] ++; //运行中
            fmrunstatus->setConStatus(i,true);
        }else{
            fmrunstatus->setConStatus(i,false); //程序启动后，默认线程都是挂起暂停运行状态
        }
    }
}

void frmmain::on_btnclose_clicked()
{
    if (QMessageBox::information(this,tr("提示"),tr("确认退出系统吗 ?"),tr("是"), tr("否"), 0,1)==0)
                             //QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
    {
        QApplication *app;
        app->exit(0);
//        this->close();
    }

}

void frmmain::closeEvent( QCloseEvent * event )
{   //点击窗口x按钮时触发
    switch( QMessageBox::information( this, tr("提示"), tr("确认退出系统吗?"), tr("是"), tr("否"), 0, 1 ) )
   {
     case 0:
          event->accept();
          break;
     case 1:
     default:
         event->ignore();
         break;
   }
}

//显示区页面切换
void frmmain::FrmClientChange()
{
    frmbaseset_1->hide();frmbaseset_2->hide();frmbaseset_3->hide();frmbaseset_4->hide();        //基本设置
    frmtestdata_1->hide();frmtestdata_2->hide();frmtestdata_3->hide();frmtestdata_4->hide();    //自动测试
    frmbinset_1->hide();frmbinset_2->hide();frmbinset_3->hide();frmbinset_4->hide();            //分级设置
    frmverify_1->hide();frmverify_2->hide();frmverify_3->hide();frmverify_4->hide();            //校准设置
    frmsystemset_1->hide();frmsystemset_2->hide();frmsystemset_3->hide();frmsystemset_4->hide();//系统设置
    ui->btnsave->setEnabled(false);
    switch (unitpublic::gicurindex) {
    case ST_INDEX_1:{   //工位1
        switch (unitpublic::gicurfun[0]) {   //取1号工位当前显示页面
        case FUN_TESTDATA:{ //测试数据页面
            frmtestdata_1->show();
            break;
        }
        case FUN_BASESET:{ //基本设置页面
            frmbaseset_1->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_BINSET:{   //分BIN设置页面
            frmbinset_1->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_VERIFY:{   //校准页面
            frmverify_1->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_SYSTEM:{   //系统设置
            frmsystemset_1->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        }
        break;
    }
    case ST_INDEX_2:{   //工位2
        switch (unitpublic::gicurfun[1]) {
        case FUN_TESTDATA:{ //测试数据页面
            frmtestdata_2->show();
            break;
        }
        case FUN_BASESET:{ //基本设置页面
            frmbaseset_2->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_BINSET:{   //分BIN设置页面
            frmbinset_2->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_VERIFY:{
            frmverify_2->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_SYSTEM:{
            frmsystemset_2->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        }
        break;
    }
    case ST_INDEX_3:{   //工位3
        switch (unitpublic::gicurfun[2]) {
        case FUN_TESTDATA:{ //测试数据页面
            frmtestdata_3->show();
            break;
        }
        case FUN_BASESET:{ //基本设置页面
            frmbaseset_3->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_BINSET:{   //分BIN设置页面
            frmbinset_3->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_VERIFY:{
            frmverify_3->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_SYSTEM:{
            frmsystemset_3->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        }
        break;
    }
    case ST_INDEX_4:{   //工位4
        switch (unitpublic::gicurfun[3]) {
        case FUN_TESTDATA:{ //测试数据页面
            frmtestdata_4->show();
            break;
        }
        case FUN_BASESET:{ //基本设置页面
            frmbaseset_4->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_BINSET:{   //分BIN设置页面
            frmbinset_4->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_VERIFY:{
            frmverify_4->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        case FUN_SYSTEM:{
            frmsystemset_4->show();
            ui->btnsave->setEnabled(true);
            break;
        }
        }
        break;
    }
    }
}

void frmmain::on_btnz1_clicked()
{   //工位1
    ui->btnz1->setStyleSheet("image: url(:/new/prefix1/res/pic/1-1.png);");
    ui->btnz2->setStyleSheet("image: url(:/new/prefix1/res/pic/2.png);");
    ui->btnz3->setStyleSheet("image: url(:/new/prefix1/res/pic/3.png);");
    ui->btnz4->setStyleSheet("image: url(:/new/prefix1/res/pic/4.png);");
    unitpublic::gicurindex = ST_INDEX_1;
    FrmClientChange();
    if(unitpublic::mthdsuspended[ST_INDEX_1])
        setbtnenable(true);
    else
        setbtnenable(false);
}

void frmmain::on_btnz2_clicked()
{   //工位2
    ui->btnz1->setStyleSheet("image: url(:/new/prefix1/res/pic/1.png);");
    ui->btnz2->setStyleSheet("image: url(:/new/prefix1/res/pic/2-1.png);");
    ui->btnz3->setStyleSheet("image: url(:/new/prefix1/res/pic/3.png);");
    ui->btnz4->setStyleSheet("image: url(:/new/prefix1/res/pic/4.png);");
    unitpublic::gicurindex = ST_INDEX_2;
    FrmClientChange();
    if(unitpublic::mthdsuspended[ST_INDEX_2])
        setbtnenable(true);
    else
        setbtnenable(false);
}

void frmmain::on_btnz3_clicked()
{   //工位3
    ui->btnz1->setStyleSheet("image: url(:/new/prefix1/res/pic/1.png);");
    ui->btnz2->setStyleSheet("image: url(:/new/prefix1/res/pic/2.png);");
    ui->btnz3->setStyleSheet("image: url(:/new/prefix1/res/pic/3-1.png);");
    ui->btnz4->setStyleSheet("image: url(:/new/prefix1/res/pic/4.png);");
    unitpublic::gicurindex = ST_INDEX_3;
    FrmClientChange();
    if(unitpublic::mthdsuspended[ST_INDEX_3])
        setbtnenable(true);
    else
        setbtnenable(false);
}

void frmmain::on_btnz4_clicked()
{   //工位4
    ui->btnz1->setStyleSheet("image: url(:/new/prefix1/res/pic/1.png);");
    ui->btnz2->setStyleSheet("image: url(:/new/prefix1/res/pic/2.png);");
    ui->btnz3->setStyleSheet("image: url(:/new/prefix1/res/pic/3.png);");
    ui->btnz4->setStyleSheet("image: url(:/new/prefix1/res/pic/4-1.png);");
    unitpublic::gicurindex = ST_INDEX_4;
    FrmClientChange();
    if(unitpublic::mthdsuspended[ST_INDEX_4])
        setbtnenable(true);
    else
        setbtnenable(false);
}

void frmmain::on_btnledset_clicked()
{
    unitpublic::gicurfun[unitpublic::gicurindex] = FUN_BASESET;   //保存当前工位显示的页面
    FrmClientChange();
}

void frmmain::on_btntestdisp_clicked()
{
    unitpublic::gicurfun[unitpublic::gicurindex] = FUN_TESTDATA;  //保存当前工位显示的页面
    FrmClientChange();
}

void frmmain::on_btnsedu_clicked()
{   //显示色度

    switch (unitpublic::gicurindex) {
    case ST_INDEX_1:{
        if(!frmcie1931_1)   //判断窗口是否已经创建
        {
            frmcie1931_1 = new FrmCIE1931(unitpublic::gicurindex,this); //Widgets 类窗口
            frmcie1931_1->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_1])
                connect(tsort1,SIGNAL(specxy(int)),frmcie1931_1,SLOT(mspecxy(int)));  //打靶,接收线程信号并打靶
            frmcie1931_1->setWindowFlags(frmcie1931_1->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmcie1931_1->show();   //已经创建，即窗口指针有分配内容地址，则直接显示
        frmcie1931_1->activateWindow(); //当前激活窗口，即让窗体显示到前面来
        break;
    }
    case ST_INDEX_2:{
        if(!frmcie1931_2)
        {
            frmcie1931_2 = new FrmCIE1931(unitpublic::gicurindex,this); //Widgets 类窗口
            frmcie1931_2->setAttribute(Qt::WA_DeleteOnClose,0);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_2])
                connect(tsort2,SIGNAL(specxy(int)),frmcie1931_2,SLOT(mspecxy(int)));  //打靶
            frmcie1931_2->setWindowFlags(frmcie1931_2->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmcie1931_2->show();
        frmcie1931_2->activateWindow();
        break;
    }
    case ST_INDEX_3:{
        if(!frmcie1931_3)
        {
            frmcie1931_3 = new FrmCIE1931(unitpublic::gicurindex,this); //Widgets 类窗口
            frmcie1931_3->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_3])
                connect(tsort3,SIGNAL(specxy(int)),frmcie1931_3,SLOT(mspecxy(int)));  //打靶
            frmcie1931_3->setWindowFlags(frmcie1931_3->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmcie1931_3->show();
        frmcie1931_3->activateWindow();
        break;
    }
    case ST_INDEX_4:{
        if(!frmcie1931_4)
        {
            frmcie1931_4 = new FrmCIE1931(unitpublic::gicurindex,this); //Widgets 类窗口
            frmcie1931_4->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_4])
                connect(tsort4,SIGNAL(specxy(int)),frmcie1931_4,SLOT(mspecxy(int)));  //打靶
            frmcie1931_4->setWindowFlags(frmcie1931_4->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmcie1931_4->show();
        frmcie1931_4->activateWindow();
        break;
    }

    }
}

void frmmain::on_btnstep_clicked()
{   //单步测试
    unitpublic::testcmd[unitpublic::gicurindex] = CMD_TEST_STEP;        //测试命令置标志位即可，在线程中处理单步测试
}

void frmmain::on_btnquxian_clicked()
{   //显示光谱能量分布曲线
    switch (unitpublic::gicurindex) {
    case ST_INDEX_1:{
        if(!frmspec_1)   //判断窗口是否已经创建
        {
            frmspec_1 = new FrmSpecCurve(unitpublic::gicurindex,this); //Widgets 类窗口
            frmspec_1->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_1])
                connect(tsort1,SIGNAL(speccurve(int)),frmspec_1,SLOT(mspeccurve(int)));  //画光谱曲线
            frmspec_1->setWindowFlags(frmspec_1->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmspec_1->show();   //已经创建，即窗口指针有分配内容地址，则直接显示
        frmspec_1->activateWindow(); //当前激活窗口，即让窗体显示到前面来
        break;
    }
    case ST_INDEX_2:{
        if(!frmspec_2)
        {
            frmspec_2 = new FrmSpecCurve(unitpublic::gicurindex,this); //Widgets 类窗口
            frmspec_2->setAttribute(Qt::WA_DeleteOnClose,0);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_2])
                connect(tsort2,SIGNAL(speccurve(int)),frmspec_2,SLOT(mspeccurve(int)));  //画光谱曲线
            frmspec_2->setWindowFlags(frmspec_2->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmspec_2->show();
        frmspec_2->activateWindow();
        break;
    }
    case ST_INDEX_3:{
        if(!frmspec_3)
        {
            frmspec_3 = new FrmSpecCurve(unitpublic::gicurindex,this); //Widgets 类窗口
            frmspec_3->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_3])
                connect(tsort3,SIGNAL(speccurve(int)),frmspec_3,SLOT(mspeccurve(int)));  //画光谱曲线
            frmspec_3->setWindowFlags(frmspec_3->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmspec_3->show();
        frmspec_3->activateWindow();
        break;
    }
    case ST_INDEX_4:{
        if(!frmspec_4)
        {
            frmspec_4 = new FrmSpecCurve(unitpublic::gicurindex,this); //Widgets 类窗口
            frmspec_4->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
            if(unitpublic::mthdstarted[ST_INDEX_4])
                connect(tsort4,SIGNAL(speccurve(int)),frmspec_4,SLOT(mspeccurve(int)));  //画光谱曲线
            frmspec_4->setWindowFlags(frmspec_4->windowFlags() | Qt::Dialog);   //加上dialog可保证窗口显示在最上面，但不影响其他进程
        }
        frmspec_4->show();
        frmspec_4->activateWindow();
        break;
    }

    }

}

void frmmain::on_btnbinset_clicked()
{
    unitpublic::gicurfun[unitpublic::gicurindex] = FUN_BINSET;   //保存当前工位显示的页面
    FrmClientChange();
}

void frmmain::on_btnsave_clicked()
{   //保存文件
    if(unitpublic::giregstauts!=1){
        QMessageBox::information(NULL,"提示","软件未注册！");       //软件未注册则不允许使用保存设置功能
        return;
    }
    if(QMessageBox::question(NULL,"保存文件","确认保存当前测试工位的全部参数设置吗？参数保存才可后生效！\n\r注意：保存修改后参数将不可恢复！",QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        switch (unitpublic::gicurindex) {
        case ST_INDEX_1:{   //测试工位1
            switch (unitpublic::gicurfun[ST_INDEX_1]) {
            case FUN_BASESET:{      //基本参数设置
                emit savebaseset(ST_INDEX_1);

                break;
                }
            case FUN_BINSET:{      //分级参数设置
                emit savebinset(ST_INDEX_1);
                break;
                }
            case FUN_VERIFY:{       //校准设置
                emit savevfyset(ST_INDEX_1);
                break;
            }
            case FUN_SYSTEM:{       //系统设置
                emit savesysset(ST_INDEX_1);
                break;
            }
            }
            break;
        }
        case ST_INDEX_2:{   //测试工位2
            switch (unitpublic::gicurfun[ST_INDEX_2]) {
            case FUN_BASESET:{      //基本参数设置
                emit savebaseset(ST_INDEX_2);
                break;
                }
            case FUN_BINSET:{      //分级参数设置
                emit savebinset(ST_INDEX_2);
                break;
                }
            case FUN_VERIFY:{       //校准设置
                emit savevfyset(ST_INDEX_2);
                break;
            }
            case FUN_SYSTEM:{       //系统设置
                emit savesysset(ST_INDEX_2);
                break;
            }
            }
            break;
        }
        case ST_INDEX_3:{
            switch (unitpublic::gicurfun[ST_INDEX_3]) {
            case FUN_BASESET:{      //基本参数设置
                emit savebaseset(ST_INDEX_3);
                break;
                }
            case FUN_BINSET:{      //分级参数设置
                emit savebinset(ST_INDEX_3);
                break;
                }
            case FUN_VERIFY:{       //校准设置
                emit savevfyset(ST_INDEX_3);
                break;
            }
            case FUN_SYSTEM:{       //系统设置
                emit savesysset(ST_INDEX_3);
                break;
            }
            }
            break;
        }
        case ST_INDEX_4:{
            switch (unitpublic::gicurfun[ST_INDEX_4]) {
            case FUN_BASESET:{      //基本参数设置
                emit savebaseset(ST_INDEX_4);

                break;
                }
            case FUN_BINSET:{      //分级参数设置
                emit savebinset(ST_INDEX_4);
                break;
                }
            case FUN_VERIFY:{       //校准设置
                emit savevfyset(ST_INDEX_4);
                break;
            }
            case FUN_SYSTEM:{       //系统设置
                emit savesysset(ST_INDEX_4);
                break;
            }
            }
            break;
        }
        }
    }
}

void frmmain::on_btnall_clicked()
{   //全部开始测试
    if(!ballstart){ //全部开始
        if(unitpublic::stenable[ST_INDEX_1]){
            unitpublic::mthdsuspended[ST_INDEX_1] = false;      //线程挂起标志=false，即全部恢复自动运行测试
        }
        if(unitpublic::stenable[ST_INDEX_2]){
            unitpublic::mthdsuspended[ST_INDEX_2] = false;
        }
        if(unitpublic::stenable[ST_INDEX_3]){
            unitpublic::mthdsuspended[ST_INDEX_3] = false;
        }
        if(unitpublic::stenable[ST_INDEX_4]){
            unitpublic::mthdsuspended[ST_INDEX_4] = false;
        }
        ballstart = true;
        ui->btnall->setText("全部暂停");
        setbtnenable(false);    //设置按钮状态及现实内容
    }else
    {       //全部暂停
        if(unitpublic::stenable[ST_INDEX_1]){
            unitpublic::mthdsuspended[ST_INDEX_1] = true;   //线程挂起
            unitpublic::iruntime[ST_INDEX_1] = 0;
        }
        if(unitpublic::stenable[ST_INDEX_2]){
            unitpublic::mthdsuspended[ST_INDEX_2] = true;   //线程挂起
            unitpublic::iruntime[ST_INDEX_2] = 0;
        }
        if(unitpublic::stenable[ST_INDEX_3]){
            unitpublic::mthdsuspended[ST_INDEX_3] = true;   //线程挂起
            unitpublic::iruntime[ST_INDEX_3] = 0;
        }
        if(unitpublic::stenable[ST_INDEX_4]){
            unitpublic::mthdsuspended[ST_INDEX_4] = true;   //线程挂起
            unitpublic::iruntime[ST_INDEX_4] = 0;
        }
        ballstart = false;
        ui->btnall->setText("全部开始");
        setbtnenable(true);    //设置按钮状态及现实内容
    }

}

//接收线程信号，返回电源状态
void frmmain::mdcstatus(int iindex,int istatus)
{
    if(istatus == 1){
        fmdcstatus->setConStatus(iindex,true);  //在线
    }else
    {
        fmdcstatus->setConStatus(iindex,false); //离线
    }
}

//接收线程信号，返回光谱仪状态
void frmmain::mspecstatus(int iindex,int istatus)
{
    if(istatus == 1){
        fmoptstatus->setConStatus(iindex,true);  //在线
    }else
    {
        fmoptstatus->setConStatus(iindex,false); //离线
    }
}


//设置线程运行或暂停时，相关按钮的状态
void frmmain::setbtnenable(bool suspended)
{
    if(suspended){  //线程挂起
        ui->btnauto->setText("自动运行");
        ui->btnauto->setIcon(QIcon(":/new/prefix1/res/pic/run.png"));
        ui->btnstep->setEnabled(true);
        ui->btnreset->setEnabled(true);
        ui->btnopen->setEnabled(true);
        ui->btnsave->setEnabled(true);
        ui->btnsaveas->setEnabled(true);
        ui->btnuser->setEnabled(true);
        ui->btnclose->setEnabled(true);
    }else{      //线程运行
        ui->btnauto->setText("暂停运行");
        ui->btnauto->setIcon(QIcon(":/new/prefix1/res/pic/stop.png"));
        ui->btnstep->setEnabled(false);
        ui->btnreset->setEnabled(false);
        ui->btnopen->setEnabled(false);
        ui->btnsave->setEnabled(false);
        ui->btnsaveas->setEnabled(false);
        ui->btnuser->setEnabled(false);
        ui->btnclose->setEnabled(false);
    }
}

void frmmain::on_btnauto_clicked()
{   //暂停运行
    switch (unitpublic::gicurindex) {
    case ST_INDEX_1:{   //工位1
        if(unitpublic::stenable[ST_INDEX_1]){   //工位是否启用
            if(unitpublic::mthdsuspended[ST_INDEX_1]){     //如果线程挂起，则恢复运行
                      //线程被挂起，则取消挂即可
                unitpublic::mthdsuspended[ST_INDEX_1] = false;   //线程恢复
                setbtnenable(false);
            }else{
                unitpublic::mthdsuspended[ST_INDEX_1] = true;   //如果线程运行中，则挂起
                unitpublic::iruntime[ST_INDEX_1] = 0;
                setbtnenable(true);
                }
            }
        break;
        }
    case ST_INDEX_2:{   //工位2
        if(unitpublic::stenable[ST_INDEX_2]){   //工位是否启用
            if(unitpublic::mthdsuspended[ST_INDEX_2]){     //如果线程挂起，则恢复运行
                      //线程被挂起，则取消挂即可
                unitpublic::mthdsuspended[ST_INDEX_2] = false;   //线程恢复
                setbtnenable(false);
         }else{
                unitpublic::mthdsuspended[ST_INDEX_2] = true;   //如果线程运行中，则挂起
                unitpublic::iruntime[ST_INDEX_2] = 0;
                setbtnenable(true);
                }
            }
        break;
        }
    case ST_INDEX_3:{   //工位3
        if(unitpublic::stenable[ST_INDEX_3]){   //工位是否启用
            if(unitpublic::mthdsuspended[ST_INDEX_3]){     //如果线程挂起，则恢复运行
                      //线程被挂起，则取消挂即可
                unitpublic::mthdsuspended[ST_INDEX_3] = false;   //线程恢复
                setbtnenable(false);
         }else{
                unitpublic::mthdsuspended[ST_INDEX_3] = true;   //如果线程运行中，则挂起
                unitpublic::iruntime[ST_INDEX_3] = 0;
                setbtnenable(true);
                }
            }
        break;
        }
    case ST_INDEX_4:{   //工位4
        if(unitpublic::stenable[ST_INDEX_4]){   //工位是否启用
            if(unitpublic::mthdsuspended[ST_INDEX_4]){     //如果线程挂起，则恢复运行
                      //线程被挂起，则取消挂即可
                unitpublic::mthdsuspended[ST_INDEX_4] = false;   //线程恢复
                setbtnenable(false);
         }else{
                unitpublic::mthdsuspended[ST_INDEX_4] = true;   //如果线程运行中，则挂起
                unitpublic::iruntime[ST_INDEX_4] = 0;
                setbtnenable(true);
                }
            }
        break;
        }
    }
}

//线程初始化，即程序启动时线程全部启动，并默认挂起状态
void frmmain::testthreadinit()
{
    if(unitpublic::stenable[ST_INDEX_1]){       //工位已启用
        tsort1 = new testSortThread(ST_INDEX_1,this);
        connect(tsort1,SIGNAL(dcstatus(int,int)),this,SLOT(mdcstatus(int,int)));  //处理电源状态
        connect(tsort1,SIGNAL(specstatus(int,int)),this,SLOT(mspecstatus(int,int)));  //处理光谱仪状态
        connect(tsort1,SIGNAL(teststatus(int,int)),frmtestdata_1,SLOT(mteststatus(int,int)));  //显示测试状态
        connect(tsort1,SIGNAL(testdata(int)),frmtestdata_1,SLOT(mtestdata(int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort1,SIGNAL(testtime(int,int)),frmtestdata_1,SLOT(mtesttime(int,int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort1,SIGNAL(p32status(int,int)),frmtestdata_1,SLOT(mp32status(int,int))); //处理IO板卡状态
        unitpublic::filedb2memdb(ST_INDEX_1);
        unitpublic::mthdstarted[ST_INDEX_1] = true;  //注意信号连接槽函数的最后一个参数，没有用默认值，避免线程内信号发送太快，导致槽函数处理不及时导致偶尔不响应的情况发生；
        unitpublic::mthdsuspended[ST_INDEX_1] = true;   //线程启动后默认挂起
        tsort1->start();
    }

    if(unitpublic::stenable[ST_INDEX_2]){       //工位已启用
        tsort2 = new testSortThread(ST_INDEX_2,this);
        connect(tsort2,SIGNAL(dcstatus(int,int)),this,SLOT(mdcstatus(int,int)));  //处理电源状态
        connect(tsort2,SIGNAL(specstatus(int,int)),this,SLOT(mspecstatus(int,int)));  //处理光谱仪状态
        connect(tsort2,SIGNAL(teststatus(int,int)),frmtestdata_2,SLOT(mteststatus(int,int)));  //显示测试状态
        connect(tsort2,SIGNAL(testdata(int)),frmtestdata_2,SLOT(mtestdata(int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort2,SIGNAL(testtime(int,int)),frmtestdata_2,SLOT(mtesttime(int,int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort2,SIGNAL(p32status(int,int)),frmtestdata_2,SLOT(mp32status(int,int))); //处理IO板卡状态
        unitpublic::filedb2memdb(ST_INDEX_2);
        unitpublic::mthdstarted[ST_INDEX_2] = true;  //注意信号连接槽函数的最后一个参数，没有用默认值，避免线程内信号发送太快，导致槽函数处理不及时导致偶尔不响应的情况发生；
        unitpublic::mthdsuspended[ST_INDEX_2] = true;   //线程启动后默认挂起
        tsort2->start();
    }

    if(unitpublic::stenable[ST_INDEX_3]){       //工位已启用
        tsort3 = new testSortThread(ST_INDEX_3,this);
        connect(tsort3,SIGNAL(dcstatus(int,int)),this,SLOT(mdcstatus(int,int)));  //处理电源状态
        connect(tsort3,SIGNAL(specstatus(int,int)),this,SLOT(mspecstatus(int,int)));  //处理光谱仪状态
        connect(tsort3,SIGNAL(teststatus(int,int)),frmtestdata_3,SLOT(mteststatus(int,int)));  //显示测试状态
        connect(tsort3,SIGNAL(testdata(int)),frmtestdata_3,SLOT(mtestdata(int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort3,SIGNAL(testtime(int,int)),frmtestdata_3,SLOT(mtesttime(int,int)),Qt::BlockingQueuedConnection);   //测试耗时显示
        connect(tsort3,SIGNAL(p32status(int,int)),frmtestdata_3,SLOT(mp32status(int,int))); //处理IO板卡状态
        unitpublic::filedb2memdb(ST_INDEX_3);
        unitpublic::mthdstarted[ST_INDEX_3] = true;  //注意信号连接槽函数的最后一个参数，没有用默认值，避免线程内信号发送太快，导致槽函数处理不及时导致偶尔不响应的情况发生；
        unitpublic::mthdsuspended[ST_INDEX_3] = true;   //线程启动后默认挂起
        tsort3->start();
    }

    if(unitpublic::stenable[ST_INDEX_4]){       //工位已启用
        tsort4 = new testSortThread(ST_INDEX_4,this);
        connect(tsort4,SIGNAL(dcstatus(int,int)),this,SLOT(mdcstatus(int,int)));  //处理电源状态
        connect(tsort4,SIGNAL(specstatus(int,int)),this,SLOT(mspecstatus(int,int)));  //处理光谱仪状态
        connect(tsort4,SIGNAL(teststatus(int,int)),frmtestdata_4,SLOT(mteststatus(int,int)));  //显示测试状态
        connect(tsort4,SIGNAL(testdata(int)),frmtestdata_4,SLOT(mtestdata(int)),Qt::BlockingQueuedConnection);   //处理测试结果显示
        connect(tsort4,SIGNAL(testtime(int,int)),frmtestdata_4,SLOT(mtesttime(int,int)),Qt::BlockingQueuedConnection);   //测试耗时显示
        connect(tsort4,SIGNAL(p32status(int,int)),frmtestdata_4,SLOT(mp32status(int,int))); //处理IO板卡状态
        unitpublic::filedb2memdb(ST_INDEX_4);
        unitpublic::mthdstarted[ST_INDEX_4] = true;  //注意信号连接槽函数的最后一个参数，没有用默认值，避免线程内信号发送太快，导致槽函数处理不及时导致偶尔不响应的情况发生；
        unitpublic::mthdsuspended[ST_INDEX_4] = true;   //线程启动后默认挂起
        tsort4->start();
    }
}

void frmmain::on_btnreset_clicked()
{   //测试复位，该操作主要是清空测试流水数据列表，以及初始化统计信息
    if(QMessageBox::question(NULL,"提示","该操作将清空流水数据列表并初始化测试统计信息，继续吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes){
        emit testreset(unitpublic::gicurindex); //发送当前工位测试复位信号,
    }
}

void frmmain::on_btnopen_clicked()
{   //打开工程文件
    QString fileName = QFileDialog::getOpenFileName(this,"打开工程文件",".","工程文件(*.db3)");
    if(fileName.isNull()) return;       //没有打开文件，则直接返回退出

    if(QMessageBox::question(NULL,"提示","该操作将重新启动程序，继续吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes){
        QSettings settings(unitpublic::gsCurPath+"/ledsort.cfg",QSettings::IniFormat); //
        settings.setValue("system/profile",fileName);   //修改配置文件，设置将要打开的工程文件名称
        //自己重启
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}

void frmmain::on_btnsaveas_clicked()
{   //另存文件
    QString fileName = QFileDialog::getSaveFileName(this,"另存工程文件",".","工程文件(*.db3)");
    if(fileName.isNull()) return;       //没有打开文件，则直接返回退出
    QFile fileTemp(unitpublic::gscurprofile);
    QFile::copy(unitpublic::gscurprofile,fileName);  //另存文件，注意此时只是将当前工程文件拷贝复制到目标文件，所以如果没有保存最新设置的话，另存文件也不会保存最新数据
    QMessageBox::information(NULL,"提示","文件另存成功！\r\n"+fileName);
}


void frmmain::on_btnabout_clicked()
{
    //修改密码，切换用户功能可以用关闭程序重新登录来代替，或者后续再增加
    frmcie1931_1->printxy(0.35,0.35);
     Frmabout  *frmabout = new Frmabout(this); //Widgets 类窗口
     frmabout->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
     frmabout->setModal(true);
     frmabout->show();
}

void frmmain::on_btnuser_clicked()
{   //修改密码，切换用户功能可以用关闭程序重新登录来代替，或者后续再增加
    Frmedtkey  *frmedtkey = new Frmedtkey(this); //Widgets 类窗口
    frmedtkey->setAttribute(Qt::WA_DeleteOnClose);  //必须加上这一句，可以保证子窗口关闭时释放资源，避免内存一直上涨
    frmedtkey->setModal(true);
    frmedtkey->show();
}

void frmmain::on_btnverify_clicked()
{   //校准参数
    unitpublic::gicurfun[unitpublic::gicurindex] = FUN_VERIFY;   //保存当前工位显示的页面
    FrmClientChange();

}

void frmmain::on_btnsystemset_clicked()
{   //系统设置
    unitpublic::gicurfun[unitpublic::gicurindex] = FUN_SYSTEM;   //保存当前工位显示的页面
    FrmClientChange();

}

void frmmain::on_cbmachine_clicked()
{
    if(ui->cbmachine->checkState()==Qt::Checked){
        unitpublic::bmachine[unitpublic::gicurindex] = true;    //联机测试
    }else{
        unitpublic::bmachine[unitpublic::gicurindex]=false; //脱机测试
    }
}

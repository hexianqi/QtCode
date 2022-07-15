#ifndef FRMMAIN_H
#define FRMMAIN_H
//主窗口
#include <QMainWindow>
#include "fmoptstatus.h"
#include "frmtestdata.h"
#include "frmbaseset.h"
#include "frmcie1931.h"
#include "frmspeccurve.h"
#include "frmbinset.h"
#include "testsortthread.h"
#include "frmverify.h"
#include "frmsystemset.h"

QT_BEGIN_NAMESPACE
namespace Ui { class frmmain; }
QT_END_NAMESPACE

class frmmain : public QMainWindow
{
    Q_OBJECT

public:
    frmmain(QWidget *parent = nullptr);
    ~frmmain();

private slots:
    void on_btnclose_clicked();
    void onUpdateTime();  //时钟信号槽响应的事件执行函数,即时钟触发事件具体执行的任务

    void on_btnz1_clicked();

    void on_btnz2_clicked();

    void on_btnz3_clicked();

    void on_btnz4_clicked();

    void on_btnledset_clicked();

    void on_btntestdisp_clicked();

    void on_btnsedu_clicked();

    void on_btnstep_clicked();

    void on_btnquxian_clicked();

    void on_btnbinset_clicked();

    void on_btnsave_clicked();

    void on_btnall_clicked();

    void mdcstatus(int iindex,int istatus); //iindex工位序号，设备状态istatus，连接正常为1，否则返回错误代码，线程中发送
    void mspecstatus(int iindex,int istatus); //iindex工位序号，光谱仪状态istatus，连接正常为1，否则返回错误代码，线程中发送


    void on_btnauto_clicked();

    void on_btnreset_clicked();

    void on_btnopen_clicked();

    void on_btnsaveas_clicked();


    void on_btnabout_clicked();

    void on_btnuser_clicked();

    void on_btnverify_clicked();

    void on_btnsystemset_clicked();

    void on_cbmachine_clicked();

signals:
    void savebaseset(int iindex);        //信号，保存基本设置参数
    void savebinset(int iindex);        //信号，保存分级设置参数
    void testreset(int iindex);         //信号，测试复位，发送信号给testdata单元，清空测试流水表、初始化统计信息
    void savevfyset(int iindex);        //信号，保存校准参数
    void savesysset(int iindex);        //信号，保存系统设置

private:
    Ui::frmmain *ui;
    QTimer* filezipTimer;
    void closeEvent( QCloseEvent * event );

public:
    FmOptStatus *fmoptstatus;   //光谱仪连接状态
    FmOptStatus *fmdcstatus;    //电源连接状态
    FmOptStatus *fmrunstatus;   //各工位运行状态，暂停、运行
    void MainwindowsDispInit();    //主窗口布局显示初始化

    Frmtestdata *frmtestdata_1;       //测试数据列表显示窗口，工位1
    Frmtestdata *frmtestdata_2;       //测试数据列表显示窗口，工位2
    Frmtestdata *frmtestdata_3;       //测试数据列表显示窗口，工位3
    Frmtestdata *frmtestdata_4;       //测试数据列表显示窗口，工位4
//    void TestdataWindowDispInit();  //测试数据显示初始化

    FrmBaseSet *frmbaseset_1; //基本设置窗口，工位1
    FrmBaseSet *frmbaseset_2; //基本设置窗口，工位2
    FrmBaseSet *frmbaseset_3; //基本设置窗口，工位3
    FrmBaseSet *frmbaseset_4; //基本设置窗口，工位4
//    void BasesetWindowDispInit();   //基本设置窗口初始化显示

    FrmBinSet* frmbinset_1; //分BIN设置窗口,工位1
    FrmBinSet* frmbinset_2;
    FrmBinSet* frmbinset_3;
    FrmBinSet* frmbinset_4;

    Frmverify* frmverify_1; //参数校准
    Frmverify* frmverify_2;
    Frmverify* frmverify_3;
    Frmverify* frmverify_4;

    Frmsystemset* frmsystemset_1;   //系统设置
    Frmsystemset* frmsystemset_2;
    Frmsystemset* frmsystemset_3;
    Frmsystemset* frmsystemset_4;

    void FrmClientChange();     //显示区页面切换，当点击工位序号或者点击右边功能按钮时，切换客户区显示的页面内容

    static FrmCIE1931* frmcie1931_1;   //色品图1
    static FrmCIE1931 *frmcie1931_2;
    static FrmCIE1931 *frmcie1931_3;
    static FrmCIE1931 *frmcie1931_4;

    static FrmSpecCurve* frmspec_1; //光谱能量曲线
    static FrmSpecCurve* frmspec_2;
    static FrmSpecCurve* frmspec_3;
    static FrmSpecCurve* frmspec_4;

    testSortThread* tsort1;     //对应4个测试工位
    testSortThread* tsort2;
    testSortThread* tsort3;
    testSortThread* tsort4;
    bool ballstart = false;     //全部开始标志

    void setbtnenable(bool suspended); //设置线程运行时，按钮是否可用的状态
    void testthreadinit();      //线程初始化，即程序启动时线程全部启动，并默认挂起状态
};

#endif // FRMMAIN_H

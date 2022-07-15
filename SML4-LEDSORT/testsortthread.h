//测试线程，负责与机台通信交互、采集光源及光谱仪数据，并对结果进行处理，告知机台BIN号，测试记录存入数据库保存
#ifndef TESTSORTTHREAD_H
#define TESTSORTTHREAD_H
#include <qthread.h>
#include "qsqldatabase.h"
#include "WENYU_PIO32P_DLL.h"

//定义线程类
class testSortThread: public QThread
{
    Q_OBJECT
public:
    testSortThread(int iindex,QObject * parent = 0);    //iindex，测试工位序号
    ~testSortThread();

signals:   //定义信号
    void dcstatus(int iindex,int istatus); //iindex工位序号，电源状态istatus，连接正常为1，否则返回错误代码
    void specstatus(int iindex,int istatus); //iindex工位序号，光谱仪状态istatus，连接正常为1，否则返回错误代码
    void p32status(int iindex,int istatus); //iindex工位序号，IO板卡状态istatus，连接正常为1，否则返回错误代码
    void teststatus(int iindex,int istatus);    //测试状态，测试中...，暂停测试!
    void testdata(int iindex);       //测试结果显示，先返回测试时间，做测试
    void testtime(int iindex,int itesttime);       //测试耗时
    void speccurve(int iindex);             //显示光谱曲线
    void specxy(int iindex);                //显示打靶图

protected:
    void run(); // 线程入口

private:

public:
    int itag;
    bool bdcopenflag;         //电源状态，true-已打开
    bool bspecopenflag;         //光谱仪状态，true-已打开
    bool bp32openflag;            //IO板卡状态，true-已打开
    WY_hDevice wyDeviceID;    //IO板卡句柄
    int dcinit();   //电源初始化
    int specinit(); //光谱仪初始化
    int pio32init();    //IO板卡初始化
    int dcspectest(int ichan);      //光色电测试，输入参数：ichan=电源通道
    int testdatasum(int ichan);    //各参数测试结果统计，等外bin则返回等外BIN号
    bool readsot();       //获取机台SOT信号
    bool sendeot(int binid,bool bcleareot);    //发送BIN号及EOT,bcleareot表示清除EOT信号
    bool testdatasum_1(int ichan,QString stestitemname,double dtestitemdata);  //各参数测试结果统计，等外bin则返回false
    int getbinnumber();
 //校准计算，传入参数：测试参数名称，VF/VFL。。。，
    //晶片序号，晶1、2.。。
    //val校准前数值
    //返回值，校准后数值
    double vfycalc(QString itemname,int ledindex,double val);
};
#endif // TESTSORTTHREAD_H

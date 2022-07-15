#ifndef FRMTESTDATA_H
#define FRMTESTDATA_H

#include <QWidget>
#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <qthread.h>

//测试流水数据及测试过程信息显示

namespace Ui {
class Frmtestdata;
}

class Frmtestdata : public QWidget
{
    Q_OBJECT

public:
    explicit Frmtestdata(qint8 iindex,QWidget *parent = nullptr);
    ~Frmtestdata();

private:
    Ui::Frmtestdata *ui;


public:
    qint8 itag;             //标签，对应测试工位序号
    int maxrowcount = 300;      //主界面可现实的历史流水表记录行数，影响到现实刷新效率、UPH
    void tvDispInit();      //数据列表显示初始化，定义列字段标题、列数量等
    int iledcount = 0;      //晶片序号，列表显示时使用
    QStandardItemModel *modeltj;        //定义为本地全局变量，避免在后续刷新数据时候重新定义影响效率，降低内存
    QStandardItemModel *modeldata;
    QStandardItemModel *modelbin;

private slots:
    void mteststatus(int iindex,int istatus);    //测试状态，测试中...，暂停测试!，线程中发出信号
    void mtestdata(int iindex);       //测试结果显示，先返回测试时间，做测试
    void mtesttime(int iindex,int itesttime);
    void mtestreset(int iindex);         //槽函数，测试复位，点击“测试服务”时，清空测试流水表、初始化统计信息
    void mupdatetestdata(int iindex);       //槽函数，保存基本参数设置后，刷新当前测试数据页面
    void mp32status(int iindex,int istatus);    //iindex工位序号，IO卡状态istatus，连接正常为1
};


//mysql数据库处理线程，删除、插入等操作
class mysqlThread: public QThread
{
    Q_OBJECT
public:
    mysqlThread(int iindex, QStringList *sql, QObject * parent = 0);    //iindex，测试工位序号
    ~mysqlThread();

    int itag;
    QStringList lstsql ;    //要执行的sql语句

protected:
    void run(); // 线程入口
};

#endif // FRMTESTDATA_H

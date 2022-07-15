#ifndef FRMBINSET_H
#define FRMBINSET_H
#include <qwidget.h>
#include "unitpublic.h"
//分BIN设置

struct Binsetpara{
    double minvalue;    //最小值
    double maxvalue;    //最大值
    QString xybinname;     //xy分级BIN名
    QString itemname;   //参数名称
};


#include <QWidget>
namespace Ui {
class FrmBinSet;
}

class FrmBinSet : public QWidget
{
    Q_OBJECT

public:
    explicit FrmBinSet(qint8 iindex,QWidget *parent = nullptr);
    ~FrmBinSet();

private:
    Ui::FrmBinSet *ui;
    int ibincount = 0;      //参与分级的参数数量
public:
    qint8 itag;   //标识，对应测试工位序号
    QList<BinXyPkg> lstbinxypkg;    //xy分级参数信息

    void BindispInit();    //初始化
    QList<QVector<Binsetpara>> getAllGroup(QList<QVector<Binsetpara>> val); // 分级参数，动态数组排列组合
    int getindexfrombinxypkg(QString name);     //通过name值获取该色区参数的ID号

    void readbinsetpara();      //从数据表 binset_para 中获取分级参数
    QString sfieldname = "";    //分级参数列表初始化时，把参与分级的参数名形成表字段并暂存在 sfieldname ，便于后续在 readbinsetpara 函数获取表binset_para 相关数据
private slots:
    void on_btnset_clicked();
    void on_btnclear_clicked();
    void on_btnin_clicked();
    void on_btnout_clicked();
    void savebinset(int iindex);        //槽函数，保存分级设置参数
    void mtvbinparadisp(int iindex);    //从临时分级参数设置窗口返回的消息，在当前页面显示临时分级参数的各种组合参数

    void on_tvbinset_entered(const QModelIndex &index);//鼠标悬停，显示提示信息

    void mupdatebinpara(int iindex);       //刷新参数，修改并保存基本参数后，需要重置分级参数
};

#endif // FRMBINSET_H

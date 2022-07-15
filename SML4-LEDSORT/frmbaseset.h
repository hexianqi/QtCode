#ifndef FRMBASESET_H
#define FRMBASESET_H

#include <QWidget>
#include <qtableview.h>

//基本设置，设置LED类型、测试项目及相关条件、条码标签等

namespace Ui {
class FrmBaseSet;
}

class FrmBaseSet : public QWidget
{
    Q_OBJECT

public:
    explicit FrmBaseSet(qint8 iindex,QWidget *parent = nullptr);
    ~FrmBaseSet();

private:
    Ui::FrmBaseSet *ui;
    void moveRow(QTableView *tableView, int currentRow, int toRow); //移动行数据

public:
    qint8 itag;   //标识，对应测试工位序号
    void tvDispInit(int led_index,QTableView* tvtestitem);      //数据列表显示初始化，定义列字段标题、列数量等

    void basesetdisp();          //基本设置参数初始化显示

private slots:

    void savebaseset(int iindex);        //槽函数，保存基本设置参数

signals:
        void updatebinpara(int iindex);     //信号，保存基本参数后通知分级设置页面刷新数据
        void updatevfypara(int iindex);     //信号，保存基本参数后通知校准参数页面刷新数据
        void updatetestdata(int iindex);     //信号，保存基本设置参数后通知主测试页面刷新数据

};

#endif // FRMBASESET_H

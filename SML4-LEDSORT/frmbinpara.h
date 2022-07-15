#ifndef FRMBINPARA_H
#define FRMBINPARA_H
//分级参数设置

#include <QDialog>
#include <qheaderview.h>
#include "unitpublic.h"

namespace Ui {
class FrmBinPara;
}

class FrmBinPara : public QDialog
{
    Q_OBJECT

public:
    explicit FrmBinPara(qint8 iindex,QWidget *parent = nullptr);
    ~FrmBinPara();

private slots:
    void MyHeadersectionClicked(int logicalIndex);
    void tvbinparadispxy(int irow,QList<BinXyPkg> binxypkg);    //XY分级窗口传回分级参数，可用来判断单元格R1等参数是否正确并提示坐标值
    void tvbinparadispvf(int irow,QList<BinVfPkg> binvfpkg);    //VF分级窗口传回分级参数

    void on_btnok_clicked();

    void on_btncancel_clicked();

private:
    Ui::FrmBinPara *ui;

public:
    qint8 itag;   //标识，对应测试工位序号
    QList<BinXyPkg> lstbinxypkg;
    void tvbinparaInit();   //参数编辑列表初始化
    void resizeEvent(QResizeEvent* size);
    //从单元格中获取分级参数，传入参数，ctext单元格字符串数据，返回minvalue和maxvalue
    //非法字符串，则函数返回false
    bool celltobinpara(QString ctext,double &minvalue,double &maxvalue);
    //非法xy分级参数，则返回false
    bool celltobinxypara(QString ctext,QPointF &xy0,QPointF &xy1,QPointF &xy2,QPointF &xy3);
    void readbinparatemp(); //读取分级参数临时表
    bool savebinparatemp(); //保存分级参数临时表

signals:
    void tvbinparadisp(int iindex);    //分级参数在上一级窗口显示
};

#endif // FRMBINPARA_H

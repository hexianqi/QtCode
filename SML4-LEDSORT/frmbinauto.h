#ifndef FRMBINAUTO_H
#define FRMBINAUTO_H

//VF/IV等自动分级设置

#include <QDialog>
#include "unitpublic.h"

namespace Ui {
class FrmBinAuto;
}

class FrmBinAuto : public QDialog
{
    Q_OBJECT

public:
    explicit FrmBinAuto(qint8 iindex,QString stp, QWidget *parent = nullptr);
    ~FrmBinAuto();

private:
    Ui::FrmBinAuto *ui;
public:
    qint8 itag;   //标识，对应测试工位序号
    int irow;   //上级菜单tableview行序号
    QString stype;  //分级参数类型，如VF1、IV1、VF2等
    int iledindex=0;
    QString sitemname="";   //分级参数名称

    void readbinaotutemp(); //读取自动分级临时表参数
    void savebinautotemp(); //保存自动分级临时表参数

private slots:
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();

signals:
    void tvbinparadispvf(int irow,QList<BinVfPkg> binvfpkg);    //VF等参数设置结果返回到上一级窗口界面显示
};

#endif // FRMBINAUTO_H

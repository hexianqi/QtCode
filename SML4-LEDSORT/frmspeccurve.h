#ifndef FRMSPECCURVE_H
#define FRMSPECCURVE_H



//光谱能量分布曲线
//需要安装QCharts，Qt安装时默认是没有选择的

#include <QDialog>
#include <QChartView>
#include <QtCharts>
#include "unitpublic.h"

namespace Ui {
class FrmSpecCurve;
}

class FrmSpecCurve : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSpecCurve(qint8 iindex,QWidget *parent = nullptr);
    ~FrmSpecCurve();

private:
    Ui::FrmSpecCurve *ui;

private slots:
    void mspeccurve(int iindex);             //显示光谱曲线


public:
    qint8 itag = 0;   //标识，对应测试工位序号
    bool isvisable = false;
   // QChartView* chartview;  //必须加上QtCharts头文件，且在pro中QT += charts，否则编译不通过
    QChart* m_chart;
    QSplineSeries *series1; //晶1，R
    QSplineSeries *series2; //晶2，G
    QSplineSeries *series3; //晶3，B

    void CurveInit();       //曲线图初始化_
    QVector<QPointF> MyPointf1;  // 绘制线对象所需要的数据,R
    QVector<QPointF> MyPointf2;  // 绘制线对象所需要的数据,G
    QVector<QPointF> MyPointf3;  // 绘制线对象所需要的数据,B
    void SpecDisp(SpecDataPkg specdata,bool bclear);        //显示光谱能量分布曲线图，传入光谱仪结构数据
};

#endif // FRMSPECCURVE_H

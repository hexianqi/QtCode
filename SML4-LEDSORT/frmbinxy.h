#ifndef FRMBINXY_H
#define FRMBINXY_H
//xy分级设置
#include <QDialog>
#include <qpainter.h>
#include <qlabel.h>
#include "unitpublic.h"

struct TCieXy{  //坐标系数据
    double xmin;        //X轴最小值
    double xmax;        //X轴最大值
    double ymin;        //Y轴最小值
    double ymax;        //Y轴最大值
    double ipx;         //X轴分辨率 = X轴宽度（xmax - xmin）/（XY_WIDTH）
    double ipy;         //Y轴分辨率 = Y轴宽度（ymax - ymin）/（XY_HEIGHT）
};

//4点坐标类
struct QPointF4{
    QPointF pt1;
    QPointF pt2;
    QPointF pt3;
    QPointF pt4;
};

class MyXyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyXyLabel(QWidget *parent = 0);

    //鼠标进入事件
    void enterEvent(QEvent *);

    //鼠标离开事件
    void leaveEvent(QEvent *);


    //鼠标按下事件
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *ev);


    //事件分发器
    bool event(QEvent *e);

signals:
    void AxisXY_Disp(int x,int y); //处理当前xy坐标值
    void AxisXY_Press(int x,int y); //处理当前xy坐标值的鼠标点击事件
    void AxisXY_DblClick(int x,int y);  //处理鼠标双击事件

public slots:
};

namespace Ui {
class FrmBinxy;
}

class FrmBinxy : public QDialog
{
    Q_OBJECT

public:
    explicit FrmBinxy(qint8 iindex,QString stp,QWidget *parent = nullptr);
    ~FrmBinxy();

private:
    Ui::FrmBinxy *ui;

    bool eventFilter(QObject *,QEvent *);

public:
    qint8 itag;   //标识，对应测试工位序号
    int irow;   //上一级窗口中tableview列表行序号
    QString stype;  //分级参数类型，如VF1、IV1、VF2等
    QPixmap imgcie;
    QPainter p;     //定义成本地全局变量，方便在QPaintEvent事件外画图
    void drawaxis_xy();     //画坐标系
    void drawaxis_xy4();    //画4点区域

    void xyzoom(int itype,double x,double y);   //坐标移动，itype，0=初始化，1=放大，2=缩小，3-选定区域放大,

    static int moldx;  //拖放前鼠标坐标,zhb 220627增加，支持鼠标拖放坐标
    static int moldy;

    int iledindex=0;

    bool readbinxytemp(); //读取自动分级临时表参数
    void savebinxytemp(); //保存自动分级临时表参数

    MyXyLabel* label;  //显示色品图

    void printxy(float x,float y);  //打靶，画十字线
    static int ixyindex;   //记录当前四边形的输入焦点，跟edt黄色值呼应，-1表示没有在输入编辑状态

    TCieXy pciexy;  //坐标系结构参数

    //计算两条直线的交叉点坐标
     QPointF line2point(QLineF l1,QLineF l2);
    //等分四边形区域
    //输入：QPointF4 point4：待等分的四边型区域4个点坐标
    //     ixf,iyf：X、Y方向上等分的数量
    //     QVector<QLineF> *lines：返回等分后的线条数组
    //     QList<QPointF4> *points4：返回等分后个小四边形的4点坐标列表数组
    //    return：返回等分后小四边形数量
    int gfDrawxy4(QPointF4 pf4,int ixf,int iyf,QVector<QLineF> *lines,QList<QPointF4> *pfs4);
    void tvbinxyInit();   //参数编辑列表初始化
    QPointF pointold[];     //存储上次点击的分区点坐标

private slots:

    void AxisXY_mDisp(int x,int y); //槽函数，接收MyLabel对象的信号，显示当前xy坐标值
    void on_toolButton_clicked();
    void AxisXY_mPress(int x,int y); //槽函数，处理鼠标在坐标系图上的点击事件
    void AxisXY_mDblClick(int x,int y); //槽函数，处理鼠标在坐标系图上的双击事件

    void on_btnfenji_clicked();
    void on_edtx0_textChanged(const QString &arg1);
    void on_edty0_textChanged(const QString &arg1);
    void on_edtx1_textChanged(const QString &arg1);
    void on_edty1_textChanged(const QString &arg1);
    void on_edtx2_textChanged(const QString &arg1);
    void on_edty2_textChanged(const QString &arg1);
    void on_edtx3_textChanged(const QString &arg1);
    void on_edty3_textChanged(const QString &arg1);
    void on_tvbinxy_clicked(const QModelIndex &index);

    void tvItemChanged();
    void on_cbdaba_clicked();
    void on_toolButton_5_clicked();

    void on_edtx0_cursorPositionChanged(int arg1, int arg2);

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

signals:
    void tvbinparadispxy(int irow,QList<BinXyPkg> binxypkg);
};

#endif // FRMBINXY_H

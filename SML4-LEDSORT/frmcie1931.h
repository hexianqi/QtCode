#ifndef FRMCIE1931_H
#define FRMCIE1931_H

//CIE1931色品图

#include <QWidget>
#include <qpainter.h>
#include <QResizeEvent>

#include "frmbinxy.h"
#include <qmenu.h>

const int CIE_WIDTH  = 1000;     //色品图像素大小，跟底图原始文件保持一致
const int CIE_HEIGHT = 1000;

#include <QLabel>

//黑体色温曲线坐标
const double temprou[67]={0.1801,0.1807,0.1813,0.1821,0.1829,0.1839,0.1849,0.1861,0.1874,0.1888,0.1903,0.1919,0.1936,0.1955,0.1975,0.1996,0.2018,0.2041,0.2064,0.2088,0.2114,0.2140,0.2166,0.2194,0.2222,0.2251,0.2280,0.2309,0.2339,0.2369,0.2400,0.2432,0.2462,0.2494,0.2526,0.2559,0.2590,0.2623,0.2659,0.2688,0.2721,0.2753,0.2786,0.2819,0.2852,0.2885,0.2918,0.2950,0.2983,0.3016,0.3050,0.3082,0.3114,0.3146,0.3179,0.3211,0.3243,0.3276,0.3307,0.3339,0.3371,0.3403,0.3433,0.3465,0.3496,0.3527,0.3556};
const double temprov[67]={0.2635,0.2659,0.2685,0.2712,0.2741,0.2771,0.2802,0.2834,0.2867,0.2899,0.2933,0.2965,0.2999,0.3030,0.3061,0.3092,0.3122,0.3158,0.3178,0.3205,0.3231,0.3255,0.3279,0.3302,0.3323,0.3344,0.3363,0.3381,0.3398,0.3415,0.3431,0.3445,0.3464,0.3471,0.3483,0.3495,0.3505,0.3515,0.3524,0.3532,0.3541,0.3547,0.3554,0.3560,0.3566,0.3571,0.3575,0.3580,0.3584,0.3587,0.3591,0.3593,0.3595,0.3597,0.3599,0.3602,0.3602,0.3603,0.3604,0.3604,0.3605,0.3605,0.3605,0.3605,0.3605,0.3604,0.3604};


class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);

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

    void paintEvent(QPaintEvent *event);

    bool m_isMousePress;
    QPoint m_beginPoint, m_endPoint;
    QPoint m_midPoint;
    QPainter m_painter;

signals:
    void AxisXY_Disp(int x,int y); //显示当前xy坐标值
    void AxisXY_Zoom(QPoint beginPoint, QPoint endPoint);
    void AxisXY_Menu(int x,int y);  //鼠标右键显示菜单

public slots:
};


namespace Ui {
class FrmCIE1931;
}

class FrmCIE1931 : public QWidget
{
    Q_OBJECT

public:
    explicit FrmCIE1931(qint8 iindex,QWidget *parent = nullptr);
    ~FrmCIE1931();

private:
    Ui::FrmCIE1931 *ui;

    bool disp_matitu   = true;         //是否显示色品图，马蹄图
    bool disp_heiti     = true;        //是否显示黑体曲线
    bool disp_tuoyuan   = false;        //是否显示椭圆
    bool disp_fenji     = true;         //是否显示分级区域

    int hisxy_maxcount = 100000;            //允许导入历史打靶坐标的最大数量，为了避免历史数据过多导致卡顿，可适当调整该参数
    QList<QPointF> lst_hisxy ;      //历史打靶坐标值，存在内存中，需要显示时从内存导入，窗体每次初始化时清空

    QMenu* m_menu;          //右键菜单
    QAction* actClear;      //坐标系初始化菜单
    QAction* actHeiti;      //是否显示色温黑体曲线菜单
    QAction* actTuoyuan;    //是否显示椭圆曲线菜单
    QAction* actMatitu;     //是否显示色品马蹄图（颜色区域）
    QAction* actFenji;      //是否显示分级区域

public:
    qint8 itag = 0;   //标识，对应测试工位序号
    bool isvisable = false;

    QPixmap imgcie;
    QPainter p;     //定义成本地全局变量，方便在QPaintEvent事件外画图

    MyLabel* label;  //显示色品图

    void printxy(float x,float y,bool his_xy=false);          //打把，画十字线，his_xy是否为历史打靶，如果是则不增加到lst_hisxy列表中
    void resizeEvent(QResizeEvent* size);
    void drawcie1931(bool hisxy);           //画色品图,hisxy是否导入历史xy打靶坐标

    TCieXy ciexy;   //坐标系参数
    QList<BinXyPkg> lstbinxypkg;    //xy分级参数信息
    void readbinsetpara();

private slots:

    void AxisXY_mDisp(int x,int y); //槽函数，接收MyLabel对象的信号，显示当前xy坐标值
    void mspecxy(int iindex);                //显示打靶图
    void AxisXY_mZoom(QPoint beginPoint, QPoint endPoint);
    void AxisXY_mMenu(int x,int y);  //鼠标右键显示菜单

    void slot_menu_clear();      //鼠标右键 - 初始化坐标系
    void slot_menu_heiti();     //鼠标右键 - 色温黑体曲线
    void slot_menu_tuoyuan();   //鼠标右键 - 色容差椭圆
    void slot_menu_matitu();    //鼠标右键 - 色品马蹄图
    void slot_menu_fenji();     //鼠标右键 - 分级区域
};

#endif // FRMCIE1931_H

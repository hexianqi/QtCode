#ifndef FRMCIE1931_H
#define FRMCIE1931_H

//CIE1931色品图

#include <QWidget>
#include <qpainter.h>
#include <QResizeEvent>

const int CIE_WIDTH  = 600;     //色品图显示区域大小
const int CIE_HEIGHT = 600;

#include <QLabel>

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
public:
    qint8 itag = 0;   //标识，对应测试工位序号
    bool isvisable = false;
    void paintEvent(QPaintEvent *event);    //绘图事件，暂时不用改方法画色品图（直接 return ）

    QPixmap imgcie;
    QPainter p;     //定义成本地全局变量，方便在QPaintEvent事件外画图
    void drawcie(QPainter* painter);    //画CIE色品图
    void drawaxis_xy();     //画坐标系

    MyLabel* label;  //显示色品图

    void printxy(float x,float y);  //打把，画十字线
    void resizeEvent(QResizeEvent* size);

private slots:

    void AxisXY_mDisp(int x,int y); //槽函数，接收MyLabel对象的信号，显示当前xy坐标值
    void mspecxy(int iindex);                //显示打靶图
    void AxisXY_mZoom(QPoint beginPoint, QPoint endPoint);

    void on_pushButton_clicked();
};

#endif // FRMCIE1931_H

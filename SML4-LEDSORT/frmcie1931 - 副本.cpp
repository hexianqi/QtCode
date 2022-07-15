#include "frmcie1931.h"
#include "ui_frmcie1931.h"
#include <qpainter.h>
#include "colormatchingfunctions.h"
#include "qmath.h"
#include "qdebug.h"
#include "frmmain.h"
#include "unitpublic.h"
#include "qdebug.h"

#include <QDebug>
#include <QMouseEvent>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
   // setMouseTracking(true);
}


//鼠标进入事件
void MyLabel::enterEvent(QEvent *)
{
//    qDebug() << "鼠标进入了";
}

//鼠标离开事件
void MyLabel::leaveEvent(QEvent *)
{
//     qDebug() << "鼠标离开了";
}


//鼠标按下事件
void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    //鼠标左键按下  打印信息
    if(ev->button() == Qt::LeftButton)
    {
        m_isMousePress = true;  //鼠标按下，
        m_beginPoint = ev->pos();//获取开始按下的点坐标
    }
}
//鼠标释放事件
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_endPoint = ev->pos(); //获取结束按下的点坐标
        m_isMousePress = false; //鼠标松开
     //   update();
        emit AxisXY_Zoom(m_beginPoint,m_endPoint);  //松开鼠标时，处理图形放大事件
    }

}
//鼠标移动事件
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
 //   if(ev->buttons() & Qt::LeftButton)
 //   {
 //       QString str =  QString("鼠标移动了 x =  %1  y = %2 " ).arg(ev->x()).arg(ev->y());
 //       qDebug() <<str;
  //  }
}


//事件分发器 :用途，分发事件
bool MyLabel::event(QEvent *e)
{

//    if( e->type() == QEvent::MouseButtonPress)
//    {
//        //如果是鼠标按下  拦截事件，不向下分发

//        QMouseEvent *ev = static_cast<QMouseEvent *>(e);

//        QString str =  QString("event中  鼠标按下了 x =  %1  y = %2 " ).arg(ev->x()).arg(ev->y());
//        qDebug() << str;

//        return true;
//    }

    if( e->type() == QEvent::MouseMove)
    {
        //如果是鼠标移动  拦截事件，不向下分发

        QMouseEvent *ev = static_cast<QMouseEvent *>(e);
        emit AxisXY_Disp(ev->x(),ev->y());      //显示xy坐标值

        m_midPoint=ev->pos();
        update();
        return true;
    }

    //其他事件  抛给父类去处理
    return QLabel::event(e);
}

void MyLabel::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);//先调用父类的paintEvent为了显示'背景'!!!
    QPainter m_painter(this);


    m_painter.setPen(QPen(Qt::red,2,Qt::DashLine));      //画笔颜色，宽度，虚线

    if (m_isMousePress)
    {
        m_painter.drawRect(QRect(m_beginPoint,m_midPoint));
    }
    else
    {   //不画终点
    //   m_painter.drawRect(QRect(m_beginPoint,m_endPoint));
    }


}

void FrmCIE1931::AxisXY_mDisp(int x,int y)
{   //在窗体的标题栏中显示当前鼠标对应xy坐标
    float fx = x*1.0 / this->width();
    float fy = 1- y*1.0/this->height();
    QString sx = QString::number(fx,'f',4);
    QString sy = QString::number(fy,'f',4);
    this->setWindowTitle(QString("打靶图 - %1#         XY:   %2,%3").arg(itag+1).arg(sx).arg(sy));
}

void FrmCIE1931::drawcie(QPainter* painter)
{    //从Paintevent函数中拷贝过来
    QImage imgcie;
    imgcie.load(":/new/prefix1/res/pic/CIE1931.jpg");
    painter->drawImage(QRect(0,0,label->geometry().width(),label->geometry().height()),imgcie,QRect(0,0,imgcie.width(),imgcie.height()));
    return;
    //painter->fillRect(0,0,ui->label->geometry().width(), ui->label->geometry().height(),Qt::white);      //背景色
    painter->setRenderHint(QPainter::Antialiasing);
    painter->scale(imgcie.width(), imgcie.height());   //显示区域，坐标系的问题,相当于把显示区域都变成1:1的坐标系
    //因为scale函数设置了放大系数，所以直接用这里的painter画图时，会出现看不见图形的缘故，主要是坐标被放大后导致

    QLinearGradient linearGradient;     //线性渐变色类
    QPointF writePoint(1.0 / 3, 1.0 - 1.0 / 3);  // 注意坐标系变化


    for (int i = 0; i < CIEDATANUM-1; i++)        //从360到830，为了保证色度图的标准程度，这里可以继续插值细分（比如每个波长数据之间再细分10组）
    {   //
        // 准备封闭三角形数据
        float x0 = ciedata1931[i][0];       //获取波长对应色度坐标,xy
        float y0 = ciedata1931[i][1];
        float z0 = ciedata1931[i][2];

        int next = i + 1;
        next = next < CIEDATANUM ? next : 0;    //注意此处的处理，如果循环条件是i < CIEDATANUM ，则会从830到360再填充一个大封闭三角形
                                                //所以，直接修改循环条件i < CIEDATANUM-1，即不绘制最后一个大三角形，而是通过后面的方法绘制马蹄形的下半部分
        float x1 = ciedata1931[next][0];    //下一个波长对应的色度坐标
        float y1 = ciedata1931[next][1];
        float z1 = ciedata1931[next][2];

        // 计算xy坐标对应的rgb数据
        int r0 = 0;
        int g0 = 0;
        int b0 = 0;
        ColorMatchingFunctions::xyz2rgb(r0, g0, b0, x0, y0, z0);    //起点颜色
        int r1 = 0;
        int g1 = 0;
        int b1 = 0;
        ColorMatchingFunctions::xyz2rgb(r1, g1, b1, x1, y1, z1);    //终点颜色
        float kk1 = (y1-y0) / (x1-x0);           //插值系数,k,b
        float bb1 = y0 - (y1-y0)*x0/(x1-x0);
        for (int n=0;n<3;n++) {             //细分3
            float x00 = x0+n*(x1-x0)/3;    //准备封闭三角形
            float y00 = kk1*x00+bb1;

            float x10 = x00 + (x1-x0)/3;   //插值
            float y10 = kk1*x10+bb1;

            QPointF point[] = {             //坐标值是浮点数，封闭三角形的三个坐标点
                writePoint,                 //白点
                QPointF(x00, 1.0 - y00),      //起点，上一个色度坐标
                QPointF(x10, 1.0 - y10)       //终点，下一个色度坐标
            };             //从这里可以看出，起始绘制的小三角形只覆盖了360-830的弧曲线部分，而白点到马蹄形下方的直线区域是没有绘制的，因为直线坐标数据没有
                            //需要通过线性y=kx+b计算出来后绘制，否则图形不标准，
                            //已知直线上的两个端点，ciedata1931[0]=0.17556023,0.00529384;ciedata1931[471]=0.73468996,0.26531004
            float p00 = (qSqrt((x10-x0)*(x10-x0)+(y10-y0)*(y10-y0)))/
                    (qSqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));       //格拉斯曼颜色混合定律
            int r00 = (1-p00)*r0+p00*r1;  //注意颜色插值方法,起点为360，终点为830，则P为当前点到起点的距离
            int g00 = (1-p00)*g0+p00*g1;
            int b00 = (1-p00)*b0+p00*b1;
            // 设置渐变填充的起始点和起始颜色
            linearGradient.setStart(writePoint);
            linearGradient.setFinalStop(QPointF(x00, 1.0 - y00));
            linearGradient.setColorAt(0.0, QColor(235, 235, 235));
            linearGradient.setColorAt(1.0, QColor(r00, g00, b00));

            // 绘制封闭三角形
            painter->setPen(QPen(QColor(r00, g00, b00, 0), 1));
            painter->setBrush(QBrush(linearGradient));
            painter->drawPolygon(point, 3);
        }

    }

    //绘制马蹄形下半部分区域（直线跟白点）
    float kbx1=ciedata1931[0][0];
    float kby1=ciedata1931[0][1];
    float kbz1=ciedata1931[0][2];
    float kbx2=ciedata1931[CIEDATANUM-1][0];
    float kby2=ciedata1931[CIEDATANUM-1][1];
    float kbz2=ciedata1931[CIEDATANUM-1][2];
    float k = (kby2-kby1) / (kbx2-kbx1);            //计算k
    float b = kby1 - (kby2-kby1)*kbx1/(kbx2-kbx1);  //计算b
    int r360 = 0;
    int g360 = 0;
    int b360 = 0;
    ColorMatchingFunctions::xyz2rgb(r360, g360, b360, ciedata1931[0][0], ciedata1931[0][1], ciedata1931[0][2]);
    int r830 = 0;
    int g830 = 0;
    int b830 = 0;
    ColorMatchingFunctions::xyz2rgb(r830, g830, b830, ciedata1931[CIEDATANUM-1][0], ciedata1931[CIEDATANUM-1][1], ciedata1931[CIEDATANUM-1][2]);

    int zcount = 300;    //差值数量，300个，密度越高，色度越标准，注意，细分越多，色彩越标准，线条感会好很多，但会影响刷新效率，所以找好平衡
    for (int m=0;m<zcount;m++) {
        float x0 = kbx1+m*(kbx2-kbx1)/zcount;    //准备封闭三角形
        float y0 = k*x0+b;
        //int wavelength1 = m*(830-360)/zcount;
        float z0 = ciedata1931[0][2];
        //float z0=kbz1+m*(kbz2-kbz1)/zcount; //xy线性插值ok，但z值怎么获取 ？？？

        float x1 = x0 + (kbx2-kbx1)/zcount;   //插值
        float y1 = k*x1+b;
        QPointF point[] = {             //坐标值是浮点数，封闭三角形的三个坐标点
            writePoint,                 //白点
            QPointF(x0, 1.0 - y0),      //起点，上一个色度坐标
            QPointF(x1, 1.0 - y1)       //终点，下一个色度坐标
        };
        float p = (qSqrt((x1-ciedata1931[0][0])*(x1-ciedata1931[0][0])+(y1-ciedata1931[0][1])*(y1-ciedata1931[0][1])))/
                (qSqrt((ciedata1931[CIEDATANUM-1][0]-ciedata1931[0][0])*(ciedata1931[CIEDATANUM-1][0]-ciedata1931[0][0])+(ciedata1931[CIEDATANUM-1][1]-ciedata1931[0][1])*(ciedata1931[CIEDATANUM-1][1]-ciedata1931[0][1])));
        int r = (1-p)*r360+p*r830;  //注意颜色插值方法,起点为360，终点为830，则P为当前点到起点的距离
        int g = (1-p)*g360+p*g830;
        int b = (1-p)*b360+p*b830;

        // 设置渐变填充的起始点和起始颜色
        linearGradient.setStart(writePoint);
        linearGradient.setFinalStop(QPointF(x0, 1.0 - y0));
        linearGradient.setColorAt(0.0, QColor(235, 235, 235));
        linearGradient.setColorAt(1.0, QColor(r, g, b));

        // 绘制封闭三角形
        painter->setPen(QPen(QColor(r, g, b, 0), 1));
        painter->setBrush(QBrush(linearGradient));
        painter->drawPolygon(point, 3);
    }
}

FrmCIE1931::FrmCIE1931(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmCIE1931)
{
    ui->setupUi(this);
    itag = iindex;
    isvisable = true;
    this->setWindowTitle(QString("打靶图 - %1#").arg(itag+1));

    this->setGeometry(400+iindex*40,200+iindex*40,this->width(),this->height());    //不同工位的色度图，顺序排列
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);

    label = new MyLabel(this);      //显示色品图
    label->setMouseTracking(true);  //注意，必须加上这一句，否则鼠标的QEvent::MouseMove事件必须在鼠标按下时移动才有效
    connect(label,SIGNAL(AxisXY_Disp(int,int)),this,SLOT(AxisXY_mDisp(int,int))); //注意函数名大小写也必须保持一致
    connect(label,SIGNAL(AxisXY_Zoom(QPoint,QPoint)),this,SLOT(AxisXY_mZoom(QPoint,QPoint))); //注意函数名大小写也必须保持一致
    //在窗口的resizeEvent事件中画CIE色品图


}

FrmCIE1931::~FrmCIE1931()
{
    delete ui;
    switch (itag) {         //析构函数中，将窗口实例变为空
    case ST_INDEX_1:{
        frmmain::frmcie1931_1 = NULL;
        break;
    }
    case ST_INDEX_2:{
        frmmain::frmcie1931_2 = NULL;
        break;
    }
    case ST_INDEX_3:{
        frmmain::frmcie1931_3 = NULL;
        break;
    }
    case ST_INDEX_4:{
        frmmain::frmcie1931_4 = NULL;
        break;
    }
    }
}


//https://blog.csdn.net/yxyx13120297/article/details/120693369
//https://blog.csdn.net/weixin_43194305/article/details/115468614
void FrmCIE1931::paintEvent(QPaintEvent *event)
{
    return; //暂时不用这个方法画色品图
    imgcie = QPixmap(this->width(),this->height());             //尺寸跟着窗口变化，填充整个窗口
    label->setGeometry(0,0,this->width(),this->height());
    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空
    p.begin(&imgcie);
    drawcie(&p);
    p.end();
    label->setPixmap(imgcie);
    drawaxis_xy();

    qDebug() << "repiant";


    //QPainter只能在paintEvent函数中使用
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::white);      //背景色
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(this->width(), this->height());   //显示区域
    QLinearGradient linearGradient;     //线性渐变色类
    QPointF writePoint(1.0 / 3, 1.0 - 1.0 / 3);  // 注意坐标系变化

    for (int i = 0; i < CIEDATANUM-1; i++)        //从360到830，为了保证色度图的标准程度，这里可以继续插值细分（比如每个波长数据之间再细分10组）
    {   //
        // 准备封闭三角形数据
        float x0 = ciedata1931[i][0];       //获取波长对应色度坐标,xy
        float y0 = ciedata1931[i][1];
        float z0 = ciedata1931[i][2];

        int next = i + 1;
        next = next < CIEDATANUM ? next : 0;    //注意此处的处理，如果循环条件是i < CIEDATANUM ，则会从830到360再填充一个大封闭三角形
                                                //所以，直接修改循环条件i < CIEDATANUM-1，即不绘制最后一个大三角形，而是通过后面的方法绘制马蹄形的下半部分
        float x1 = ciedata1931[next][0];    //下一个波长对应的色度坐标
        float y1 = ciedata1931[next][1];
        float z1 = ciedata1931[next][2];

/*
    //不带细分的处理
         QPointF point[] = {             //坐标值是浮点数，封闭三角形的三个坐标点
            writePoint,                 //白点
            QPointF(x0, 1.0 - y0),      //起点，上一个色度坐标
            QPointF(x1, 1.0 - y1)       //终点，下一个色度坐标
        };             //从这里可以看出，起始绘制的小三角形只覆盖了360-830的弧曲线部分，而白点到马蹄形下方的直线区域是没有绘制的，因为直线坐标数据没有
        int r = 0;
        int g = 0;
        int b = 0;
        ColorMatchingFunctions::xyz2rgb(r, g, b, x0, y0, z0);    //起点颜色
        // 设置渐变填充的起始点和起始颜色
        linearGradient.setStart(writePoint);
        linearGradient.setFinalStop(QPointF(x0, 1.0 - y0));
        linearGradient.setColorAt(0.0, QColor(235, 235, 235));
        linearGradient.setColorAt(1.0, QColor(r, g, b));

        // 绘制封闭三角形
        painter.setPen(QPen(QColor(r, g, b, 0), 1));
        painter.setBrush(QBrush(linearGradient));
        painter.drawPolygon(point, 3);
*/

        // 计算xy坐标对应的rgb数据
        int r0 = 0;
        int g0 = 0;
        int b0 = 0;
        ColorMatchingFunctions::xyz2rgb(r0, g0, b0, x0, y0, z0);    //起点颜色
        int r1 = 0;
        int g1 = 0;
        int b1 = 0;
        ColorMatchingFunctions::xyz2rgb(r1, g1, b1, x1, y1, z1);    //终点颜色
        float kk1 = (y1-y0) / (x1-x0);           //插值系数,k,b
        float bb1 = y0 - (y1-y0)*x0/(x1-x0);
        for (int n=0;n<3;n++) {    //细分3
            float x00 = x0+n*(x1-x0)/3;    //准备封闭三角形
            float y00 = kk1*x00+bb1;

            float x10 = x00 + (x1-x0)/3;   //插值
            float y10 = kk1*x10+bb1;

            QPointF point[] = {             //坐标值是浮点数，封闭三角形的三个坐标点
                writePoint,                 //白点
                QPointF(x00, 1.0 - y00),      //起点，上一个色度坐标
                QPointF(x10, 1.0 - y10)       //终点，下一个色度坐标
            };             //从这里可以看出，起始绘制的小三角形只覆盖了360-830的弧曲线部分，而白点到马蹄形下方的直线区域是没有绘制的，因为直线坐标数据没有
                            //需要通过线性y=kx+b计算出来后绘制，否则图形不标准，
                            //已知直线上的两个端点，ciedata1931[0]=0.17556023,0.00529384;ciedata1931[471]=0.73468996,0.26531004
            float p00 = (qSqrt((x10-x0)*(x10-x0)+(y10-y0)*(y10-y0)))/
                    (qSqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));       //格拉斯曼颜色混合定律
            int r00 = (1-p00)*r0+p00*r1;  //注意颜色插值方法,起点为360，终点为830，则P为当前点到起点的距离
            int g00 = (1-p00)*g0+p00*g1;
            int b00 = (1-p00)*b0+p00*b1;
            // 设置渐变填充的起始点和起始颜色
            linearGradient.setStart(writePoint);
            linearGradient.setFinalStop(QPointF(x00, 1.0 - y00));
            linearGradient.setColorAt(0.0, QColor(235, 235, 235));
            linearGradient.setColorAt(1.0, QColor(r00, g00, b00));

            // 绘制封闭三角形
            painter.setPen(QPen(QColor(r00, g00, b00, 0), 1));
            painter.setBrush(QBrush(linearGradient));
            painter.drawPolygon(point, 3);

            float p1 =writePoint.x()*this->width();
            float p2=writePoint.y()*this->height();
            float p3=x10*this->width();
            float p4=(1-y10)*this->height();
            painter.drawLine(p1,p2,p3,p4);
        }

    }
    return;
    //绘制马蹄形下半部分区域（直线跟白点）
    float kbx1=ciedata1931[0][0];
    float kby1=ciedata1931[0][1];
    float kbz1=ciedata1931[0][2];
    float kbx2=ciedata1931[CIEDATANUM-1][0];
    float kby2=ciedata1931[CIEDATANUM-1][1];
    float kbz2=ciedata1931[CIEDATANUM-1][2];
    float k = (kby2-kby1) / (kbx2-kbx1);            //计算k
    float b = kby1 - (kby2-kby1)*kbx1/(kbx2-kbx1);  //计算b
    int r360 = 0;
    int g360 = 0;
    int b360 = 0;
    ColorMatchingFunctions::xyz2rgb(r360, g360, b360, ciedata1931[0][0], ciedata1931[0][1], ciedata1931[0][2]);
    int r830 = 0;
    int g830 = 0;
    int b830 = 0;
    ColorMatchingFunctions::xyz2rgb(r830, g830, b830, ciedata1931[CIEDATANUM-1][0], ciedata1931[CIEDATANUM-1][1], ciedata1931[CIEDATANUM-1][2]);

    int zcount = 300;    //差值数量，300个，密度越高，色度越标准，注意，细分越多，色彩越标准，线条感会好很多，但会影响刷新效率，所以找好平衡
    for (int m=0;m<zcount;m++) {
        float x0 = kbx1+m*(kbx2-kbx1)/zcount;    //准备封闭三角形
        float y0 = k*x0+b;
        //int wavelength1 = m*(830-360)/zcount;
        float z0 = ciedata1931[0][2];
        //float z0=kbz1+m*(kbz2-kbz1)/zcount; //xy线性插值ok，但z值怎么获取 ？？？

        float x1 = x0 + (kbx2-kbx1)/zcount;   //插值
        float y1 = k*x1+b;
        QPointF point[] = {             //坐标值是浮点数，封闭三角形的三个坐标点
            writePoint,                 //白点
            QPointF(x0, 1.0 - y0),      //起点，上一个色度坐标
            QPointF(x1, 1.0 - y1)       //终点，下一个色度坐标
        };
        float p = (qSqrt((x1-ciedata1931[0][0])*(x1-ciedata1931[0][0])+(y1-ciedata1931[0][1])*(y1-ciedata1931[0][1])))/
                (qSqrt((ciedata1931[CIEDATANUM-1][0]-ciedata1931[0][0])*(ciedata1931[CIEDATANUM-1][0]-ciedata1931[0][0])+(ciedata1931[CIEDATANUM-1][1]-ciedata1931[0][1])*(ciedata1931[CIEDATANUM-1][1]-ciedata1931[0][1])));
        int r = (1-p)*r360+p*r830;  //注意颜色插值方法,起点为360，终点为830，则P为当前点到起点的距离
        int g = (1-p)*g360+p*g830;
        int b = (1-p)*b360+p*b830;

        qDebug()<<p<<r<<g<<b<<x1<<y1;
        // 设置渐变填充的起始点和起始颜色
        linearGradient.setStart(writePoint);
        linearGradient.setFinalStop(QPointF(x0, 1.0 - y0));
        linearGradient.setColorAt(0.0, QColor(235, 235, 235));
        linearGradient.setColorAt(1.0, QColor(r, g, b));

        // 绘制封闭三角形
        painter.setPen(QPen(QColor(r, g, b, 0), 1));
        painter.setBrush(QBrush(linearGradient));
        painter.drawPolygon(point, 3);
    }

 //   FrmCIE1931::paintEvent(event);    //不注释会导致死循环 ?不断触发事件
}

//画坐标系
void FrmCIE1931::drawaxis_xy()
{
    p.begin(&imgcie);
    p.setPen(QPen(Qt::darkGray,1));
    for (int i=0;i<10;i++) {
        p.drawLine(0,i*(this->height()/10.0),this->width(),i*(this->height()/10.0));
        p.drawLine(i*(this->width()/10.0),0,i*(this->width()/10.0),this->height());
    }
    p.drawText(2,this->height()-2,"0.0");   //原点，左下角
    p.drawText(2,12,"1.0");                 //Y轴，左上角
    p.drawText(this->width()-20,this->height()-2,"1.0");    //X轴，右小角
    p.end();
    label->setPixmap(imgcie);
}

//打把，画十字线
void FrmCIE1931::printxy(float x, float y)
{
    p.begin(&imgcie);
    p.setPen(QPen(Qt::black,1));
    p.setBrush(QBrush(Qt::black));
    float fx=x*this->width();
    float fy=(1-y)*this->height();
    p.drawLine(fx-3.0,fy,fx+3.0,fy);
    p.drawLine(fx,fy-3.0,fx,fy+3.0);
    p.end();
    label->setPixmap(imgcie);
}

//在窗口的resizeEvent事件中画CIE色品图
//色品图随尺寸大小变化，画图时原来的“靶点”会被清除
void FrmCIE1931::resizeEvent(QResizeEvent *size)
{
    imgcie = QPixmap(this->width(),this->height());             //尺寸跟着窗口变化，填充整个窗口
    label->setGeometry(0,0,this->width(),this->height());
    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空
    p.begin(&imgcie);
    drawcie(&p);
    p.end();
    label->setPixmap(imgcie);
    drawaxis_xy();
}

void FrmCIE1931::mspecxy(int iindex)
{
    if(iindex == itag){
        printxy(unitpublic::lsttestdatapkg[itag][LED_1].CIE_x,unitpublic::lsttestdatapkg[itag][LED_1].CIE_y);
        printxy(unitpublic::lsttestdatapkg[itag][LED_2].CIE_x,unitpublic::lsttestdatapkg[itag][LED_2].CIE_y);
        printxy(unitpublic::lsttestdatapkg[itag][LED_3].CIE_x,unitpublic::lsttestdatapkg[itag][LED_3].CIE_y);
    }
}

void FrmCIE1931::on_pushButton_clicked()
{

}

void FrmCIE1931::AxisXY_mZoom(QPoint beginPoint, QPoint endPoint)
{
    if((endPoint.x() - beginPoint.x())>10 && (endPoint.y() - beginPoint.y())>10)
    {   //
        qDebug() << "放大" << beginPoint.x() << endPoint.x() << beginPoint.y() << endPoint.y();
    }
    if((beginPoint.x() - endPoint.x())>10 && (beginPoint.y() - endPoint.y())>10)
    {   //
        qDebug() << "缩小" << beginPoint.x() << endPoint.x() << beginPoint.y() << endPoint.y();

    }

//    imgcie = QPixmap(this->width(),this->height());             //尺寸跟着窗口变化，填充整个窗口
//    label->setGeometry(0,0,this->width(),this->height());
//    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空
//    p.begin(&imgcie);
//    drawcie(&p);
//    p.end();
//    label->setPixmap(imgcie);
//    drawaxis_xy();

}

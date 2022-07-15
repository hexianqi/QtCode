#include "frmcie1931.h"
#include "ui_frmcie1931.h"
#include <qpainter.h>
#include "colormatchingfunctions.h"
#include "qmath.h"
#include "qdebug.h"
#include "frmmain.h"
#include "unitpublic.h"
#include "qdebug.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

#include <QDebug>
#include <QMouseEvent>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    m_isMousePress = false;

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
    }else
    if(ev->button() == Qt::RightButton)
    {
        emit AxisXY_Menu(ev->x(),ev->y());
    }
}
//鼠标释放事件
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_endPoint = ev->pos(); //获取结束按下的点坐标
        m_isMousePress = false; //鼠标松开
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
    if( e->type() == QEvent::MouseMove)
    {
        //如果是鼠标移动  拦截事件，不向下分发
        QMouseEvent *ev = static_cast<QMouseEvent *>(e);
        emit AxisXY_Disp(ev->x(),ev->y());      //显示xy坐标值
        m_midPoint=ev->pos();   //虚线中间点
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

void FrmCIE1931::AxisXY_mMenu(int x,int y)
{
    m_menu->exec(QCursor::pos());   //显示右键菜单
}

void FrmCIE1931::AxisXY_mDisp(int x,int y)
{   //在窗体的标题栏中显示当前鼠标对应xy坐标
    float fx = x * ciexy.ipx + ciexy.xmin;
    float fy = ciexy.ymax-y*ciexy.ipy;// +ciexy.ymin;
    QString sx = QString::number(fx,'f',4);
    QString sy = QString::number(fy,'f',4);
    this->setWindowTitle(QString("打靶图 - %1#         XY:   %2,%3").arg(itag+1).arg(sx).arg(sy));
}

//右键菜单 - 初始化坐标系
void FrmCIE1931::slot_menu_clear()
{
    ciexy.xmin = 0.0;   //初始化默认坐标系
    ciexy.xmax = 1.0;
    ciexy.ymin = 0.0;
    ciexy.ymax = 1.0;
    ciexy.ipx = (ciexy.xmax - ciexy.xmin) / this->width();        //横坐标每像素对应的坐标步进值
    ciexy.ipy = (ciexy.ymax - ciexy.ymin) / this->height();       //纵坐标每像素对应的坐标步进值
    drawcie1931(true);  //重画坐标系
}

//右键菜单 - 黑体色温曲线
void FrmCIE1931::slot_menu_heiti()
{
    disp_heiti = actHeiti->isChecked();
    drawcie1931(true);  //重画坐标系
}

void FrmCIE1931::slot_menu_tuoyuan()
{
    disp_tuoyuan = actTuoyuan->isChecked();
    drawcie1931(true);  //重画坐标系
}

void FrmCIE1931::slot_menu_matitu()
{
    disp_matitu = actMatitu->isChecked();
    drawcie1931(true);  //重画坐标系
}

void FrmCIE1931::slot_menu_fenji()
{
    disp_fenji = actFenji->isChecked();
    drawcie1931(true);  //重画坐标系
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

    lst_hisxy.clear();  //历史打靶坐标值清空
    label = new MyLabel(this);      //显示色品图
    label->setMouseTracking(true);  //注意，必须加上这一句，否则鼠标的QEvent::MouseMove事件必须在鼠标按下时移动才有效
    connect(label,SIGNAL(AxisXY_Disp(int,int)),this,SLOT(AxisXY_mDisp(int,int))); //注意函数名大小写也必须保持一致
    connect(label,SIGNAL(AxisXY_Zoom(QPoint,QPoint)),this,SLOT(AxisXY_mZoom(QPoint,QPoint))); //注意函数名大小写也必须保持一致
    connect(label,SIGNAL(AxisXY_Menu(int,int)),this,SLOT(AxisXY_mMenu(int,int))); //注意函数名大小写也必须保持一致

    m_menu = new QMenu(label);  //定义右键菜单，在mylabel的鼠标右键点击事件中发出槽信号，在窗体中弹出菜单并显示

    actClear = new QAction();
    actClear->setText("坐标初始化");
    actClear->setCheckable(false);
    m_menu->addAction(actClear);
    connect(actClear,SIGNAL(triggered()),this,SLOT(slot_menu_clear()));  //初始化坐标系
    m_menu->addSeparator();

    actHeiti = new QAction();
    actHeiti->setText("黑体色温曲线");
    actHeiti->setCheckable(true);
    actHeiti->setChecked(disp_heiti);
    connect(actHeiti,SIGNAL(triggered()),this,SLOT(slot_menu_heiti()));
    m_menu->addAction(actHeiti);

    actTuoyuan = new QAction();
    actTuoyuan->setText("色容差椭圆");
    actTuoyuan->setCheckable(true);
    actTuoyuan->setChecked(disp_tuoyuan);
    connect(actTuoyuan,SIGNAL(triggered()),this,SLOT(slot_menu_tuoyuan()));
    m_menu->addAction(actTuoyuan);

    actMatitu = new QAction();
    actMatitu->setText("色品马蹄图");
    actMatitu->setCheckable(true);
    actMatitu->setChecked(disp_matitu);
    connect(actMatitu,SIGNAL(triggered()),this,SLOT(slot_menu_matitu()));
    m_menu->addAction(actMatitu);
    m_menu->addSeparator();

    actFenji = new QAction();
    actFenji->setText("色区分级框图");
    actFenji->setCheckable(true);
    actFenji->setChecked(disp_fenji);
    connect(actFenji,SIGNAL(triggered()),this,SLOT(slot_menu_fenji()));
    m_menu->addAction(actFenji);

    //在窗口的resizeEvent事件中画CIE色品图

    this->setMaximumSize(CIE_WIDTH,CIE_HEIGHT);
    this->setMinimumSize(200,200);
    ciexy.xmin = 0.0;   //初始化默认坐标系
    ciexy.xmax = 1.0;
    ciexy.ymin = 0.0;
    ciexy.ymax = 1.0;
    ciexy.ipx = (ciexy.xmax - ciexy.xmin) / this->width();        //横坐标每像素对应的坐标步进值
    ciexy.ipy = (ciexy.ymax - ciexy.ymin) / this->height();       //纵坐标每像素对应的坐标步进值
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
//void FrmCIE1931::paintEvent(QPaintEvent *event)
//{
//}


//打把，画十字线
void FrmCIE1931::printxy(float x, float y,bool his_xy)
{
    if(!his_xy){
        lst_hisxy.insert(0,QPointF(x,y));//如果不是历史数据，则打靶数据存入历史缓存
    }
    if((x>=ciexy.xmin) && (x<=ciexy.xmax) && (y>=ciexy.ymin) &&(y<=ciexy.ymax)){    //打靶坐标必须在当前坐标系范围内
        p.begin(&imgcie);
        p.setPen(QPen(Qt::black,1));
        p.setBrush(QBrush(Qt::black));
        float fx=(x-ciexy.xmin)/ciexy.ipx;
        float fy=(ciexy.ymax-y)/ciexy.ipy;
        p.drawLine(fx-3.0,fy,fx+3.0,fy);
        p.drawLine(fx,fy-3.0,fx,fy+3.0);
        p.end();
        if(!his_xy)     //历史打靶，不直接输出，先内存处理
            label->setPixmap(imgcie);
    }
}

//在窗口的resizeEvent事件中画CIE色品图
//色品图随尺寸大小变化，画图时原来的“靶点”会被清除
void FrmCIE1931::resizeEvent(QResizeEvent *size)
{
    ciexy.ipx = (ciexy.xmax - ciexy.xmin) / this->width();        //横坐标每像素对应的坐标步进值
    ciexy.ipy = (ciexy.ymax - ciexy.ymin) / this->height();       //纵坐标每像素对应的坐标步进值

    drawcie1931(true);  //窗口尺寸变化时，重画色品图
}

void FrmCIE1931::mspecxy(int iindex)
{
    if(iindex == itag){
        printxy(unitpublic::lsttestdatapkg[itag][LED_1].CIE_x,unitpublic::lsttestdatapkg[itag][LED_1].CIE_y);
        printxy(unitpublic::lsttestdatapkg[itag][LED_2].CIE_x,unitpublic::lsttestdatapkg[itag][LED_2].CIE_y);
        printxy(unitpublic::lsttestdatapkg[itag][LED_3].CIE_x,unitpublic::lsttestdatapkg[itag][LED_3].CIE_y);
    }
}

void FrmCIE1931::AxisXY_mZoom(QPoint beginPoint, QPoint endPoint)
{
    if((endPoint.x() - beginPoint.x())>10 && (endPoint.y() - beginPoint.y())>10)
    {   //放大时必须要有一定的范围，否则不做处理，即鼠标拖动选择区域范围有限制，矩形区域太小则不进行缩放处理
        qDebug() << "放大" << beginPoint.x() << endPoint.x() << beginPoint.y() << endPoint.y();
        double xmax = ciexy.xmin + endPoint.x()   * ciexy.ipx;
        double xmin = ciexy.xmin + beginPoint.x() * ciexy.ipx;
        double ymin = ciexy.ymax - endPoint.y()   * ciexy.ipy;
        double ymax = ciexy.ymax - beginPoint.y() * ciexy.ipy;
        if((xmax-xmin)>0.001)
        {   //放大最小分辨率，即最大最小值坐标间距至少为0.001，0.001是当前色品底图1000*1000像素对应坐标系0-1.0的最小像素单位
            ciexy.xmax = xmax;
            ciexy.xmin = xmin;
            ciexy.ipx = (xmax - xmin) / this->width();      //注意浮点数计算， 否则ipx结果会变0
        }
        if((ymax-ymin)>0.001)
        {
            ciexy.ymin = ymin;
            ciexy.ymax = ymax;   //注意，纵坐标的最大值是起点，最小值在终点
            ciexy.ipy = (ymax - ymin) / this->height();
        }
        drawcie1931(true);
    }
}

void FrmCIE1931::drawcie1931(bool hisxy)
{
    //1.内存图片重绘初始化
    imgcie = QPixmap(this->width(),this->height());             //尺寸跟着窗口变化，填充整个窗口
    label->setGeometry(0,0,this->width(),this->height());
    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空

    //2.导入色品图底图，不显示色品图的时候可以导入一个相同像素尺寸的空白图片即可，色品图底图像素尺寸必须是1000*1000，对应0 - 1.0坐标系
    p.begin(&imgcie);
    QImage img;
    if(disp_matitu){img.load(":/new/prefix1/res/pic/CIE1931.jpg");}
    else {img.load(":/new/prefix1/res/pic/CIE1931_1.jpg");}   //不显示色品图时
    p.drawImage(QRect(0,0,label->geometry().width(),label->geometry().height()),img,
                         QRect(ciexy.xmin/0.001,(1-ciexy.ymax)/0.001,(ciexy.xmax-ciexy.xmin)/0.001,(ciexy.ymax-ciexy.ymin)/0.001)
                       );   //注意，此处0.001 = 1.0 / CIE_WIDTH，1.0 / CIE_HEIGHT，即底图的坐标系

    //3.画坐标系
    p.setPen(QPen(Qt::darkGray,1));
    for (int i=0;i<10;i++) {
        p.drawLine(0,i*(this->height()/10.0),this->width(),i*(this->height()/10.0));
        p.drawLine(i*(this->width()/10.0),0,i*(this->width()/10.0),this->height());
    }
    p.drawText(2,this->height()-2,QString::number(ciexy.xmin,'f',4));   //原点，左下角
    p.drawText(2,this->height()-20,QString::number(ciexy.ymin,'f',4));   //原点，左下角
    p.drawText(2,12,QString::number(ciexy.ymax,'f',4));                 //Y轴，左上角
    p.drawText(this->width()-35,this->height()-2,QString::number(ciexy.xmax,'f',4));    //X轴，右小角

    //4.画黑体色温曲线
    if(disp_heiti){
        p.setPen(QPen(Qt::black,2));
        for (int i=0;i<66;i++) {
            double x1 = (3*temprou[i])   / (4 + 2*temprou[i]-8*temprov[i]);         //计算黑体曲线坐标，标准算法
            double y1 = (2*temprov[i])   / (4 + 2*temprou[i]-8*temprov[i]);
            double x2 = (3*temprou[i+1]) / (4 + 2*temprou[i+1]-8*temprov[i+1]);
            double y2 = (2*temprov[i+1]) / (4 + 2*temprou[i+1]-8*temprov[i+1]);

            float fx1=(x1-ciexy.xmin)/ciexy.ipx;
            float fy1=(ciexy.ymax-y1)/ciexy.ipy;
            float fx2=(x2-ciexy.xmin)/ciexy.ipx;
            float fy2=(ciexy.ymax-y2)/ciexy.ipy;

            p.drawLine(fx1,fy1,fx2,fy2);
        }
    }
    //5.画色容差椭圆
    if(disp_tuoyuan){

    }

    //6.画色区分级框图
    if(disp_fenji){
        lstbinxypkg.clear();
        readbinsetpara();
        p.setPen(QPen(Qt::blue,1));
        for (int i=0;i<lstbinxypkg.count();i++) {

            float fx1=(lstbinxypkg.at(i).pt0.x()-ciexy.xmin)/ciexy.ipx;
            float fy1=(ciexy.ymax-lstbinxypkg.at(i).pt0.y())/ciexy.ipy;
            float fx2=(lstbinxypkg.at(i).pt1.x()-ciexy.xmin)/ciexy.ipx;
            float fy2=(ciexy.ymax-lstbinxypkg.at(i).pt1.y())/ciexy.ipy;
            p.drawLine(fx1,fy1,fx2,fy2);

            fx1=(lstbinxypkg.at(i).pt0.x()-ciexy.xmin)/ciexy.ipx;
            fy1=(ciexy.ymax-lstbinxypkg.at(i).pt0.y())/ciexy.ipy;
            fx2=(lstbinxypkg.at(i).pt3.x()-ciexy.xmin)/ciexy.ipx;
            fy2=(ciexy.ymax-lstbinxypkg.at(i).pt3.y())/ciexy.ipy;
            p.drawLine(fx1,fy1,fx2,fy2);

            fx1=(lstbinxypkg.at(i).pt2.x()-ciexy.xmin)/ciexy.ipx;
            fy1=(ciexy.ymax-lstbinxypkg.at(i).pt2.y())/ciexy.ipy;
            fx2=(lstbinxypkg.at(i).pt1.x()-ciexy.xmin)/ciexy.ipx;
            fy2=(ciexy.ymax-lstbinxypkg.at(i).pt1.y())/ciexy.ipy;
            p.drawLine(fx1,fy1,fx2,fy2);

            fx1=(lstbinxypkg.at(i).pt2.x()-ciexy.xmin)/ciexy.ipx;
            fy1=(ciexy.ymax-lstbinxypkg.at(i).pt2.y())/ciexy.ipy;
            fx2=(lstbinxypkg.at(i).pt3.x()-ciexy.xmin)/ciexy.ipx;
            fy2=(ciexy.ymax-lstbinxypkg.at(i).pt3.y())/ciexy.ipy;
            p.drawLine(fx1,fy1,fx2,fy2);
        }
    }
    //7.画历史打靶坐标
    if(hisxy){
        for (int i=0;i<lst_hisxy.count();i++) {
            if (i > hisxy_maxcount) break;  //最多可显示的历史打靶坐标数量
            printxy(lst_hisxy.at(i).x(),lst_hisxy.at(i).y(),true);  //历史打靶数据
        }
    }
    p.end();

    //内存画图处理完毕，输出显示，为了保证色品图刷新效率，所有画图初始化操作都在内存中完成后再一次性输出显示
    label->setPixmap(imgcie);

}

//从数据表 binset_para 中获取分级参数
void FrmCIE1931::readbinsetpara()
{
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinset,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        //分级坐标只查询“晶1”的数据，默认只处理单晶白光
        mysql.exec(QString("select distinct binxy1_name,x0_1,y0_1,x1_1,y1_1,x2_1,y2_1,x3_1,y3_1 from binset_para where station_id=%1").arg(itag));    //查询xy分级参数表
        while (mysql.next()) {
            BinXyPkg binxypkg;
            binxypkg.name = mysql.value(0).toString();
            binxypkg.pt0 =  QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble());
            binxypkg.pt1 =  QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble());
            binxypkg.pt2 =  QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble());
            binxypkg.pt3 =  QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble());
            lstbinxypkg.append(binxypkg);
        }
    }
    mydb.close();

}

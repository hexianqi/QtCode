#include "frmbinxy.h"
#include "ui_frmbinxy.h"

#include <QMouseEvent>
#include "qdebug.h"
#include "float.h"
#include "qstandarditemmodel.h"
#include "qmessagebox.h"
#include "qpolygon.h"
#include "unitpublic.h"
#include "unitprofile.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

const int XY_WIDTH = 420;       //坐标系显示区尺寸大小
const int XY_HEIGHT = 420;

int FrmBinxy::moldx=0;
int FrmBinxy::moldy=0;


int FrmBinxy::ixyindex = -1;

FrmBinxy::FrmBinxy(qint8 iindex,QString stp,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBinxy)
{
    ui->setupUi(this);
    itag = iindex;
    stype = stp;
    for (int i=0;i<LED_COUNT;i++) {
        if(stp.contains(QString::number(i+1))){
            iledindex = i;      //获取晶片序号，0,1,2
            break;
        }
    }
    this->setGeometry(360,200,1024,690);          //显示位置
    this->setWindowTitle(QString("xy坐标分级（%1）   %2#").arg(stype).arg(itag+1));
    ui->edtminx->setText("0.000");
    ui->edtmaxx->setText("1.000");
    ui->edtminy->setText("0.000");
    ui->edtmaxy->setText("1.000");

    label = new MyXyLabel(this);      //显示色品图
    label->setGeometry(10,10,480,480);
    imgcie = QPixmap(label->geometry().width(),label->geometry().height());             //尺寸跟着窗口变化，填充整个窗口
    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空
    label->setMouseTracking(true);  //注意，必须加上这一句，否则鼠标的QEvent::MouseMove事件必须在鼠标按下时移动才有效
    connect(label,SIGNAL(AxisXY_Disp(int,int)),this,SLOT(AxisXY_mDisp(int,int))); //注意函数名大小写也必须保持一致
    connect(label,SIGNAL(AxisXY_Press(int,int)),this,SLOT(AxisXY_mPress(int,int)));
    connect(label,SIGNAL(AxisXY_DblClick(int,int)),this,SLOT(AxisXY_mDblClick(int,int)));

    QDoubleValidator*validator=new QDoubleValidator(0.0,1.0,4,this);        //坐标值输入框，范围0-1，四位小数
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->edtminx->setValidator(validator);
    ui->edtmaxx->setValidator(validator);
    ui->edtminy->setValidator(validator);
    ui->edtmaxy->setValidator(validator);
    ui->edtx0->setValidator(validator);
    ui->edty0->setValidator(validator);
    ui->edtx1->setValidator(validator);
    ui->edty1->setValidator(validator);
    ui->edtx2->setValidator(validator);
    ui->edty2->setValidator(validator);
    ui->edtx3->setValidator(validator);
    ui->edty3->setValidator(validator);

    ui->edtx0->installEventFilter(this);
    ui->edty0->installEventFilter(this);
    ui->edtx1->installEventFilter(this);
    ui->edty1->installEventFilter(this);
    ui->edtx2->installEventFilter(this);
    ui->edty2->installEventFilter(this);
    ui->edtx3->installEventFilter(this);
    ui->edty3->installEventFilter(this);
    drawaxis_xy();
    tvbinxyInit();
    if(readbinxytemp()){        //从xy自动分级临时参数表中获取上次设置的相关xy分选参数，并刷新显示
        ui->btnfenji->click();
    };
}

FrmBinxy::~FrmBinxy()
{
    delete ui;
}

//过滤坐标输入事件，捕捉编辑状态
bool FrmBinxy::eventFilter(QObject * watched, QEvent *event)
{

    if((watched == ui->edtx0)||(watched == ui->edty0))
    {
        if(event->type()==QEvent::FocusIn) {    //获取输入信号
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::yellow);
            ui->edtx0->setPalette(p);
            ui->edty0->setPalette(p);
            ixyindex = 0;
        }else if (event->type()==QEvent::FocusOut){
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::white);
            ui->edtx0->setPalette(p);
            ui->edty0->setPalette(p);
            ixyindex=-1;
        }
    }else
    if((watched == ui->edtx1)||(watched == ui->edty1))
    {
        if(event->type()==QEvent::FocusIn) {    //获取输入信号
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::yellow);
            ui->edtx1->setPalette(p);
            ui->edty1->setPalette(p);
            ixyindex = 1;
        }else if (event->type()==QEvent::FocusOut){
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::white);
            ui->edtx1->setPalette(p);
            ui->edty1->setPalette(p);
            ixyindex=-1;
        }
    }else
    if((watched == ui->edtx2)||(watched == ui->edty2))
    {
        if(event->type()==QEvent::FocusIn) {    //获取输入信号
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::yellow);
            ui->edtx2->setPalette(p);
            ui->edty2->setPalette(p);
            ixyindex=2;
        }else if (event->type()==QEvent::FocusOut){
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::white);
            ui->edtx2->setPalette(p);
            ui->edty2->setPalette(p);
            ixyindex=-1;
        }
    }else
    if((watched == ui->edtx3)||(watched == ui->edty3))
    {
        if(event->type()==QEvent::FocusIn) {    //获取输入信号
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::yellow);
            ui->edtx3->setPalette(p);
            ui->edty3->setPalette(p);
            ixyindex=3;
        }else if (event->type()==QEvent::FocusOut){
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::white);
            ui->edtx3->setPalette(p);
            ui->edty3->setPalette(p);
            ixyindex=-1;
        }
    }
}

MyXyLabel::MyXyLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
   // setMouseTracking(true);
}


//鼠标进入事件
void MyXyLabel::enterEvent(QEvent *)
{
//    qDebug() << "鼠标进入了";
}

//鼠标离开事件
void MyXyLabel::leaveEvent(QEvent *)
{
//     qDebug() << "鼠标离开了";
}


//鼠标按下事件
void MyXyLabel::mousePressEvent(QMouseEvent *ev)
{
    //鼠标左键按下  打印信息
    if(ev->button() == Qt::LeftButton)
    {
        FrmBinxy::moldx = ev->x()-40;  //拖放前坐标
        FrmBinxy::moldy = ev->y()-20;
    }
}
//鼠标释放事件
void MyXyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        emit AxisXY_Press(ev->x()-40,ev->y()-20);
    }
}
//鼠标移动事件
void MyXyLabel::mouseMoveEvent(QMouseEvent *ev)
{

}


//事件分发器 :用途，分发事件
bool MyXyLabel::event(QEvent *e)
{
    if( e->type() == QEvent::MouseMove)
    {
        //如果是鼠标移动  拦截事件，不向下分发
        QMouseEvent *ev = static_cast<QMouseEvent *>(e);
        emit AxisXY_Disp(ev->x()-40,ev->y()-20);      //显示xy坐标值
        return true;
    }else
        if( e->type() == QEvent::MouseButtonDblClick)
        {
            emit AxisXY_DblClick(0,0);      //双击初始化坐标
            return true;
        }
    //其他事件  抛给父类去处理
    return QLabel::event(e);
}
//画4点坐标区域
void FrmBinxy::drawaxis_xy4()
{
    p.begin(&imgcie);
    QPointF point[] = {
        QPointF(40+(ui->edtx0->text().toFloat()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - ui->edty0->text().toFloat())/pciexy.ipy),
        QPointF(40+(ui->edtx1->text().toFloat()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - ui->edty1->text().toFloat())/pciexy.ipy),
        QPointF(40+(ui->edtx2->text().toFloat()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - ui->edty2->text().toFloat())/pciexy.ipy),
        QPointF(40+(ui->edtx3->text().toFloat()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - ui->edty3->text().toFloat())/pciexy.ipy),
    };
    p.setPen(QPen(Qt::red,1));
    p.drawPolygon(point,4);     //画区域
    p.end();
    label->setPixmap(imgcie);
}

//画坐标系
void FrmBinxy::drawaxis_xy()
{
    pciexy.xmin = ui->edtminx->text().toFloat();     //注意输入框的内容，必须是0-1范围内的浮点数，坐标值
    pciexy.xmax = ui->edtmaxx->text().toFloat();
    pciexy.ymin = ui->edtminy->text().toFloat();
    pciexy.ymax = ui->edtmaxy->text().toFloat();
    pciexy.ipx = (pciexy.xmax - pciexy.xmin) / XY_WIDTH ;    //计算X、Y轴分辨率
    pciexy.ipy = (pciexy.ymax - pciexy.ymin) / XY_HEIGHT ;

    imgcie.fill(Qt::white); //注意，重绘时原来的图形都清空
    p.begin(&imgcie);
    p.setPen(QPen(Qt::black,2));
    p.drawRect(40,20,XY_WIDTH,XY_HEIGHT);   //画坐标XY轴，背景label的尺寸是480*480，坐标区域为420*420，上下左右留边，空白区域
                                    //留白：左40，下40，上20，右20
    p.drawText(30,40+XY_HEIGHT,ui->edtminx->text());        //原点X，左下角
    p.drawText(2,10+XY_HEIGHT,ui->edtminy->text());        //原点Y，左下角
    p.drawText(2,20,ui->edtmaxy->text());                  //Y轴，左上角
    p.drawText(label->geometry().width()-50,40+XY_HEIGHT,ui->edtmaxx->text());    //X轴，右下角

    p.drawText(2,XY_HEIGHT/2 + 20,QString::number((pciexy.ymax+pciexy.ymin)/2,'f',4));        //Y轴中线
    p.drawText(40+XY_WIDTH/2,40+XY_WIDTH,QString::number((pciexy.xmax+pciexy.xmin)/2,'f',4)); //X轴中线

    QPen pen;
    QVector<qreal>dashes;
    qreal space = 4;
    dashes << 3 << space;
    pen.setDashPattern(dashes); //虚线
    pen.setColor(Qt::darkGray); //灰色
    pen.setWidth(1);            //线宽
    p.setPen(pen);
    p.drawLine(40,XY_HEIGHT/2 + 20,XY_WIDTH+40,XY_HEIGHT/2 + 20);       //坐标中间画2条十字虚线
    p.drawLine(40+XY_WIDTH/2,20,40+XY_WIDTH/2,XY_HEIGHT+20);
    p.end();
    label->setPixmap(imgcie);
}

//分BIN参数编辑列表初始化
//行信息来源于产品测试项目中是否参与分BIN的设置
void FrmBinxy::tvbinxyInit()
{
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(9);  //
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("NAME"));         //为什么用fromLocal8Bit会乱码，
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("X0"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Y0"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("X1"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Y1"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("X2"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Y2"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("X3"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("Y3"));
    ui->tvbinxy->setModel(model);
    ui->tvbinxy->setColumnWidth(0,90);
    ui->tvbinxy->setColumnWidth(1,50);
    ui->tvbinxy->setColumnWidth(2,50);
    ui->tvbinxy->setColumnWidth(3,50);
    ui->tvbinxy->setColumnWidth(4,50);
    ui->tvbinxy->setColumnWidth(5,50);
    ui->tvbinxy->setColumnWidth(6,50);
    ui->tvbinxy->setColumnWidth(7,50);
    ui->tvbinxy->setColumnWidth(8,50);
    ui->tvbinxy->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: black;"          //文字颜色
                                                     "font: 9pt;"      //字体大小
                                                     "padding-left: 2px;"
                                                     "border: 1px solid #6c6c6c;}");

   // ui->tvbinxy->setEditTriggers(QAbstractItemView::AllEditTriggers);  //双击选中某个单元格时进入编辑状态
    ui->tvbinxy->setSelectionBehavior(QAbstractItemView::SelectItems);    //设置选中模式为选单元格

    ui->tvbinxy->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tvbinxy->verticalHeader()->setDefaultSectionSize(16); //行高
    ui->tvbinxy->verticalHeader()->setSectionsClickable(true);    //允许点击行标题头
  //  connect(ui->tvbinxy->model(),SIGNAL(itemChanged(QStandardItem*)),this,SLOT(tvItemChanged()));
}

//打把，画十字线
void FrmBinxy::printxy(float x, float y)
{
    p.begin(&imgcie);
    p.setPen(QPen(Qt::black,1));
    p.setBrush(QBrush(Qt::black));

    float fx=40+(x-pciexy.xmin)/pciexy.ipx;
    float fy=20+(pciexy.ymax - y)/pciexy.ipy;

//    float fx=x*label->geometry().width();
//    float fy=(1-y)*label->geometry().height();
    p.drawLine(fx-3.0,fy,fx+3.0,fy);
    p.drawLine(fx,fy-3.0,fx,fy+3.0);
    p.end();
    label->setPixmap(imgcie);
}

//处理色品图点击事件
void FrmBinxy::AxisXY_mDisp(int x,int y)
{   //在窗体的标题栏中显示当前鼠标对应xy坐标
    QString sx = QString::number(pciexy.xmin + x *pciexy.ipx,'f',4);
    QString sy = QString::number(pciexy.ymax - y *pciexy.ipy,'f',4);
    this->setWindowTitle(QString("xy坐标分级（%1）   %2#      XY:  %3,%4").arg(stype).arg(itag+1).arg(sx).arg(sy));
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinxy->model());//通过QStandardItemModel获取tableview行数据,继承类型强制转换
    for (int i=0;i<ui->tvbinxy->model()->rowCount();i++) {
        QVector<QPointF> points;
        points.append(QPointF(40+(model->data(model->index(i,1)).toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->data(model->index(i,2)).toFloat())/pciexy.ipy));
        points.append(QPointF(40+(model->data(model->index(i,3)).toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->data(model->index(i,4)).toFloat())/pciexy.ipy));
        points.append(QPointF(40+(model->data(model->index(i,5)).toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->data(model->index(i,6)).toFloat())/pciexy.ipy));
        points.append(QPointF(40+(model->data(model->index(i,7)).toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->data(model->index(i,8)).toFloat())/pciexy.ipy));


        QPolygonF polygon(points);
        if(polygon.containsPoint(QPointF(x+40,y+20),Qt::WindingFill)){
            ui->tvbinxy->selectRow(i);
        }
    }
}


void FrmBinxy::on_toolButton_clicked()
{   //根据设置的X、Y轴坐标起始及终止值，重画XY坐标图
    drawaxis_xy();
}

void FrmBinxy::AxisXY_mDblClick(int x,int y)
{
    xyzoom(0,x,y);
}

void FrmBinxy::AxisXY_mPress(int x,int y)
{   //鼠标点击事件
    if((qAbs(x-moldx)>3) || (qAbs(y-moldy)>3))
    {   //鼠标拖放，坐标至少移动3个像素才被当做是拖放
        xyzoom(3,x,y);
        //qDebug() << x << moldx << y << moldx;
    }
    switch (ixyindex) {
    case 0:{
        ui->edtx0->setText(QString::number(pciexy.xmin+x*pciexy.ipx,'f',4));
        ui->edty0->setText(QString::number(pciexy.ymax-y*pciexy.ipy,'f',4));
        break;
    }
    case 1:{
        ui->edtx1->setText(QString::number(pciexy.xmin+x*pciexy.ipx,'f',4));
        ui->edty1->setText(QString::number(pciexy.ymax-y*pciexy.ipy,'f',4));
        break;
    }
    case 2:{
        ui->edtx2->setText(QString::number(pciexy.xmin+x*pciexy.ipx,'f',4));
        ui->edty2->setText(QString::number(pciexy.ymax-y*pciexy.ipy,'f',4));
        break;
    }
    case 3:{
        ui->edtx3->setText(QString::number(pciexy.xmin+x*pciexy.ipx,'f',4));
        ui->edty3->setText(QString::number(pciexy.ymax-y*pciexy.ipy,'f',4));
        break;
    }
    }

    if(ixyindex>-1){    //编辑状态下，才画四边形
        drawaxis_xy();  //先初始化原图
        drawaxis_xy4(); //画新四边形
    }
}
//计算两条直线的交叉点坐标
 QPointF FrmBinxy::line2point(QLineF l1,QLineF l2)
 {
    float k1 = 0; float b1=0; float k2=0;float b2=0;
    if(l1.p1().x() != l1.p2().x()){
        k1 = (l1.p1().y() - l1.p2().y()) / (l1.p1().x() - l1.p2().x());
        b1 = (l1.p2().y() * l1.p1().x() - l1.p1().y()*l1.p2().x()) / (l1.p1().x() - l1.p2().x());
    }
    if(l2.p1().x() != l2.p2().x())
    {
       k2 = (l2.p1().y() - l2.p2().y()) / (l2.p1().x() - l2.p2().x());
       b2 = (l2.p2().y() * l2.p1().x() - l2.p1().y() * l2.p2().x()) / (l2.p1().x() - l2.p2().x());
    }
    if((l1.p1().x() != l1.p2().x()) && (l2.p1().x() != l2.p2().x()))
    {
        return QPointF((b2 - b1)/(k1 - k2),(k1*b2 - k2*b1)/(k1-k2));
    }else
    if((l1.p1().x() != l1.p2().x()) && (l2.p1().x() == l2.p2().x()))
    {
        return QPointF(l2.p1().x(),k1 * l2.p1().x() + b1);
    }else
    if((l1.p1().x() == l1.p2().x()) && (l2.p1().x() != l2.p2().x()))
    {
        return QPointF(l1.p1().x(),k2 * l1.p1().x() + b2);
    }else
    {
        return QPointF(-1,-1);      //平行线
    }
 }

 //等分四边形区域
 //输入：QPointF4 point4：待等分的四边型区域4个点坐标
 //     ixf,iyf：X、Y方向上等分的数量
 //     QList<QLineF> *lines：返回等分后的线条数组
 //     QList<QPointF4> *points4：返回等分后个小四边形的4点坐标列表数组
 //    return：返回等分后小四边形数量
int FrmBinxy::gfDrawxy4(QPointF4 pf4,int ixf,int iyf,QVector<QLineF> *lines,QList<QPointF4> *pfs4)
{
    //第一步：计算X轴等分后的线段
    QVector<QLineF> linex;      //X轴等分后的线段，注意水平或垂直线的处理，K=0或 ∞
    for (int i=0;i<ixf+1;i++) {
        QLineF l1(pf4.pt1,pf4.pt4);
        float xf1 = (pf4.pt4.x() - pf4.pt1.x()) / ixf;  //X向上边线等分值
        QLineF l2(QPointF(pf4.pt1.x() + i*xf1,1),QPointF(pf4.pt1.x() + i*xf1,2));   //即经过待等分的X向直线上，在等分点做一条直线（y分别是1,2），通过2条相交线的交叉点来求这点的Y坐标
        QPointF p03 = line2point(l1,l2);    //X上边线等分点的坐标值

        QLineF l3(pf4.pt2,pf4.pt3);
        float xf2 = (pf4.pt3.x() - pf4.pt2.x()) / ixf;  //X向下边线等分值
        QLineF l4(QPointF(pf4.pt2.x() + i*xf2,1),QPointF(pf4.pt2.x() + i*xf2,1));
        QPointF p04 = line2point(l3,l4);    //X下边线等分点的坐标值
        linex.append(QLineF(p03,p04));      //上下边线等分点连接成一条直线
        lines->append(QLineF(QPointF(40+(p03.x()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - p03.y())/pciexy.ipy),      //坐标值转化为像素值
                             QPointF(40+(p04.x()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - p04.y())/pciexy.ipy)));
    }
    //第二步，计算Y轴等分后的线段
    QVector<QLineF> liney;
    for(int i=0;i<iyf+1;i++)
    {
        QLineF l1(pf4.pt1,pf4.pt2);
        float yf1 = (pf4.pt1.y() - pf4.pt2.y()) / iyf;  //Y向左边线等分值
        QLineF l2(QPointF(1,pf4.pt1.y() - yf1*i),QPointF(2,pf4.pt1.y() - yf1*i));   //同上，在Y向等分点上做一条直线
        QPointF p03 = line2point(l1,l2);

        QLineF l3(pf4.pt4,pf4.pt3);
        float yf2 = (pf4.pt4.y() - pf4.pt3.y()) / iyf;
        QLineF l4(QPointF(1,pf4.pt4.y() - yf2*i),QPointF(2,pf4.pt4.y() - yf2*i));
        QPointF p04 = line2point(l3,l4);
        liney.append(QLineF(p03,p04));  //左右边线等分点连接成一条直线
        lines->append(QLineF(QPointF(40+(p03.x()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - p03.y())/pciexy.ipy),      //坐标值转化为像素值
                             QPointF(40+(p04.x()-pciexy.xmin)/pciexy.ipx,20+(pciexy.ymax - p04.y())/pciexy.ipy)));
    }
    //第三步，计算以上各线段的交叉点坐标，即是分级区域的坐标


    for (int ix=0;ix<ixf;ix++) {
        for (int iy=0;iy<iyf;iy++) {
            QPointF4 f4;
            f4.pt1 = line2point(linex.at(ix),liney.at(iy));         //获取左上点坐标
            f4.pt4 = line2point(linex.at(ix+1),liney.at(iy));       //获取右上点坐标
            f4.pt3 = line2point(linex.at(ix+1),liney.at(iy+1));     //右下
            f4.pt2 = line2point(linex.at(ix),liney.at(iy+1));       //左下
            pfs4->append(f4);
        }
    }
    return ixf * iyf;
}

void FrmBinxy::on_edtx0_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}
void FrmBinxy::on_edty0_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_edtx1_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_edty1_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_edtx2_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}
void FrmBinxy::on_edty2_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_edtx3_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_edty3_textChanged(const QString &arg1)
{
    ui->btnfenji->click();  //可以直接修改编辑框的坐标，调整框图位置
}

void FrmBinxy::on_btnfenji_clicked()
{
    //按等分数量，划分四角形区域，并计算对应的各坐标点xy值，在tableview中显示
    ui->spx->setFocus();    //把输入焦点从坐标输入编辑框移除

       drawaxis_xy();  //先初始化原图
       tvbinxyInit();
       QPointF4 p4; //注意上下左右坐标位置的相对关系，否则可能产生等分异常
       p4.pt1 = QPointF(ui->edtx0->text().toFloat(),ui->edty0->text().toFloat());
       p4.pt2 = QPointF(ui->edtx1->text().toFloat(),ui->edty1->text().toFloat());
       p4.pt3 = QPointF(ui->edtx2->text().toFloat(),ui->edty2->text().toFloat());
       p4.pt4 = QPointF(ui->edtx3->text().toFloat(),ui->edty3->text().toFloat());
       QVector<QLineF> *lines = new QVector<QLineF>();
       QList<QPointF4> *points4 = new QList<QPointF4>();
       int ix = ui->spx->value();
       int iy = ui->spy->value();
       int icount = gfDrawxy4(p4,ix,iy,lines,points4);
       QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinxy->model());
       for (int i=0;i<icount;i++) {
            model->setItem(i,0,new QStandardItem(QString("R%1").arg(i+1)));
            model->setItem(i,1,new QStandardItem(QString::number(points4->at(i).pt1.x(),'f',4)));
            model->setItem(i,2,new QStandardItem(QString::number(points4->at(i).pt1.y(),'f',4)));
            model->setItem(i,3,new QStandardItem(QString::number(points4->at(i).pt2.x(),'f',4)));
            model->setItem(i,4,new QStandardItem(QString::number(points4->at(i).pt2.y(),'f',4)));
            model->setItem(i,5,new QStandardItem(QString::number(points4->at(i).pt3.x(),'f',4)));
            model->setItem(i,6,new QStandardItem(QString::number(points4->at(i).pt3.y(),'f',4)));
            model->setItem(i,7,new QStandardItem(QString::number(points4->at(i).pt4.x(),'f',4)));
            model->setItem(i,8,new QStandardItem(QString::number(points4->at(i).pt4.y(),'f',4)));
            ui->tvbinxy->setModel(model);
            ui->tvbinxy->setColumnWidth(0,90);
            ui->tvbinxy->setColumnWidth(1,50);
            ui->tvbinxy->setColumnWidth(2,50);
            ui->tvbinxy->setColumnWidth(3,50);
            ui->tvbinxy->setColumnWidth(4,50);
            ui->tvbinxy->setColumnWidth(5,50);
            ui->tvbinxy->setColumnWidth(6,50);
            ui->tvbinxy->setColumnWidth(7,50);
            ui->tvbinxy->setColumnWidth(8,50);
       }
       p.begin(&imgcie);
       p.setPen(QPen(Qt::red,1));
       p.drawLines(lines[0]);           //画等分计算后的线
       p.end();
       label->setPixmap(imgcie);
}


void FrmBinxy::on_tvbinxy_clicked(const QModelIndex &index)
{   //点击事件
    return;
    if( ! index.data().toString().isEmpty()){
        QAbstractItemModel *model = ui->tvbinxy->model ();    //通过model获取tableview行数据
        p.begin(&imgcie);
        if(!pointold->isNull()){        //之前 点击过的区域恢复红色显示
            p.setPen(QPen(Qt::red,1));
            p.drawPolygon(pointold,4);
        }
        p.setPen(QPen(Qt::blue,1));    //当前点击的区域，蓝色显示
        QPointF point[] = {             //坐标值是浮点数，
            QPointF(40+(model->index(index.row(),1).data().toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->index(index.row(),2).data().toFloat())/pciexy.ipy), //X0/Y0
            QPointF(40+(model->index(index.row(),3).data().toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->index(index.row(),4).data().toFloat())/pciexy.ipy), //X1/Y1
            QPointF(40+(model->index(index.row(),5).data().toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->index(index.row(),6).data().toFloat())/pciexy.ipy), //X2/Y2
            QPointF(40+(model->index(index.row(),7).data().toFloat()-pciexy.xmin)/pciexy.ipx, 20+(pciexy.ymax- model->index(index.row(),8).data().toFloat())/pciexy.ipy) //X3/Y3
        };
        pointold[0] = point[0];
        pointold[1] = point[1];
        pointold[2] = point[2];
        pointold[3] = point[3];

        p.drawPolygon(point,4);
        p.end();
        label->setPixmap(imgcie);
    }
}

//tvbinxy单元格改变时触发
void FrmBinxy::tvItemChanged()
{

}

void FrmBinxy::on_cbdaba_clicked()
{   //勾选时，可以将主测试页面当前测试的结果打靶在坐标系上
    ui->btnfenji->click();
    if(ui->cbdaba->checkState() == Qt::Checked)
    {   //预览打靶，从mysql数据库testdata数据表中，调出最近半小时内前100个数据，作为打靶预览，数据数量可调

        QString ssql = QString("select CIE_x1,CIE_y1,CIE_x2,CIE_y2,CIE_x3,CIE_y3 from testdata where dtime>=DATE_SUB(NOW(),INTERVAL 15 MINUTE) and station_id=%1 order by id desc limit 100 ").arg(itag);  //倒序，30分钟内最近100条
        QSqlQuery mysql(unitpublic::dbmysql);
        mysql.exec(ssql);       //查询测试流水数据,预览时只取晶片1的xy坐标，正常情况下要进行色坐标分选的基本上是白光
        while (mysql.next()) {
            double x1=mysql.value(0).toDouble();
            double y1=mysql.value(1).toDouble();
            double x2=mysql.value(2).toDouble();
            double y2=mysql.value(3).toDouble();
            double x3=mysql.value(4).toDouble();
            double y3=mysql.value(5).toDouble();
            if((x1>0)&&(y1>0))
                printxy(x1,y1);
            if((x2>0)&&(y2>0))
                printxy(x2,y2);
            if((x3>0)&&(y3>0))
                printxy(x3,y3);
        }
    }
}

void FrmBinxy::on_toolButton_5_clicked()
{   //确认xy分级参数
    ui->spx->setFocus();
    QList<BinXyPkg> lstbinxypkg;
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinxy->model());
    for (int i=0;i<ui->tvbinxy->model()->rowCount();i++) {
       if(model->data(model->index(i,0)).toString().trimmed() != "")
       {    //NAME值不为空则保存，否则放弃
            BinXyPkg binxypkg;
            binxypkg.name = model->data(model->index(i,0)).toString().trimmed();
            binxypkg.pt0 = QPointF(model->data(model->index(i,1)).toFloat(),model->data(model->index(i,2)).toFloat());
            binxypkg.pt1 = QPointF(model->data(model->index(i,3)).toFloat(),model->data(model->index(i,4)).toFloat());
            binxypkg.pt2 = QPointF(model->data(model->index(i,5)).toFloat(),model->data(model->index(i,6)).toFloat());
            binxypkg.pt3 = QPointF(model->data(model->index(i,7)).toFloat(),model->data(model->index(i,8)).toFloat());
            lstbinxypkg.append(binxypkg);
       }
    }
    savebinxytemp();
    emit tvbinparadispxy(irow,lstbinxypkg);
    this->close();
}


bool FrmBinxy::readbinxytemp() //读取自动分级临时表参数
{
    bool result=false;
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("readbinxytemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return false;
    }
    else
    {
        QSqlQuery mysql(mydb);
        if(!mysql.exec(QString("SELECT x0,y0,x1,y1,x2,y2,x3,y3,x_count,y_count FROM binxy_temp where station_id=%1 and led_index=%2").arg(itag).arg(iledindex))) //查询xy分级参数临时表
        {
            unitpublic::gpwritelog(QString("查询自动分级参数临时表 binauto_temp 失败:%1").arg(mydb.lastError().text()));
        }
        else
        {
            while (mysql.next()) {  //mysql.value 对应序号同查询列表字段顺序
                //xy分级临时参数
                ui->edtx0->setText(mysql.value(0).toString());
                ui->edty0->setText(mysql.value(1).toString());
                ui->edtx1->setText(mysql.value(2).toString());
                ui->edty1->setText(mysql.value(3).toString());
                ui->edtx2->setText(mysql.value(4).toString());
                ui->edty2->setText(mysql.value(5).toString());
                ui->edtx3->setText(mysql.value(6).toString());
                ui->edty3->setText(mysql.value(7).toString());
                ui->spx->setValue(mysql.value(8).toInt());
                ui->spy->setValue(mysql.value(9).toInt());
                result = true;
            }

        }
    }
    mydb.close();
    return result;
}

//保存xy分级临时表参数
void FrmBinxy::savebinxytemp()
{
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinxytemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        mysql.exec(QString("delete from binxy_temp where station_id=%1 and led_index=%2").arg(itag).arg(iledindex));
        mysql.exec(QString("insert into binxy_temp (station_id,led_index,x0,y0,x1,y1,x2,y2,x3,y3,x_count,y_count) values (%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%11)")
                   .arg(itag)
                   .arg(iledindex)
                   .arg(ui->edtx0->text().toDouble())
                   .arg(ui->edty0->text().toDouble())
                   .arg(ui->edtx1->text().toDouble())
                   .arg(ui->edty1->text().toDouble())
                   .arg(ui->edtx2->text().toDouble())
                   .arg(ui->edty2->text().toDouble())
                   .arg(ui->edtx3->text().toDouble())
                   .arg(ui->edty3->text().toDouble())
                   .arg(ui->spx->value())
                   .arg(ui->spy->value()));
    }
    mydb.close();
}

void FrmBinxy::on_edtx0_cursorPositionChanged(int arg1, int arg2)
{

}

//坐标系图形处理，itype，0-初始化，1-放大，2-缩小，3-选定区域放大
//x，y：坐标步进值
void FrmBinxy::xyzoom(int itype, double x, double y)
{
    switch (itype) {
    case 0:{    //双击时初始化
        ui->edtminx->setText("0.000");
        ui->edtmaxx->setText("1.000");
        ui->edtminy->setText("0.000");
        ui->edtmaxy->setText("1.000");
        break;
    }
    case 1:{    //点击“放大”
        if((ui->edtminx->text().toFloat()+x)<=1.000) ui->edtminx->setText(QString::number(ui->edtminx->text().toFloat()+x,'f',3)); else ui->edtminx->setText("1.000");
        if((ui->edtmaxx->text().toFloat()-x)>=0.000) ui->edtmaxx->setText(QString::number(ui->edtmaxx->text().toFloat()-x,'f',3)); else ui->edtmaxx->setText("0.000");
        if((ui->edtminy->text().toFloat()+y)<=1.000) ui->edtminy->setText(QString::number(ui->edtminy->text().toFloat()+y,'f',3)); else ui->edtminy->setText("1.000");
        if((ui->edtmaxy->text().toFloat()-y)>=0.000) ui->edtmaxy->setText(QString::number(ui->edtmaxy->text().toFloat()-y,'f',3)); else ui->edtmaxy->setText("0.000");
        break;
    }
    case 2:{    //点击“缩小”
        if((ui->edtminx->text().toFloat()-x)>=0.000) ui->edtminx->setText(QString::number(ui->edtminx->text().toFloat()-x,'f',3)); else ui->edtminx->setText("0.000");
        if((ui->edtmaxx->text().toFloat()+x)<=1.000) ui->edtmaxx->setText(QString::number(ui->edtmaxx->text().toFloat()+x,'f',3)); else ui->edtmaxx->setText("1.000");
        if((ui->edtminy->text().toFloat()-y)>=0.000) ui->edtminy->setText(QString::number(ui->edtminy->text().toFloat()-y,'f',3)); else ui->edtminy->setText("0.000");
        if((ui->edtmaxy->text().toFloat()+y)<=1.000) ui->edtmaxy->setText(QString::number(ui->edtmaxy->text().toFloat()+y,'f',3)); else ui->edtmaxy->setText("1.000");
        break;
    }
    case 3:{    //鼠标选定区域从左上角向右下角放大
        ui->edtminx->setText(QString::number(pciexy.xmin+(moldx)*pciexy.ipx,'f',3));
        ui->edtmaxx->setText(QString::number(pciexy.xmin+(x)*pciexy.ipx,'f',3));
        ui->edtminy->setText(QString::number(pciexy.ymax-(y)*pciexy.ipy,'f',3));
        ui->edtmaxy->setText(QString::number(pciexy.ymax-(moldy)*pciexy.ipy,'f',3));
        break;

//        if(x>=0){   //左移
//            if((ui->edtminx->text().toFloat() + qAbs(x))<=1.000) ui->edtminx->setText(QString::number(ui->edtminx->text().toFloat() + qAbs(x),'f',3)); else ui->edtminx->setText("1.000");
//            if((ui->edtmaxx->text().toFloat() + qAbs(x))<=1.000) ui->edtmaxx->setText(QString::number(ui->edtmaxx->text().toFloat() + qAbs(x),'f',3)); else ui->edtmaxx->setText("1.000");
//        }else{      //右移
//            if((ui->edtminx->text().toFloat() - qAbs(x))>=0.000) ui->edtminx->setText(QString::number(ui->edtminx->text().toFloat() - qAbs(x),'f',3)); else ui->edtminx->setText("0.000");
//            if((ui->edtmaxx->text().toFloat() - qAbs(x))>=0.000) ui->edtmaxx->setText(QString::number(ui->edtmaxx->text().toFloat() - qAbs(x),'f',3)); else ui->edtmaxx->setText("0.000");
//        }
//        if(y>=0){   //上移
//            if((ui->edtminy->text().toFloat() + qAbs(y))<=1.000) ui->edtminy->setText(QString::number(ui->edtminy->text().toFloat() + qAbs(y),'f',3)); else ui->edtminy->setText("1.000");
//           if((ui->edtmaxy->text().toFloat() + qAbs(y))<=1.000) ui->edtmaxy->setText(QString::number(ui->edtmaxy->text().toFloat() + qAbs(y),'f',3)); else ui->edtmaxy->setText("1.000");
//        }else{      //下移
//            if((ui->edtminy->text().toFloat() - qAbs(y))>=0.000) ui->edtminy->setText(QString::number(ui->edtminy->text().toFloat() - qAbs(y),'f',3)); else ui->edtminy->setText("0.000");
//            if((ui->edtmaxy->text().toFloat() - qAbs(y))>=0.000) ui->edtmaxy->setText(QString::number(ui->edtmaxy->text().toFloat() - qAbs(y),'f',3)); else ui->edtmaxy->setText("0.000");
//        }
//        break;
    }
    }
    drawaxis_xy();
    drawaxis_xy4(); //画新四边形
    ui->btnfenji->click();  //分级预览
}

void FrmBinxy::on_toolButton_2_clicked()
{   //放大坐标
    xyzoom(1,0.001,0.001);  //步进固定为 0.001
}

void FrmBinxy::on_toolButton_3_clicked()
{   //缩小坐标
    xyzoom(2,0.001,0.001);  //步进固定为 0.001
}

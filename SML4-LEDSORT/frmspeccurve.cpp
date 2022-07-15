#include "frmspeccurve.h"
#include "ui_frmspeccurve.h"
#include "frmmain.h"
#include "unitpublic.h"
#include <qchart.h>
#include "colormatchingfunctions.h"

FrmSpecCurve::FrmSpecCurve(qint8 iindex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSpecCurve)
{
    ui->setupUi(this);
    itag = iindex;
    isvisable = true;
    this->setWindowTitle(QString("光谱能量分布 - %1#").arg(itag+1));

    this->setGeometry(300+iindex*40,200+iindex*40,this->width(),this->height());    //不同工位的光谱能量图，顺序排列
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);   //进制最大化按钮

    CurveInit();
}

FrmSpecCurve::~FrmSpecCurve()
{
    delete ui;
    switch (itag) {         //析构函数中，将窗口实例变为空
    case ST_INDEX_1:{
        frmmain::frmspec_1 = NULL;
        break;
    }
    case ST_INDEX_2:{
        frmmain::frmspec_2 = NULL;
        break;
    }
    case ST_INDEX_3:{
        frmmain::frmspec_3 = NULL;
        break;
    }
    case ST_INDEX_4:{
        frmmain::frmspec_4 = NULL;
        break;
    }
    }
}

void FrmSpecCurve::CurveInit()
{
    for(int i = 0; i < 401; i ++)   //380-780,一共401个数据
    {
            MyPointf1 << QPointF(i+380,0);
            MyPointf2 << QPointF(i+380,0);
            MyPointf3 << QPointF(i+380,0);
    }

    m_chart = new QChart();
    series1 = new QSplineSeries();//实例化一个QLineSeries对象
    //series1->setColor(QColor(0,100,255));
    series1->setColor(Qt::red);//
    series1->replace(MyPointf1); //初始化数据
    series1->setVisible(true);
    series1->setPointLabelsFormat("(@xPoint,@yPoint)");
    series1->setPointLabelsVisible(false);  //不显示点标签数据

    series2 = new QSplineSeries();//实例化一个QLineSeries对象
    series2->setColor(Qt::green);
    series2->replace(MyPointf1); //初始化数据
    series2->setVisible(true);
    series2->setPointLabelsFormat("(@xPoint,@yPoint)");
    series2->setPointLabelsVisible(false);  //不显示点标签数据

    series3 = new QSplineSeries();//实例化一个QLineSeries对象
    series3->setColor(Qt::blue);
    series3->replace(MyPointf1); //初始化数据
    series3->setVisible(true);
    series3->setPointLabelsFormat("(@xPoint,@yPoint)");
    series3->setPointLabelsVisible(false);  //不显示点标签数据

    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    m_chart->setDropShadowEnabled(true);//背景阴影    m_chart->setAutoFillBackground(true);  //设置背景自动填充
    m_chart->addSeries(series1);//添加系列到QChart上
    m_chart->addSeries(series2);//添加系列到QChart上
    m_chart->addSeries(series3);//添加系列到QChart上

    m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体


    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(380,780);    //默认则坐标为动态计算大小，白光
    //axisX->setLabelFormat("%dS");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,110);    //默认则坐标为动态计算大小的
  //  axisY->setTitleText("value值");

    m_chart->setAxisX(axisX,series1);
    m_chart->setAxisY(axisY,series1);
    m_chart->setAxisX(axisX,series2);
    m_chart->setAxisY(axisY,series2);
    m_chart->setAxisX(axisX,series3);
    m_chart->setAxisY(axisY,series3);
    //m_chart->createDefaultAxes();             //或者创建默认轴

    //修改说明样式
    m_chart->legend()->setVisible(false);   //不显示底部内容
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    m_chart->legend()->setMaximumHeight(50);
    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(chartView);

 //   resize(960, 720);

}

void FrmSpecCurve::SpecDisp(SpecDataPkg specdata,bool bclear)
{
    for(int i = 0; i < 401; i ++)   //380-780,一共401个数据
    {
        if (bclear){
                //清空曲线
            MyPointf1.clear();
            MyPointf2.clear();
            MyPointf3.clear();
        }
                else{
            MyPointf1 << QPointF(i+380,spec_testdata3[i]);   //重画曲线
            MyPointf2 << QPointF(i+380,spec_testdata3[i]);   //重画曲线
            MyPointf3 << QPointF(i+380,spec_testdata3[i]);   //重画曲线
        }
    }
    series1->replace(MyPointf1); //初始化数据
    series2->replace(MyPointf2); //初始化数据
    series3->replace(MyPointf3); //初始化数据
}

//槽函数，接收线程信号，显示光谱曲线
void FrmSpecCurve::mspeccurve(int iindex)
{
    if(iindex == itag){
    MyPointf1.clear();
    MyPointf2.clear();
    MyPointf3.clear();
    for(int i = 0; i < 401; i ++)   //380-780,一共401个数据
        {
            MyPointf1 << QPointF(unitpublic::lstspecdatapkg[itag][LED_1].dx[i],unitpublic::lstspecdatapkg[itag][LED_1].dy[i]);   //重画曲线
            MyPointf2 << QPointF(unitpublic::lstspecdatapkg[itag][LED_2].dx[i],unitpublic::lstspecdatapkg[itag][LED_2].dy[i]);   //重画曲线
            MyPointf3 << QPointF(unitpublic::lstspecdatapkg[itag][LED_3].dx[i],unitpublic::lstspecdatapkg[itag][LED_3].dy[i]);   //重画曲线
        }
        series1->replace(MyPointf1); //初始化数据
        series2->replace(MyPointf2); //初始化数据
        series3->replace(MyPointf3); //初始化数据
    }
}

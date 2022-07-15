#ifndef UNITPUBLIC_H
#define UNITPUBLIC_H
#include <QTime>
#include <QPointF>
#include <qwidget.h>
#include <qitemdelegate.h>
#include <qsqldatabase.h>


//公共参数

const int FUN_TESTDATA  = 1;    //测试数据页面
const int FUN_BASESET   = 2;        //基本设置页面
const int FUN_BINSET    = 3;        //分级设置页面
const int FUN_VERIFY    = 4;        //校准页面
const int FUN_SYSTEM    = 5;        //系统设置

const int ST_INDEX_1    = 0;    //测试工位1
const int ST_INDEX_2    = 1;    //测试工位2
const int ST_INDEX_3    = 2;    //测试工位3
const int ST_INDEX_4    = 3;    //测试工位4
const int ST_COUNT      = 4;    //测试工位数量，默认4，最大也是4

const int LED_1 = 0;    //晶1
const int LED_2 = 1;    //晶2
const int LED_3 = 2;    //晶3

const int ITEMBIN_COUNT = 50;  //单项参数最大分BIN数量
const int LED_COUNT     = 3;    //LED晶片数量,最大3，默认3
const int TESTITEM_COUNT= 12;    //测试项目数量，默认12

const int CMD_TEST_DONE   =0;   //命令执行完毕
const int CMD_TEST_STEP   =1;       //单步测试命令，测试线程中判断收到单步测试命令时，只执行一次测试
//const int CMD_TEST_INIT   =2;       //导入参数等初始化命令
//const int CMD_TEST_AUTO   =3;       //自动连续运行命令

const QString REG_KEY_SN = "sml-ledsort-1";  //产品序列号，DES密匙
const QString REG_KEY_CODE = "sml-ledsort-2";  //产品注册码，DES密匙

const int VALID_INT = 1;        //有效数字
const int VALID_REAL = 2;       //有效浮点数

const int ELEVEL_HIGH = 1;      //高电平
const int ELEVEL_LOW  = 0;      //低电平
const int BINOUT_HIGH    = 1;   //bin号，输出信号，高位 bit 8-15
const int BINOUT_LOW     = 0;   //bin号，输出信号，低位 bit 0-7
//光色电测试结果，数据结构元素与lstTestItemName保持一致
//lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
struct TestDataPkg{
    double VF=0;
    double VFL=0;
    double IR=0;
    double IV=0;
    double WD=0;
    double WP=0;
    double Ra=0;
    double CCT=0;
    double CIE_x=0;
    double CIE_y=0;
    double SDCM=0;
    double R9=0;

    //以上参数晶1、2、3分别存储，即结果不一样
    //以下参数晶1、2、3结果一样，属于该LED共同属性，值放在晶1位置
    int binid=0;    //BIN号
    QString pol = "+";  //极性： +，-
    bool testresult = false;    //测试结果，OK、NG
    int testdataid = 0; //测试数据流水号，用于测试界面显示
} ;

//测试系统性能统计信息
struct TestTjSysPkg{
    double uph;
};

//测试参数统计数据，数据结构元素与lstTestItemName保持一致
struct TestDataSumPkg{
    double maxdata=0;     //最大值
    double mindata=99999999;     //最小值
    double sumdata=0;       //累计值，用于计算平均值
    double avgdata=0;     //平均值
    double ngcount=0;     //NG数量
    double ngpercent=0;   //NG比例
};

//工位测试统计数据
struct StationSumPkg{
    double uph=0; //UPH
    int sumcount=0;         //累计产量
    int valcount=0;         //有效产量
    int bincount[256]={0};      //每BIN累计数量
    double binpercent[256]={0}; //每BIN占比
};

//光谱仪结构数据,SML_GetAllSSPDHWTRG
struct SpecDataPkg{
    double pPara[4];  // 色坐标修正值 m_CIEx_k = pPara[0];m_CIEx_b = pPara[1];m_CIEy_k = pPara[2];m_CIEy_b = pPara[3];
    double dx[401];     //波长 400 个值[380~780]
    double dy[401];      //采样值 400 个值
    double dss[2048];     // 2048 个原始采样值
};

//赛美蓝光谱仪测试结果数据,SML_GetAllTestParaSPDPLUS
struct smlSpecDataPkg{
    double m_dPeakValuePI=0; //峰值
    double m_dTotalEnergy_EX=0; //总能量
    double m_dPeakValueWavelengh=0;//峰值波长
    double m_dPeakValueBandwidth=0;//峰值带宽
    double m_dLuminousFlux=0;//光通量
    double m_dRadiationFlux=0;//辐射通量
    double m_dPe=0;//色纯度
    double m_dTc=0;//色温
    double m_dx=0;//色坐标(x,y),(u,v)
    double m_dy=0;
    double m_du=0;
    double m_dv=0;
    double m_dDomWavelengh=0;//主波长
    double m_dRa=0;//显色指数
    double m_dR0=0;
    double m_dR1=0;
    double m_dR2=0;
    double m_dR3=0;
    double m_dR4=0;
    double m_dR5=0;
    double m_dR6=0;
    double m_dR7=0;
    double m_dR8=0;
    double m_dR9=0;
    double m_dR10=0;
    double m_dR11=0;
    double m_dR12=0;
    double m_dR13=0;
    double m_dR14=0;
    double m_dRR=0;//红色比
    double m_dGR=0;//绿色比
    double m_dBR=0;//蓝色比
    double m_nMaxSpectrumSample=0;//最大光谱采样值
    double m_dX=0;//X
    double m_dY=0;//Y
    double m_dZ=0;//Z
    double m_dRf=0;//
    double m_dRg=0;//
};

//XY分级参数，四边形区域
struct BinXyPkg{
    QString name;   //BIN名
    QPointF pt0;    //四边形左上角坐标值
    QPointF pt1;    //
    QPointF pt2;    //
    QPointF pt3;    //
};

//公差、公比分级参数，IV\VF等...，临时参数
struct BinVfPkg{    //VF参数
    QString name;  //BIN名
    double fbegin;    //电压值良品上限
    double fend;    //电压值良品下限
};

struct PolyXy{
    double x[30]={0};     //最多支持30个值参与标定
    double y[30]={0};     //最多支持30个值参与标定
    double beta[8]={0};   //最多支持8级
};

//  function polyfit(n,p:integer;var polyxy:Tpolyxy):integer;stdcall;external 'polyfit.dll' name 'polyfit';
typedef int(Polyfit)(int n,int p,PolyXy *polyxy);  //多项拟合函数DLL库

class unitpublic
{
public:
    unitpublic();

public:
    static QString gsCurPath;      //当前路径，全局变量，必须要用 static 声明， 且如果放在类中定义，其他类访问时容易报错
    static int gicurindex;          //当前工位序号,1-4
    static int gicurfun[4];        //保存对应工位的当前功能页面，测试，基本设置，校准，

    static qint8 gpwritelog(QString stxt);   //写日志
    static void readsyspara(QString sfilename);    //初始化主参数，即从ini配置文件中读取设置
    static QString gscurprofile;    //当前工程文件(*.db3)名称

    static bool mthdsuspended[ST_COUNT];  //线程挂起标志，由外部设置改变这个变量，线程判断这个变量为true则进入死循环，sleep，一直到这个状态被外部设置为false才恢复继续执行run任务
    static bool mthdsuspendok[ST_COUNT];  //线程挂起成功标志，当线程进入挂起死循环时该状态为true，其他线程可以根据这个true状态判断线程确实被挂起后才开始执行自己的任务
    static bool mthdstarted[ST_COUNT];      //线程是否已经启动

    static bool stenable[ST_COUNT];    //测试工位是否启用
    static int iruntime[ST_COUNT];       //各测试工位程序启动到现在的持续运行时间
    static TestDataPkg lsttestdatapkg[ST_COUNT][LED_COUNT];                         //各工位对应每个晶片当前测试的光色电测试结果数据
    static TestDataSumPkg lsttestdatasumpkg[ST_COUNT][LED_COUNT][TESTITEM_COUNT];   //各工位对应每个晶片当前测试的光色电各测试结果统计数据
    static SpecDataPkg lstspecdatapkg[ST_COUNT][LED_COUNT];                         //各工位对应每个晶片当前测试的光谱能量数据
    static smlSpecDataPkg lstsmlspecdatapkg[ST_COUNT][LED_COUNT];                   //各工位对应每个晶片当前测试的光谱色参数数据
    static BinXyPkg lstbinxypkg[ST_COUNT][LED_COUNT][ITEMBIN_COUNT];
    static int testcmd[ST_COUNT];       //测试命令:单步、自动
    static StationSumPkg lststationsumpkg[ST_COUNT];    //工位统计数据

    static int StringListToTxt(QString filename,QStringList lsttxt);   //QstringList列表数据保存到文本文件
    static int TxtToStringList(QString filename,QStringList &lsttxt);   //文本文件读入到QstringList列表数据

    static QSqlDatabase dbmysql;    //Mysql数据库连接对象，mysql主要存储操作员信息、测试历史数据
    static QSqlDatabase dblstmysql[ST_COUNT];   //避免多线程利用一个连接同时处理事物
    static QString gsuser;          //当前登录用户名

    static QString gssoftsn;        //软件序列号
    static QString gsregcode;       //软件注册码
    static int giregstauts;         //软件注册状态

    static int softisreg(QString scode);   //判断软件是否注册，参数scode为注册码
    static QString getsoftsn(QString sn); //获取序列号
    static bool regExpCheck(int nType,QString strValue);
    static QPixmap createQRCode(const QString &text,int nsize);

    //获取BIN参数，用来打印标签
    static int getbinpara(int iindex,int binid,QString &binpara);
    static QSqlDatabase dblstmem[ST_COUNT];    //内存数据库，每个线程单独

    static bool bmachine[ST_COUNT];   //是否连接测试标志，
    static void filedb2memdb(int iindex);      //将本地数据库转移至内存数据库
};

//设置tableview某列不可编辑，建立委托
class ReadOnlyDelegate: public QItemDelegate    // 注意，需要 #include <qitemdelegate.h>
{

public:
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent)
    {    }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override //final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }
};




#endif // UNITPUBLIC_H

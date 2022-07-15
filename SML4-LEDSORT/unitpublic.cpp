//公共变量、函数、过程
#include "unitpublic.h"
#include "qsettings.h"
#include "qfile.h"
#include "qtextstream.h"
#include "unitprofile.h"
#include "DES.h"
#include "QRCode/qrencode.h"
#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qdebug.h"

unitpublic::unitpublic()
{

}

QString unitpublic::gsCurPath = ""; //当前路径
int unitpublic::gicurindex  = ST_INDEX_1;    //当前工位序号，默认1
int unitpublic::gicurfun[4] = {FUN_TESTDATA,FUN_TESTDATA,FUN_TESTDATA,FUN_TESTDATA};    //当前页面，默认4个工位初始都是测试数据页面
QString unitpublic::gscurprofile = "";  //当前工程文件名称，程序启动后必须先指定工程文件，才可以开始测试
bool  unitpublic::mthdsuspended[ST_COUNT]={false,false,false,false};  //主线程挂起标志，默认为否
bool  unitpublic::mthdsuspendok[ST_COUNT]={false,false,false,false};    //对应到4个测试工位的线程状态，是否挂起
bool unitpublic::mthdstarted[ST_COUNT]={false,false,false,false};      //线程是否已经启动
bool unitpublic::stenable[ST_COUNT]={true,true,true,true};    //测试工位是否启用，默认都启用
            //线程构造函数中会先调用一次初始化任务，所以该变量初始为false，到中途暂停测试后加载或设置新参数时为true，则再次执行初始化
int unitpublic::testcmd[ST_COUNT] = {CMD_TEST_DONE,CMD_TEST_DONE,CMD_TEST_DONE,CMD_TEST_DONE};  //测试命令，默认自动运行，非自动运行命令都在线程挂起过程中执行
int unitpublic::iruntime[ST_COUNT]={0,0,0,0};                   //程序启动到现在的持续运行时间，暂停测试时清零
TestDataPkg unitpublic::lsttestdatapkg[ST_COUNT][LED_COUNT];         //各工位对应每个晶片当前测试的光色电测试结果数据
TestDataSumPkg unitpublic::lsttestdatasumpkg[ST_COUNT][LED_COUNT][TESTITEM_COUNT];   //各工位对应每个晶片当前测试的光色电各测试结果统计数据
SpecDataPkg unitpublic::lstspecdatapkg[ST_COUNT][LED_COUNT];         //各工位对应每个晶片当前测试的光谱能量数据
smlSpecDataPkg unitpublic::lstsmlspecdatapkg[ST_COUNT][LED_COUNT];   //各工位对应每个晶片当前测试的光谱色参数数据
BinXyPkg unitpublic::lstbinxypkg[ST_COUNT][LED_COUNT][ITEMBIN_COUNT];//xy自动分级临时参数
StationSumPkg unitpublic::lststationsumpkg[ST_COUNT];    //工位统计数据
QSqlDatabase unitpublic::dbmysql;   //Mysql连接
QSqlDatabase unitpublic::dblstmysql[ST_COUNT];  //多个连接池，避免跨线程事物处理
QString unitpublic::gsuser;     //当前登录用户
QString unitpublic::gssoftsn;        //软件序列号
QString unitpublic::gsregcode;       //软件注册码
int unitpublic::giregstauts=0;         //软件注册状态，默认未注册
bool unitpublic::bmachine[ST_COUNT]={true};     //默认联机测试，联机测试时，软件需要判断机台SOT信号进行交互测试
QSqlDatabase unitpublic::dblstmem[ST_COUNT];

//初始化参数,从ini文件sfilename中读取
void unitpublic::readsyspara(QString sfilename)
{
    QSettings settings(sfilename,QSettings::IniFormat); //
    unitpublic::gscurprofile = settings.value("system/profile","").toString();  //获取当前工程文件名，默认为空
    for(int i=0;i<ST_COUNT;i++){    //读取测试工位是否启用
        unitpublic::stenable[i] = settings.value(QString("system/station%1").arg(i+1),true).toBool();   //注意，序号的下标，配置文件中从1-4，对应程序中的0-3
    }
    unitpublic::gsregcode = settings.value("system/regcode","").toString(); //获取注册码
}

//写日志
qint8 unitpublic::gpwritelog(QString stxt)
{
    QString sfilename = "ledsort.log";      //ini配置文件，
    QFile f(unitpublic::gsCurPath+"/"+sfilename);   //配置文件在当前路径下
    if(f.size()>5000000)
    {
        f.remove();     //文件大于5M则删除
    }

    if(!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {       //注意：观察发现这样 QFile打开文件会导致缓存(buff/cache)不断增加，只有当文件删除时候才会释放
        //可以增加QIODevice::Unbuffered来避免内存消耗，但这个方式写磁盘文件的效率会降低
        //考虑到我们的日志文件只保存2M大小后自动删除，所以先不考虑缓存增加及内存消耗的问题，反正删除文件后会释放内存
        return -1;  //创建或打开文件失败
    }

    QTextStream txtOutput(&f);
    txtOutput << QString("[%1:]%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(stxt)<< endl;
    f.close();
    return 1;
}

//QstringList列表数据保存到文本文件
int unitpublic::StringListToTxt(QString filename,QStringList lsttxt)
{
    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {   return -1;  //创建或打开文件失败
    }

    QTextStream txtOutput(&f);
    for(int i=0;i<lsttxt.count();i++)
        txtOutput << lsttxt.at(i) << endl;
    f.close();
    return 1;   //写文件成功
}

//文本文件读入到QstringList列表数据
int unitpublic::TxtToStringList(QString filename, QStringList &lsttxt)
{
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {   return -1;  //打开文件失败
    }

    QTextStream txtInput(&f);
    while(!txtInput.atEnd())
       lsttxt.append(txtInput.readLine());
    f.close();
    return 1;   //读文件成功

}
//获取序列号
//传入参数，sn=硬件序号参数
QString unitpublic::getsoftsn(QString sn)
{
    unitpublic::gssoftsn = EncodeMain(sn,REG_KEY_SN);  //软件产品序列号
    return unitpublic::gssoftsn;
}
//判断软件是否注册
int unitpublic::softisreg(QString scode)
{
    QString s1 = EncodeMain(unitpublic::gssoftsn,REG_KEY_CODE); //序列号加密
    if(s1==scode){
        unitpublic::giregstauts = 1;
        return 1;       //注册成功，返回1
    }else{
        unitpublic::giregstauts = 0;
        return 0;
    }
}


/***************************************************************************
*breif：strValue有效性判断
*param：nType [in] 有效性的类型(实数/整数等等 此处只做了整数与小数的判断)
*param:	strValue [in] 需要判断的内容
*return: 如果strValue 符合该类型的正则表达式 则返回ture
****************************************************************************/
bool unitpublic::regExpCheck(int nType,QString strValue)
{
    bool bRet = true;
    switch (nType)	{
    case VALID_INT:{
        QRegExp reg("^[-?\\d+]?\\d*$");
        QRegExpValidator validator(reg,0);
        int pos = 0;
        if(QValidator::Acceptable!=validator.validate(strValue,pos)){
//            strInfo += QString(":请输入数字!");
            bRet = false;
        }
        break;}
    case VALID_REAL:{
        QRegExp reg("^-?\\d+(\\.\\d+)?$");
        QRegExpValidator validator(reg,0);
        int pos = 0;
        if (QValidator::Acceptable!=validator.validate(strValue,pos)){
//            strInfo += QString(":请输入实数!");
            bRet = false;
        }
        break;}
    }

    return bRet;
}

//生成二维码图片
//传入参数：text，二维码文字内容
//          nsize，图片大小
//返回：QPixmap图片
QPixmap unitpublic::createQRCode(const QString &text,int nsize)
{
    int margin = 2;
    if (text.length() == 0)
    {
        return QPixmap();
    }
    QRcode *qrcode = QRcode_encodeString(text.toLocal8Bit(), 2, QR_ECLEVEL_L, QR_MODE_8, 0);
    if (qrcode == NULL) {
        return QPixmap();
    }
    unsigned char *p, *q;
    p = NULL;
    q = NULL;
    int x, y, bit;
    int realwidth;

    realwidth = qrcode->width;
    QImage image = QImage(realwidth, realwidth, QImage::Format_Indexed8);
    QRgb value;
    value = qRgb(255,255,255);
    image.setColor(0, value);
    value = qRgb(0,0,0);
    image.setColor(1, value);
    image.setColor(2, value);
    image.fill(0);
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++)
    {
        bit = 7;
        q += margin / 8;
        bit = 7 - (margin % 8);
        for(x=0; x<qrcode->width; x++)
        {
            if ((*p & 1) << bit)
                image.setPixel(x, y, 1);
            else
                image.setPixel(x, y, 0);
            bit--;
            if(bit < 0)
            {
                q++;
                bit = 7;
            }
            p++;
        }
    }
    return QPixmap::fromImage(image.scaledToWidth(nsize));
}

//获取BIN参数，用来打印标签
//传入参数：iindex，工位序号
//          binid，BIN号
    //    返回参数：binpara，该BIN参数
    //      return，1表示返回成功，0则失败
int unitpublic::getbinpara(int iindex,int binid,QString &binpara)
{
    int result = 0;     //初始化0

    QString spara = "";

    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    mydb.open();
    QSqlQuery mysql(mydb);

    QString ssql = QString("select  bin_number,bin_name,bin_memo from binset_para where station_id=%1 and bin_number=%2").arg(iindex).arg(binid);
    mysql.exec(ssql);
    if(mysql.next())
        spara = QString("BIN:%1 \rNAME:%2 \rMEMO:%3 \r").arg(mysql.value(0).toInt()).arg(mysql.value(1).toString()).arg(mysql.value(2).toString());

    for(int i=0;i<LED_COUNT;i++){   //三晶
        for(int k=0;k<TESTITEM_COUNT;k++){  //测试参数
            if(unitprofile::testitempara[iindex][i][k].bin_enable){   //参与分级
                switch (k) {//lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
                case 0:{    //VF
                    QString ssql = QString("select  VF%1_MIN,VF%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("VF%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',3)).arg(QString::number(mysql.value(1).toDouble(),'f',3));
                    break;
                    }
                case 1:{    //VFL
                    QString ssql = QString("select  VFL%1_MIN,VFL%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("VFL%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',3)).arg(QString::number(mysql.value(1).toDouble(),'f',3));
                    break;
                    }
                case 2:{    //IR
                    QString ssql = QString("select  IR%1_MIN,IR%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("IR%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',3)).arg(QString::number(mysql.value(1).toDouble(),'f',3));
                    break;
                    }
                case 3:{    //IV
                    QString ssql = QString("select  IV%1_MIN,IV%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("IV%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',2)).arg(QString::number(mysql.value(1).toDouble(),'f',2));
                    break;
                    }
                case 4:{    //WD
                    QString ssql = QString("select  WD%1_MIN,WD%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("WD%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                case 5:{    //WP
                    QString ssql = QString("select  WP%1_MIN,WP%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("WP%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                case 6:{    //Ra
                    QString ssql = QString("select  Ra%1_MIN,Ra%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("Ra%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                case 7:{    //CCT
                    QString ssql = QString("select  CCT%1_MIN,CCT%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("CCT%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                case 8:{    //CIE_x ，
                    QString ssql = QString("select  binxy%1_name from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("xy%1:%2 \r").arg(i+1).arg(mysql.value(0).toString());
                    break;
                    }
                case 9:{    //CIY_y ，暂不处理
                    break;
                    }
                case 10:{    //SDCM
                    QString ssql = QString("select  SDCM%1_MIN,SDCM%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("SDCM%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                case 11:{    //R9
                    QString ssql = QString("select  R9%1_MIN,R9%1_MAX from binset_para where station_id=%2 and bin_number=%3").arg(i+1).arg(iindex).arg(binid);
                    mysql.exec(ssql);
                    if(mysql.next())
                        spara = spara + QString("R9%1:%2 - %3 \r").arg(i+1).arg(QString::number(mysql.value(0).toDouble(),'f',1)).arg(QString::number(mysql.value(1).toDouble(),'f',1));
                    break;
                    }
                }
            }
        }
    }
    binpara = spara;        //返回该BIN参数
    mydb.close();
    return 1;
}

//创建 内存数据库，提高查询效率，每次更新关键配置时，都需要更新内存数据库
void unitpublic::filedb2memdb(int iindex)
{       //
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）

    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("filedb2memdb,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QStringList tables = mydb.tables();
        mydb.close();

        if(!unitpublic::dblstmem[iindex].isOpen())
        {
        if(QSqlDatabase::contains(QString("MEMORY%1").arg(iindex)))
            unitpublic::dblstmem[iindex] = QSqlDatabase::database(QString("MEMORY%1").arg(iindex));//在不同的线程中，连接名一定要区分独立开，否则异常,不管是本地文件还是内存数据库
        else
            unitpublic::dblstmem[iindex] = QSqlDatabase::addDatabase("QSQLITE",QString("MEMORY%1").arg(iindex));
        }

        unitpublic::dblstmem[iindex].setDatabaseName(":memory:");  //内存数据库
        unitpublic::dblstmem[iindex].open();

        QSqlQuery query(unitpublic::dblstmem[iindex]);
        query.exec(QString("attach database '%1' as srcdb;").arg(unitpublic::gscurprofile));    //源表

        for(int i=0;i<tables.count();i++){
            QString name = tables.at(i);
            if((name=="binset_para") || (name=="verify_para") || (name=="system_cfg") )
            {   //内存数据库中只保留分级参数表和校准参数表即可,binset_para,verify_para,system_cfg
                QString sql = QString("create table %1 as select * from srcdb.%2;").arg(name).arg(name);        //创建表
                query.exec(sql);
            }
        }
    query.exec("detach database srcdb;");
    }
//    unitpublic::dblstmem[iindex].close();   //数据库不要关闭，内存数据库关闭后自动销毁
}


//   工程文件管理模块
//各项测试参数处理

#include "unitpublic.h"
#include "unitprofile.h"
#include "QSqlError"
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <qdebug.h>

BaseSetPara unitprofile::basesetpara[ST_COUNT];   //各工位对应基本参数设置,1..4工位
TestItemPara unitprofile::testitempara[ST_COUNT][LED_COUNT][TESTITEM_COUNT]; //三维数组，分别对应测试工位(1..4)、晶片序号(1..3)、10个测试项目
//BinItemPara unitprofile::binitempara[ST_COUNT][LED_COUNT][ITEMBIN_COUNT] ; //三维数组，，分别对应测试工位、晶片序号、最多50个测试项目分bin参数
PolPara unitprofile::polpara[ST_COUNT]; //POL极性判断参数列表，分别对应四个测试工位

unitprofile::unitprofile()
{

}

//读取工程文件
void unitprofile::readprofile(QString filename)
{
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");

//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");   //数据库连接组件
    mydb.setDatabaseName(filename);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("打开工程文件失败:%1").arg(mydb.lastError().text()));
    }
    else
    {
        QSqlQuery mysql(mydb);
        //读基本设置参数表 system_cfg
        if(!mysql.exec(QString("SELECT station_id,led_type,spec_jftime,spec_ystime,sdcm_type,auto_print,bin_maxcount,qrcode_size,binout_default,sot_bit,sot_type,eot_binout,eot_bit,eot_type FROM system_cfg"))) //查询基本设置参数表
        {
            unitpublic::gpwritelog(QString("查询基本设置参数表 system_cfg 失败:%1").arg(mydb.lastError().text()));
        }
        else
        {
            while (mysql.next()) {  //mysql.value 对应序号同查询列表字段顺序
                int st_id = mysql.value(0).toInt();     //测试工位
                unitprofile::basesetpara[st_id].led_type = mysql.value(1).toInt();      //led_type
                unitprofile::basesetpara[st_id].spec_jftime = mysql.value(2).toInt();   //spec_jftime
                unitprofile::basesetpara[st_id].spec_ystime = mysql.value(3).toInt();   //spec_ystime
                unitprofile::basesetpara[st_id].sdcm_type = mysql.value(4).toInt();     //sdcm_type
                unitprofile::basesetpara[st_id].auto_print = mysql.value(5).toBool();
                unitprofile::basesetpara[st_id].bin_maxcount = mysql.value(6).toInt();
                unitprofile::basesetpara[st_id].qrcode_size = mysql.value(7).toInt();
                unitprofile::basesetpara[st_id].binout_default = mysql.value(8).toInt();
                unitprofile::basesetpara[st_id].sot_bit=mysql.value(9).toInt();
                unitprofile::basesetpara[st_id].sot_type=mysql.value(10).toInt();
                unitprofile::basesetpara[st_id].eot_binout=mysql.value(11).toInt();
                unitprofile::basesetpara[st_id].eot_bit=mysql.value(12).toInt();
                unitprofile::basesetpara[st_id].eot_type=mysql.value(13).toInt();
            }
        }
        //读POL极性设置参数表 pol_para
        if(!mysql.exec(QString("SELECT station_id,time_delay,vf,ma,vfmax,vfmin FROM pol_para"))) //查询POL极性设置参数表
        {
            unitpublic::gpwritelog(QString("查询POL极性设置参数表 pol_para 失败:%1").arg(mydb.lastError().text()));
        }
        else
        {
            while (mysql.next()) {  //mysql.value 对应序号同查询列表字段顺序
                int st_id = mysql.value(0).toInt();     //测试工位
                unitprofile::polpara[st_id].time_delay = mysql.value(1).toInt();
                unitprofile::polpara[st_id].vf = mysql.value(2).toDouble();
                unitprofile::polpara[st_id].ma = mysql.value(3).toDouble();
                unitprofile::polpara[st_id].vfmax = mysql.value(4).toDouble();
                unitprofile::polpara[st_id].vfmin = mysql.value(5).toDouble();
            }
        }

        //读测试项目参数表 test_item
        if(!mysql.exec(QString("SELECT station_id,led_index,item_name,test_enable,bin_enable,verify_type,vf_val,if_val,ok_max,ok_min,time_delay,time_opt,range_iv,bin_out FROM test_item order by station_id,led_index"))) //查询基本设置参数表，注意排序
        {
            unitpublic::gpwritelog(QString("查询测试项目参数表 test_item 失败:%1").arg(mydb.lastError().text()));
        }
        else
        {   //查询不到结果时，为默认值
            while (mysql.next()) {
                int st_id = mysql.value(0).toInt();     //测试工位，1、2、3、4
                int led_id = mysql.value(1).toInt();    //led序号，晶1、2、3
                QString sname = mysql.value(2).toString();
                int name_id = lstTestItemName.indexOf(mysql.value(2).toString());//测试项目名称，VF、IV。。。对应序号
                unitprofile::testitempara[st_id][led_id][name_id].test_enable = mysql.value(3).toBool();    //主界面测试流水表中是否显示该列
                unitprofile::testitempara[st_id][led_id][name_id].bin_enable = mysql.value(4).toBool();    //是否分级
                unitprofile::testitempara[st_id][led_id][name_id].verify_type = mysql.value(5).toInt();    //校准方式
                unitprofile::testitempara[st_id][led_id][name_id].vf_val = mysql.value(6).toDouble();    //电压
                unitprofile::testitempara[st_id][led_id][name_id].if_val = mysql.value(7).toDouble();    //电流
                unitprofile::testitempara[st_id][led_id][name_id].ok_max = mysql.value(8).toDouble();    //良品上限
                unitprofile::testitempara[st_id][led_id][name_id].ok_min = mysql.value(9).toDouble();    //良品下限
                unitprofile::testitempara[st_id][led_id][name_id].time_delay = mysql.value(10).toInt();    //测试延时
                unitprofile::testitempara[st_id][led_id][name_id].time_opt = mysql.value(11).toInt();    //光谱积分
                unitprofile::testitempara[st_id][led_id][name_id].range_iv = mysql.value(12).toInt();    //亮度量程

                unitprofile::testitempara[st_id][led_id][name_id].bin_out = mysql.value(13).toInt();    //该参数超出上下限范围的等外BIN号
                if((mysql.value(13).toInt()<1)||(mysql.value(13).toInt()>256)){
                    unitprofile::testitempara[st_id][led_id][name_id].bin_out = 255;    //等外bin默认255号
                }
            }
        }
        mydb.close();
    }
}

//写工程文件
void unitprofile::saveprofile(QString filename)
{
    int index = unitpublic::gicurindex;
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");   //数据库连接组件
    mydb.setDatabaseName(filename);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("保存工程文件失败:%1").arg(mydb.lastError().text()));
    }
    else
    {
        QSqlQuery mysql(mydb);

        //写基本设置参数表 system_cfg
        mysql.exec(QString("delete from system_cfg where station_id=%1").arg(index));   //先删除当前工位的基本参数
        QString ssql= QString("insert into system_cfg (station_id,led_type,spec_jftime,spec_ystime,sdcm_type,auto_print,bin_maxcount,qrcode_size,binout_default,sot_bit,sot_type,eot_binout,eot_bit,eot_type) values (%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14)")
                   .arg(index)                                          //工位序号
                   .arg(unitprofile::basesetpara[index].led_type)       //led类型
                   .arg(unitprofile::basesetpara[index].spec_jftime)    //光谱测试积分时间
                   .arg(unitprofile::basesetpara[index].spec_ystime)    //光谱测试延时时间
                   .arg(unitprofile::basesetpara[index].sdcm_type)
                   .arg(unitprofile::basesetpara[index].auto_print)
                   .arg(unitprofile::basesetpara[index].bin_maxcount)
                   .arg(unitprofile::basesetpara[index].qrcode_size)
                   .arg(unitprofile::basesetpara[index].binout_default)
                   .arg(unitprofile::basesetpara[index].sot_bit)
                   .arg(unitprofile::basesetpara[index].sot_type)
                   .arg(unitprofile::basesetpara[index].eot_binout)
                   .arg(unitprofile::basesetpara[index].eot_bit)
                   .arg(unitprofile::basesetpara[index].eot_type)
                   ;
        mysql.exec(ssql);

        //写POL极性判断设置参数表 pol_para
        mysql.exec(QString("delete from pol_para where station_id=%1").arg(index));   //先删除当前工位的POL极性设置参数
        mysql.exec(QString("insert into pol_para (station_id,time_delay,vf,ma,vfmax,vfmin) values (%1,%2,%3,%4,%5,%6)")
                   .arg(index)                                          //工位序号
                   .arg(unitprofile::polpara[index].time_delay)       //延时
                   .arg(unitprofile::polpara[index].vf)    //电压
                   .arg(unitprofile::polpara[index].ma)    //电流
                   .arg(unitprofile::polpara[index].vfmax)  //电压上限
                   .arg(unitprofile::polpara[index].vfmin));    //电压下限

        //写测试项目参数表 test_item
        mysql.exec(QString("delete from test_item where station_id=%1").arg(index));   //先删除当前工位的测试项目参数
        for(int ledid=0;ledid<3;ledid++){
            for(int i=0;i<TESTITEM_COUNT;i++){
                QString ssql = QString("insert into test_item (station_id,led_index,item_name,test_enable,bin_enable,verify_type,vf_val,if_val,ok_max,ok_min,time_delay,time_opt,range_iv,bin_out ) values (%1,%2,'%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14)")
                        .arg(index)
                        .arg(ledid)
                        .arg(lstTestItemName[i])
                        .arg(unitprofile::testitempara[index][ledid][i].test_enable)
                        .arg(unitprofile::testitempara[index][ledid][i].bin_enable)
                        .arg(unitprofile::testitempara[index][ledid][i].verify_type)
                        .arg(unitprofile::testitempara[index][ledid][i].vf_val)
                        .arg(unitprofile::testitempara[index][ledid][i].if_val)
                        .arg(unitprofile::testitempara[index][ledid][i].ok_max)
                        .arg(unitprofile::testitempara[index][ledid][i].ok_min)
                        .arg(unitprofile::testitempara[index][ledid][i].time_delay)
                        .arg(unitprofile::testitempara[index][ledid][i].time_opt)
                        .arg(unitprofile::testitempara[index][ledid][i].range_iv)
                        .arg(unitprofile::testitempara[index][ledid][i].bin_out);
                mysql.exec(ssql);
            }
        }
        mydb.close();
    }

}

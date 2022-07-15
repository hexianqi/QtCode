//工程文件管理模块，工程文件以sqlite数据库文件（*.db3）存储
#ifndef UNITPROFILE_H
#define UNITPROFILE_H
#include "unitpublic.h"



//基本设置参数结构
struct BaseSetPara{ //数据存储在 system_cfg 表中
    int led_type = 1;        //LED类型，0:2脚1晶;1:4脚2晶共阳;2:4脚2晶共阴;3:4脚3晶共阳;4:4脚3晶共阴;5:6脚1晶;6:6脚3晶
    int spec_jftime = 5;    //光谱仪测试积分时间 ，暂时不用
    int spec_ystime = 3;    //光谱仪测试延时时间，暂时不用
    int sdcm_type   = 1;  //SDCM标准，0:ANSI_F6500;1:ANSI_F5700;2:ANSI_F5000;3:ANSI_F4500;4:ANSI_F4000;5:ANSI_F3500;6:ANSI_F3000;7:ANSI_F2700;8:IEC_F6500;9:IEC_F5000;10:IEC_F4000;11:IEC_F3500;12:IEC_F3000;13:IEC_F2700;
    bool auto_print = false;    //是否满料后自动打印标签
    int bin_maxcount = 3000;    //BIN满料数量
    int qrcode_size = 80;       //二维码图片尺寸大小（像素）
    int binout_default      = 255;      //默认等外BIN，当单项参数测试值都在上下限范围内，但不在有效分级参数内的，划分到默认等外BIN
    int sot_bit = 0;        //机台SOT信号输入端口号（bit 0-15），默认bit0
    int sot_type = ELEVEL_HIGH;       //SOT输入信号，有效电平，默认高电平有效
    int eot_binout = BINOUT_LOW;    //bin号输出端口号，默认低8位，bit 0-7
    int eot_bit = 15;       //EOT信号输出端口号，当bin号是低8位时，EOT取值范围是8-15，否则0-7
    int eot_type = ELEVEL_HIGH;     //EOT信号，默认端口输出高电平有效
};

//测试项目名称列表，暂时固定12个测试项目，后续如果有新增，直接这里增加即可
const QStringList lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
const QStringList lstledtype = {"2脚1晶","4脚2晶","4脚3晶共阳","4脚3晶共阴","6脚3晶"};
//测试项目参数列表，顺序对应上面的测试项目名称
struct TestItemPara{    //数据存储在表 test_item 中
    bool test_enable = true;    //默认测试主界面流水数据显示该列
    bool bin_enable = false;    //是否分级，默认false
    int verify_type = 0;    //校准方式
    double vf_val = 5;      //电压
    double if_val = 100;      //电流
    double ok_max = 100;      //良品上限
    double ok_min = 0;      //良品下限
    int time_delay = 3;     //延时
    int time_opt   = 5;     //光谱积分时间
    int range_iv   = 1;     //亮度量程档位，1晶白光有效
    int bin_out    = 255;   //测试结果超出上下限范围的等外BIN，默认255
};
//测试项目对应分BIN参数列表
struct BinItemPara{     //数据存储在表 bin_item 表中
    QString item_name = "";  //测试项目名称
    QString bin_name = "";   //分bin名
    double bin_min = 0.0;   //起始值
    double bin_max = 0.0;     //结束值
    double bin_x0 = 0.0;      //xy分级，色区4坐标值
    double bin_y0 = 0.0;      //
    double bin_x1 = 0.0;      //
    double bin_y1 = 0.0;      //
    double bin_x2 = 0.0;      //
    double bin_y2 = 0.0;      //
    double bin_x3 = 0.0;      //
    double bin_y3 = 0.0;      //
};

//POL极性判断参数结构
struct PolPara{
    int time_delay; //延时
    double vf;      //电压
    double ma;      //电流
    double vfmax;   //电压上限
    double vfmin;   //电压下限
};

class unitprofile
{
public:
    unitprofile();

    static BaseSetPara basesetpara[ST_COUNT];   //各工位对应基本参数设置,1..4工位
    static void readprofile(QString filename);  //读工程文件参数
    static void saveprofile(QString filename);  //写工程文件参数
    static PolPara polpara[ST_COUNT];     //极性POL判断参数

    static TestItemPara testitempara[ST_COUNT][LED_COUNT][TESTITEM_COUNT]; //三维数组，分别对应测试工位、晶片序号、12个测试项目，数组TESTITEM_COUNT下标与lstTestItemName保持一致，不能错位
  //  static BinItemPara binitempara[ST_COUNT][LED_COUNT][ITEMBIN_COUNT] ; //三维数组，，分别对应测试工位、晶片序号、最多50个测试项目分bin参数
};

#endif // UNITPROFILE_H

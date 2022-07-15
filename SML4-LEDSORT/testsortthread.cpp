#include "testsortthread.h"
#include "unitprofile.h"
#include "unitpublic.h"
#include <qdebug.h>
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "windows.h"
extern "C"    //因为是C版的dll文件，在C++中引入其头文件要加extern "C" {},注意
{
    #include "WENYU_PIO32P_DLL.h"
}

extern "C"    //因为是C版的dll文件，在C++中引入其头文件要加extern "C" {},注意
{
    #include "semielectricitydll.h"
}
extern "C"
{
    #include "semispectrumerdll.h"
}


testSortThread::testSortThread(int iindex,QObject * parent)
{
    itag = iindex;      //测试工位序号
    bdcopenflag = false;         //电源状态，true-已打开，注意变量必须初始化，否则会出现在debug下正常，但release下不对了，就是初始值不一样导致
    bspecopenflag = false;         //光谱仪状态，true-已打开
    bp32openflag = false;
//    filedb2memdb(); //创建内存数据库
}

testSortThread::~testSortThread()
{
    if(bdcopenflag){
        SML_CloseEPDevices(itag);   //关闭电源
    }
    if(bspecopenflag){
        SML_CloseDevices(itag); //关闭光谱仪
    }
    if(bp32openflag){
        WY_Close(wyDeviceID);   //关闭IO板卡
    }
}

//IO板卡初始化
int testSortThread::pio32init()
{
    if(WY_Open(itag,wyDeviceID)==0){       //注意，板卡打开成功函数返回是0，4张卡对应4个工位0,1,2,3
        bp32openflag = true;
        return 1;       //初始化成功返回1
    }else {
        bp32openflag = false;
        return 0;
    }
}

//电源初始化
//初始化成功返回1，否则为错误代码
int testSortThread::dcinit()
{
    //1.打开电源
    bdcopenflag = SML_OpenEPDevices(itag);  //注意，电源编号同工位序号保持一致
    if(!bdcopenflag)
        {return -1;}  //打开电源失败
    //0x21-两脚单晶;0x24-两脚单晶(四向);0x22-两脚双晶;0xA4-两脚双晶(四向);0x32-三脚双晶共阴;0x34-三脚双晶共阴(四向);0xB2-三脚双晶共阳;0xB4-三脚双晶共阳(四向);
    //0x42-四脚双晶;0x44-四脚双晶(四向);0x43-四脚三晶共阴;0x49-四脚三晶共阴(四向);0xC3-四脚三晶共阳;
    //0xC9-四脚三晶共阳(四向);0x63-六脚三晶;0x64-六脚四晶;0x84-八脚四晶;0xA5-十脚五晶;0xF1-自定义类型1;0xF2-自定义类型2;0xF3-自定义类型3;

    SML_LoadCalibrate(itag);
    //2.设置晶片类型
    int iledtype=0;
    switch (unitprofile::basesetpara[itag].led_type) {
    case 0:{
        iledtype = 0x21;    //2脚1晶
        break;
    }
    case 1:{
        iledtype = 0x42;    //4脚2晶
        break;
    }
    case 2:{
        iledtype = 0xC3;    //4脚3晶共阳
        break;
    }
    case 3:{
        iledtype = 0x43;    //4脚3晶共阴
        break;
    }
    case 4:{
        iledtype = 0x63;    //6脚3晶
        break;
    }
    default:{
        iledtype = 0x21;    //2脚1晶
        break;
    }
    }
    if(!SML_SetChipType(itag,iledtype))
        {return -2;} //设置晶片类型失败

    //3.设置POL极性判断参数
    double dDataIn[5];
    dDataIn[0] = unitprofile::polpara[itag].time_delay*10; //延时
    dDataIn[1] = unitprofile::polpara[itag].vf;         //电压
    dDataIn[2] = unitprofile::polpara[itag].ma;         //电流
    dDataIn[3] = unitprofile::polpara[itag].vfmax;      //电压上限
    dDataIn[4] = unitprofile::polpara[itag].vfmin;      //电压下限
    if(!SML_SetPDPOL(itag,0,dDataIn))   //POL极性参数只设置0通道即可
        {return -3;}    //设置极性参数失败

    return 1;       //初始化成功完成
}

//光谱仪初始化
int testSortThread::specinit()
{
    //1.打开光谱仪
    bspecopenflag = SML_OpenDevices(itag);      //打开光谱仪
    if(!bspecopenflag)
    {
        return -1;  //光谱仪打开失败
    }
    SML_InitCalibratePara(itag);//光谱仪初始化
    return 1;
}
//校准计算，传入参数：测试参数名称，VF/VFL。。。，
   //晶片序号，晶1、2.。。
   //val校准前数值
   //返回值，校准后数值
double testSortThread::vfycalc(QString itemname,int ledindex,double val)
{
    double k=1;
    double b=0;
    double offset = 0;
    double n1=0;
    double n2=1;
    double n3=0;
    QString ssql = QString("select val_k,val_b,val_offset,val_n1,val_n2,val_n3 from verify_para where station_id=%1 and led_index=%2 and item_name=%3").arg(itag).arg(ledindex).arg(itemname);
//    QSqlQuery mysql(memdb); //查询内存数据库
    QSqlQuery mysql(unitpublic::dblstmem[itag]);
    mysql.exec(ssql);
    if(mysql.next()){       //有校准参数
    switch (unitprofile::testitempara[itag][ledindex][lstTestItemName.indexOf(itemname)].verify_type) {
    case 0:{
        return val; //不校准，直接返回原数值
        break;
    }
    case 1:{        //K，b线性校准
        k=mysql.value(0).toDouble();
        b=mysql.value(1).toDouble();
        return k*val + b;
        break;
    }
    case 2:{        //offset校准
        offset=mysql.value(2).toDouble();
        return val+offset;
        break;
    }
    case 3:{        //ployfit校准
        n1=mysql.value(3).toDouble();
        n2=mysql.value(4).toDouble();
        n3=mysql.value(5).toDouble();
        return n1 + n2*val + n3*val*val ;
        break;
    }
    }
    }else{
        return val; //无校准参数，直接返回
    }
}

//光色电测试，输入参数：ichan=电源通道
int testSortThread::dcspectest(int ichan)
{
    int expoustime = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("WD")].time_opt;
    if(!SML_SetExposuretime(itag,expoustime)){
        bspecopenflag = false;      //调用函数失败，光谱仪掉线
    };   //光谱仪积分时间
    double dDataIn[202]={0};
    double dDataOut[153]={0};
    if(unitprofile::basesetpara[itag].led_type==0){
        dDataIn[0] = 0;     //自动排向
    }else{
        if(ichan==0){
            dDataIn[0] = 6;     //多晶自动排向
        }else
        {
            dDataIn[0] = 5;     //不排向，跟随上次结果
        }
    }
    dDataIn[1] = 0;     //测试完不关灯

    dDataIn[2] = 5;     //IR，多晶RGB
    dDataIn[3] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IR")].time_delay; //延时时间
    dDataIn[4] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IR")].vf_val; //电压
    dDataIn[5] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IR")].if_val; //电流

    dDataIn[6] = 1;     //VFL，用VF项测试VFL，小电流即可
    dDataIn[7] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VFL")].time_delay; //延时时间
    dDataIn[8] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VFL")].vf_val; //电压
    dDataIn[9] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VFL")].if_val; //电流

    dDataIn[10] = 4;     //IV，多晶RGB
    dDataIn[11] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IV")].time_delay; //延时时间
    dDataIn[12] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IV")].vf_val; //电压
    dDataIn[13] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("IV")].if_val; //电流

    dDataIn[14] = 7;     //VF-T，多晶RGB，用VF-T测试VF，跟光谱仪联动触发测试
    dDataIn[15] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VF")].time_delay; //延时时间
    dDataIn[16] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VF")].vf_val; //电压
    dDataIn[17] = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf("VF")].if_val; //电流


    if(!SML_TestPROGRAM(itag,ichan,dDataIn,dDataOut)){
        bdcopenflag = false;
    };       //测试电参数
    //double *pValOut: 输出（返回）值(153 个字节）；0-POL 值，1-开关值，2-POL
    //的电压值，3~152:(50*3=150):50 个测试项目的结果值(3 个数据：1-测试项
    //目，2、3-对应的结果数据)
    unitpublic::lsttestdatapkg[itag][ichan].VFL = dDataOut[7];  //跟上文的输入测试参数列表对应
    unitpublic::lsttestdatapkg[itag][ichan].VFL = vfycalc("VFL",ichan,dDataOut[7]);
    if(unitprofile::basesetpara[itag].led_type!=0){
        unitpublic::lsttestdatapkg[itag][ichan].IV = dDataOut[11];  //跟上文的输入测试参数列表对应，RGB，数据2
        unitpublic::lsttestdatapkg[itag][ichan].IV = vfycalc("IV",ichan,dDataOut[11]);
    }
    unitpublic::lsttestdatapkg[itag][ichan].IR = dDataOut[4];     //IR
    unitpublic::lsttestdatapkg[itag][ichan].IR = vfycalc("IR",ichan,dDataOut[4]);
    unitpublic::lsttestdatapkg[itag][ichan].VF = dDataOut[13];     //VF
    unitpublic::lsttestdatapkg[itag][ichan].VF = vfycalc("VF",ichan,dDataOut[13]);


    double dPara[4]={0}, dX[401], dY[401],dData[2048];
    int iCnt=0,iData=0; //外触发模式测试光谱
    if(!SML_GetAllSSPDHWTRG(itag,dPara,dX,dY,&iCnt,dData,&iData)){  //取光谱能量值，dpara参数备用SML_GetAllSSPDPLUS
        bspecopenflag = false;
    };
    memcpy(unitpublic::lstspecdatapkg[itag][ichan].dx,dX,sizeof (dX));  //波长范围值380-780
    memcpy(unitpublic::lstspecdatapkg[itag][ichan].dy,dY,sizeof (dY));  //波长对应的光谱能量值
//    msleep(10);
    double dTestPara[38]={0};int iParacnt;
    if(!SML_GetAllTestParaSPDPLUS(itag,dTestPara,&iParacnt)){   //iParacnt返回dTestPara数据个数，38
        bspecopenflag = false;
    };
    memcpy(&unitpublic::lstsmlspecdatapkg[itag][ichan],dTestPara,sizeof (dTestPara)); //将返回的光谱数据赋值给lstsmlspecdatapkg对应的工位及晶片数据，注意内存拷贝长度
    unitpublic::lsttestdatapkg[itag][ichan].WD = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dDomWavelengh;    //主波长
    unitpublic::lsttestdatapkg[itag][ichan].WD = vfycalc("WD",ichan,unitpublic::lsttestdatapkg[itag][ichan].WD);

    unitpublic::lsttestdatapkg[itag][ichan].WP = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dPeakValueWavelengh;  //峰波长
    unitpublic::lsttestdatapkg[itag][ichan].WP = vfycalc("WP",ichan,unitpublic::lsttestdatapkg[itag][ichan].WP);
    if(unitprofile::basesetpara[itag].led_type == 0){   //单晶白光，光通量用光谱仪测试
        unitpublic::lsttestdatapkg[itag][ichan].IV = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dLuminousFlux;        //光通量
        unitpublic::lsttestdatapkg[itag][ichan].IV = vfycalc("IV",ichan,unitpublic::lsttestdatapkg[itag][ichan].IV);
    }
    unitpublic::lsttestdatapkg[itag][ichan].CCT = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dTc; //色温
    unitpublic::lsttestdatapkg[itag][ichan].CCT = vfycalc("CCT",ichan,unitpublic::lsttestdatapkg[itag][ichan].CCT);
    unitpublic::lsttestdatapkg[itag][ichan].CIE_x = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dx;    //X坐标
    unitpublic::lsttestdatapkg[itag][ichan].CIE_x = vfycalc("CIE_x",ichan,unitpublic::lsttestdatapkg[itag][ichan].CIE_x);
    unitpublic::lsttestdatapkg[itag][ichan].CIE_y = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dy;    //y坐标
    unitpublic::lsttestdatapkg[itag][ichan].CIE_y = vfycalc("CIE_y",ichan,unitpublic::lsttestdatapkg[itag][ichan].CIE_y);
    unitpublic::lsttestdatapkg[itag][ichan].Ra = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dRa;      //显色指数
    unitpublic::lsttestdatapkg[itag][ichan].Ra = vfycalc("Ra",ichan,unitpublic::lsttestdatapkg[itag][ichan].Ra);
    unitpublic::lsttestdatapkg[itag][ichan].R9 = unitpublic::lstsmlspecdatapkg[itag][ichan].m_dR9;      //R9
    unitpublic::lsttestdatapkg[itag][ichan].R9 = vfycalc("R9",ichan,unitpublic::lsttestdatapkg[itag][ichan].R9);

    SML_SetSWCH(itag,ichan,0);      //测试完毕关灯
//unitpublic::lsttestdatapkg[itag][ichan].SDCM = ，色容差调用哪个SML函数?
}

bool testSortThread::testdatasum_1(int ichan,QString stestitemname,double dtestitemdata)
{
    bool result = false;
    unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].sumdata =    //计算累计值
            unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].sumdata+dtestitemdata;
    if(dtestitemdata >= unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].maxdata){
        unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].maxdata = dtestitemdata;   //最大值
    }
    if(dtestitemdata <= unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].mindata){
        unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].mindata = dtestitemdata;   //最小值
    }
    unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].avgdata =     //计算平均值
            unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].sumdata / unitpublic::lsttestdatapkg[itag][0].testdataid;    //累计值 / 测试数量
    if((dtestitemdata > unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].ok_max)||
            (dtestitemdata < unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].ok_min)){
        unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].ngcount ++;    //NG数量加1
    }else
        result = true;    //结果在上下限范围内，不属于等外BIN，则函数返回true
    unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].ngpercent =
            unitpublic::lsttestdatasumpkg[itag][ichan][lstTestItemName.indexOf(stestitemname)].ngcount *100.0 / unitpublic::lsttestdatapkg[itag][0].testdataid;    //NG数量/测试数量，计算NG比例
    return result;
}

//统计各参数的最大、最小值、平局值等
//测试结果超出上下限范围，则属于等外bin，并返回等外bin号
//如果测试结果没有超出上下限范围，则返回0,
int testSortThread::testdatasum(int ichan)
{//{"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
    //VFL
    int result =0 ; //默认返回0，即各项参数测试结果都在上下限范围内
    QString stestitemname = "VF";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double  dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].VF;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算VF各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回VF对应等外bin
    }

    stestitemname = "VFL";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double  dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].VFL;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算VFL各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回VFL对应等外bin
    }
    stestitemname = "IR";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double  dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].IR;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算IR各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回IR对应等外bin
    }

    stestitemname = "IV";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].IV;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算IV各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回IV对应等外bin
    }

    stestitemname = "WD";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].WD;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算WD各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回WD对应等外bin
    }

    stestitemname = "WP";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].WP;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算WP各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回WP对应等外bin
    }

    stestitemname = "Ra";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].Ra;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算Ra各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回Ra对应等外bin
    }

    stestitemname = "CCT";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].CCT;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算CCT各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回CCT对应等外bin
    }

    stestitemname = "CIE_x";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].CIE_x;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算CIE_x各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回CIE_x对应等外bin
    }

    stestitemname = "CIE_y";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].CIE_y;
        if(!testdatasum_1(ichan,stestitemname,dtestitemdata))       //计算CIE_y各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回CIE_y对应等外bin
    }

    stestitemname = "SDCM";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].SDCM;
        testdatasum_1(ichan,stestitemname,dtestitemdata);       //计算SDCM各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回SDCM对应等外bin
    }

    stestitemname = "R9";
    if(unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].test_enable){ //参数要参与测试
        double dtestitemdata = unitpublic::lsttestdatapkg[itag][ichan].R9;
        testdatasum_1(ichan,stestitemname,dtestitemdata);       //计算R9各项统计参数
            result = unitprofile::testitempara[itag][ichan][lstTestItemName.indexOf(stestitemname)].bin_out; //NG，则返回R9对应等外bin
    }

    return result;      //所有参数都OK则返回0，否则返回该参数对应的等外bin
                        //注意，多个参数属于等外bin时，按以上代码的顺序来确定最后的等外bin号，所以在设置等外bin号时可以根据需要调整设置策略，让LED进入对应的BIN号
}

//获取BIN号
int testSortThread::getbinnumber()
{
    int result = 0;     //初始化0
    bool xybinenable = false;   //颜色参数是否参与分级
    int ixybincount = 0;
    QString sfield = " bin_number ";
    QString swhere = QString("where station_id=%1 ").arg(itag);

    for(int i=0;i<LED_COUNT;i++){   //三晶
        for(int k=0;k<TESTITEM_COUNT;k++){  //测试参数
            if(unitprofile::testitempara[itag][i][k].bin_enable){   //参与分级
                switch (k) {//lstTestItemName = {"VF","VFL","IR","IV","WD","WP","Ra","CCT","CIE_x","CIE_y","SDCM","R9"};
                case 0:{    //VF
                    swhere = swhere + QString(" and (VF%1_MIN<=%2 and VF%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].VF);
                    break;
                    }
                case 1:{    //VFL
                    swhere = swhere + QString(" and (VFL%1_MIN<=%2 and VFL%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].VFL);
                    break;
                    }
                case 2:{    //IR
                    swhere = swhere + QString(" and (IR%1_MIN<=%2 and IR%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].IR);
                    break;
                    }
                case 3:{    //IV
                    swhere = swhere + QString(" and (IV%1_MIN<=%2 and IV%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].IV);
                    break;
                    }
                case 4:{    //WD
                    swhere = swhere + QString(" and (WD%1_MIN<=%2 and WD%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].WD);
                    break;
                    }
                case 5:{    //WP
                    swhere = swhere + QString(" and (WP%1_MIN<=%2 and WP%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].WP);
                    break;
                    }
                case 6:{    //Ra
                    swhere = swhere + QString(" and (Ra%1_MIN<=%2 and Ra%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].Ra);
                    break;
                    }
                case 7:{    //CCT
                    swhere = swhere + QString(" and (CCT%1_MIN<=%2 and CCT%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].CCT);
                    break;
                    }
                case 8:{    //CIE_x ，暂不处理
                    sfield = sfield + QString(",x0_%1,y0_%1,x1_%1,y1_%1,x2_%1,y2_%1,x3_%1,y3_%1 ").arg(i+1);    //色区字段名
                    xybinenable = true;
                    ixybincount++;  //参与xy分级的晶片数量
                    break;
                    }
                case 9:{    //CIY_y ，暂不处理
                    break;
                    }
                case 10:{    //SDCM
                    swhere = swhere + QString(" and (SDCM%1_MIN<=%2 and SDCM%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].SDCM);
                    break;
                    }
                case 11:{    //R9
                    swhere = swhere + QString(" and (R9%1_MIN<=%2 and R9%1_MAX>%2) ").arg(i+1).arg(unitpublic::lsttestdatapkg[itag][i].R9);
                    break;
                    }
                }
            }
        }
    }

    QString ssql = QString("select %1 from binset_para %2 ").arg(sfield).arg(swhere);   //查询语句
//    QSqlQuery mysql(memdb); //查询内存数据库
    QSqlQuery mysql(unitpublic::dblstmem[itag]);
    mysql.exec("select bin_number,VF1_MIN,VF1_MAX,IV1_MIN,IV1_MAX,VF2_MIN,VF2_MAX,binxy1_name from binset_para");
    while (mysql.next()) {
        qDebug() << mysql.value(0) << mysql.value(1) << mysql.value(2) << mysql.value(3);
    }
    mysql.exec(ssql);    //查表
    while (mysql.next()) {  //开始判断xy坐标
        if(xybinenable){//xy需要分级，则还需要继续判断
            switch (ixybincount) {
            case 1:{        //只有晶1参与xy分级,正常情况下，一般只有晶1参与颜色分级，白光
                QVector<QPointF> points1;    //色区坐标
                points1.append(QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble()));
                points1.append(QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble()));
                points1.append(QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble()));
                points1.append(QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble()));

                QPolygonF polygon1(points1);  //判断当前坐标是否在色区内
                if(polygon1.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][0].CIE_x,unitpublic::lsttestdatapkg[itag][0].CIE_y),Qt::WindingFill)){
                    result = mysql.value(0).toInt();    //找到BIN号
                }
                break;
            }
            case 2:{        //晶1、2参与xy分级
                QVector<QPointF> points1;    //晶1色区坐标
                points1.append(QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble()));
                points1.append(QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble()));
                points1.append(QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble()));
                points1.append(QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble()));
                QPolygonF polygon1(points1);  //判断当前坐标是否在色区内
                QVector<QPointF> points2;    //晶2色区坐标
                points2.append(QPointF(mysql.value(9).toDouble(),mysql.value(10).toDouble()));
                points2.append(QPointF(mysql.value(11).toDouble(),mysql.value(12).toDouble()));
                points2.append(QPointF(mysql.value(13).toDouble(),mysql.value(14).toDouble()));
                points2.append(QPointF(mysql.value(15).toDouble(),mysql.value(16).toDouble()));

                QPolygonF polygon2(points2);  //判断当前坐标是否在色区内
                if((polygon1.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][0].CIE_x,unitpublic::lsttestdatapkg[itag][0].CIE_y),Qt::WindingFill))
                        &&(polygon2.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][1].CIE_x,unitpublic::lsttestdatapkg[itag][1].CIE_y),Qt::WindingFill))){
                    result = mysql.value(0).toInt();    //找到BIN号,晶1、2坐标均满足各自的色区要求
                }
                break;
            }
            case 3:{        //晶1、2、3都参与xy分级
                QVector<QPointF> points1;    //晶1色区坐标
                points1.append(QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble()));
                points1.append(QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble()));
                points1.append(QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble()));
                points1.append(QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble()));
                QPolygonF polygon1(points1);  //判断当前坐标是否在色区内
                QVector<QPointF> points2;    //晶2色区坐标
                points2.append(QPointF(mysql.value(9).toDouble(),mysql.value(10).toDouble()));
                points2.append(QPointF(mysql.value(11).toDouble(),mysql.value(12).toDouble()));
                points2.append(QPointF(mysql.value(13).toDouble(),mysql.value(14).toDouble()));
                points2.append(QPointF(mysql.value(15).toDouble(),mysql.value(16).toDouble()));
                QPolygonF polygon2(points2);  //判断当前坐标是否在色区内
                QVector<QPointF> points3;    //晶2色区坐标
                points3.append(QPointF(mysql.value(17).toDouble(),mysql.value(18).toDouble()));
                points3.append(QPointF(mysql.value(19).toDouble(),mysql.value(20).toDouble()));
                points3.append(QPointF(mysql.value(21).toDouble(),mysql.value(22).toDouble()));
                points3.append(QPointF(mysql.value(23).toDouble(),mysql.value(24).toDouble()));
                QPolygonF polygon3(points3);  //判断当前坐标是否在色区内

                if((polygon1.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][0].CIE_x,unitpublic::lsttestdatapkg[itag][0].CIE_y),Qt::WindingFill))
                        &&(polygon2.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][1].CIE_x,unitpublic::lsttestdatapkg[itag][1].CIE_y),Qt::WindingFill))
                        &&(polygon3.containsPoint(QPointF(unitpublic::lsttestdatapkg[itag][2].CIE_x,unitpublic::lsttestdatapkg[itag][2].CIE_y),Qt::WindingFill))){
                    result = mysql.value(0).toInt();    //找到BIN号,晶1、2坐标均满足各自的色区要求
                }
                break;
            }
            }
        }else{  //不进行xy分级，则直接返回前面的参数分级查询结果BIN号
            result=mysql.value(0).toInt();
            break;      //只查询第一条记录
        }
    }
    return result;
}
//获取机台SOT信号
bool testSortThread::readsot()
{
    long sot_val = 0;
    if(WY_GetInPutData(wyDeviceID,sot_val)==0){     //获取输入端口DI0-15的数据
        long sot_bit = 1 << unitprofile::basesetpara[itag].sot_bit;                     //先把1按sot_bit左移
        long sot_level = (sot_bit & sot_val) >> unitprofile::basesetpara[itag].sot_bit; //取对应输入端口（即sot_bit位）的数据后右移到最末尾
        if(unitprofile::basesetpara[itag].sot_type == sot_level){   //sot对应端口输入的电平信号跟有效电平信号一致，则认为收到有效的SOT信号
            //读到SOT信号后，要清除EOT信号 ？
            sendeot(0,true);    //清除EOT信号
            return true;
        }else{
            return false;
        }
    }else{
        bp32openflag = false;   //IO卡打开失败
        return false;
    }
}

//发送机台EOT信号及BIN号
bool testSortThread::sendeot(int binid,bool bcleareot)
{
    long eot_val = 0 | binid;
    if(unitprofile::basesetpara[itag].eot_binout==BINOUT_LOW){  //BIN号为输出端口的高8位
        eot_val = eot_val << 8;     //高8位
    }   //如果是低8位，则不进行移位处理
    if(!bcleareot){ //设置EOT信号
        if(unitprofile::basesetpara[itag].eot_type==ELEVEL_HIGH){   //EOT信号高电平有效
            eot_val = eot_val | (1 << unitprofile::basesetpara[itag].eot_bit);  //将EOT对应位置高电平，则输出EOT信号
        }   //如果EOT信号是低电平有效，则不处理，0即是低电平设置EOT信号
    }else { //清除 EOT信号
        if(unitprofile::basesetpara[itag].eot_type==ELEVEL_LOW){   //EOT信号低电平有效
            eot_val = eot_val | (1 << unitprofile::basesetpara[itag].eot_bit);  //将EOT对应位置高电平,则清除EOT信号
        }   //如果EOT信号是高电平有效，则不处理，0即是低电平清除EOT信号
    }
    if(WY_SetOutPutData(wyDeviceID,eot_val)==0)
    {
        return true;
    }else {
        bp32openflag = false;   //IO卡打开失败
        return false;
    }
}

//线程执行内容
void testSortThread::run()
{
    LARGE_INTEGER litmp;
    LONGLONG Qpart1,Qpart2,Qpart3,Qpart0;
    double dfMinus,dfFreq,dfTime,dSpanTime;
    QueryPerformanceFrequency(&litmp);      //高精度计时，windows api
    dfFreq = (double)litmp.QuadPart;
    int iuphcount = 0;  //UPH计算因子，每生产10个动态刷新一次UPH值
    while (true) {      //执行测试
        QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
        Qpart1 = litmp.QuadPart; //开始计时

        //QDateTime startTime = QDateTime::currentDateTime();
        //1.线程挂起处理
        while (unitpublic::mthdsuspended[itag])
        {
            msleep(1);   //线程挂起后，不执行线程的主要任务，在这里一直等待恢复，采用自定义全局变量来识别
            unitpublic::mthdsuspendok[itag]=true;
            emit teststatus(itag,0);    //暂停测试，挂起
            //线程挂起的过程中，可以执行一些命令，比如单步测试、参数初始化导入等等
            switch (unitpublic::testcmd[itag]) {
            case CMD_TEST_STEP:{    //单步测试
                unitpublic::mthdsuspended[itag] = false;    //单步测试，退出挂起状态，开始执行测试
                break;
            }
            }
        }
        unitpublic::mthdsuspendok[itag]=false;
        emit teststatus(itag,1);    //恢复测试，resume

        //2.电源初始化
//        msleep(10);
        if(!bdcopenflag){
            if(dcinit()==1){
                emit dcstatus(itag,1);
            }else
            {
                emit dcstatus(itag,0);
            }
        }
        if(!bspecopenflag){
            if(specinit()==1){
                emit specstatus(itag,1);
            }else
            {
                emit specstatus(itag,0);
            }
        }
        if((!bdcopenflag)||(!bspecopenflag))
        {
            msleep(30);
            emit testdata(itag);    //显示测试结果，数据处理也都在一个测试节拍内
            if(unitpublic::testcmd[itag]==CMD_TEST_STEP){
                unitpublic::mthdsuspended[itag] = true;     //执行完一次测试后，线程挂起
                unitpublic::testcmd[itag] = CMD_TEST_DONE;
            }
            continue;   //电源或光谱仪不在线，不测试，返回继续循环执行
        }
        //3.等待机台SOT信号
        if(unitpublic::testcmd[itag]!=CMD_TEST_STEP){   //机台联机且不是单步测试时，要打开IO板卡并等待机台SOT信号
            while (unitpublic::bmachine[itag] && (!unitpublic::mthdsuspended[itag])) {  //线程未挂起且联机状态，则原地等待sot信号
                if(!bp32openflag){
                    if(pio32init()==1){
                        emit p32status(itag,1); //IO板卡打开成功
                    }else
                    {
                        emit p32status(itag,0);
                    }
                }
                if(readsot()){  //原地等待SOT信号
                    break;  //收到机台SOT信号则退出原地等待，往下走进行光色电测试
                }
                msleep(10); //
            }
        }


        //4.光色电测试
        msleep(30);    //收到SOT信号后要延时，保证探针夹紧再测试
        Qpart0 = litmp.QuadPart; //接收到SOT就位信号，开始测试计时
        int binid=0;
        int binid1=0;
        int binid2=0;
        int binid3=0;
        if(unitprofile::basesetpara[itag].led_type == 0){
            dcspectest(LED_1);      //1晶
            unitpublic::lsttestdatapkg[itag][0].testdataid ++ ;
            binid1=testdatasum(LED_1);     //统计测试结果,统计结果必须在累计计数之后
        }else
        if(unitprofile::basesetpara[itag].led_type == 1){
            dcspectest(LED_1);      //2晶
            dcspectest(LED_2);
            unitpublic::lsttestdatapkg[itag][0].testdataid ++ ;
            binid1=testdatasum(LED_1);     //统计测试结果
            binid2=testdatasum(LED_2);     //统计测试结果
        }else
        {
            dcspectest(LED_1);      //3晶
            dcspectest(LED_2);
            dcspectest(LED_3);
            unitpublic::lsttestdatapkg[itag][0].testdataid ++ ;
            binid1=testdatasum(LED_1);     //统计测试结果
            binid2=testdatasum(LED_2);     //统计测试结果
            binid3=testdatasum(LED_3);     //统计测试结果，注意多晶时，等外bin的顺序，取最后一个晶片的最后一个参数等外bin号
        }
        if((binid1==0)&&(binid2==0)&&(binid3==0)){
            binid=getbinnumber(); //如果testdatasum返回值为0，则表示该参数OK，不在等外bin，继续通过getbinnumber查询BIN号
            if(binid>0)
                unitpublic::lsttestdatapkg[itag][0].testresult = true;      //测试结果OK
            else
                unitpublic::lsttestdatapkg[itag][0].testresult = false;
        }else{
            if(binid1>0)
                binid=binid1;   //NG时按晶1、2、3的顺序取等外BIN
            else
                if(binid2>0)
                    binid = binid2;
            else
                    if(binid3>0)
                        binid=binid3;
        }
        emit speccurve(itag);       //画光谱曲线
        emit specxy(itag);          //CIE色品图打靶
        unitpublic::lststationsumpkg[itag].sumcount ++; //累计产量递增
        if(binid>0){                                        //注意bin号与下标的对应关系，bincount数组是从0开始
            unitpublic::lststationsumpkg[itag].bincount[binid-1] ++;  //该BIN计数递增
            unitpublic::lststationsumpkg[itag].binpercent[binid-1] = unitpublic::lststationsumpkg[itag].bincount[binid-1]*100.0 / unitpublic::lststationsumpkg[itag].sumcount;
            unitpublic::lststationsumpkg[itag].valcount ++; //计算方法后期可根据实际需求自行更改，另外目前统计计数都是程序启动开始以来的计数，是否需要保存到其他地方，下次程序启动后再继续计数，根据实际需求修改
        }else{           //binid==0时，表示测试值都在单项参数的max_min设定范围内，但又没有被分选到设定的分级参数区间内，类似一些离散点
                //默认等外BIN
            binid=unitprofile::basesetpara[itag].binout_default;
            unitpublic::lststationsumpkg[itag].bincount[binid-1] ++;  //该BIN计数递增
            unitpublic::lststationsumpkg[itag].binpercent[binid-1] = unitpublic::lststationsumpkg[itag].bincount[binid-1]*100.0 / unitpublic::lststationsumpkg[itag].sumcount;
        }
        //5.发送BIN号至机台,EOT信号
        //...
        unitpublic::lsttestdatapkg[itag][0].binid = binid; //，BIN号数据都存放在晶1的位置，可能是等外bin也可能是正常bin
        sendeot(binid,false);   //发送BIN号
        //6.统计测试效率
        iuphcount ++ ;
        if(iuphcount>=10){   //UPH计算，采样值为10个测试周期
            dfMinus = (double)(Qpart1 - Qpart3);//计算计数器值
            dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
            if(dfTime>0)        //最开始的2组数据可能是负数
                unitpublic::lststationsumpkg[itag].uph = ((iuphcount * 3600.0)/dfTime)/1000; //单位 K/H
            QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
            Qpart3 = litmp.QuadPart; //终止计时
            iuphcount = 0;
        }
        //7.主线程显示测试数据
        emit testdata(itag);    //显示测试结果，数据处理也都在一个测试节拍内
        QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
        Qpart2 = litmp.QuadPart; //终止计时
        dfMinus = (double)(Qpart2 - Qpart0);//计算计数器值
        dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
        dSpanTime = dfTime*1000;    //ms
        emit testtime(itag,dSpanTime);   //耗时

        if(unitpublic::testcmd[itag] == CMD_TEST_STEP){ //单步测试
            unitpublic::mthdsuspended[itag] = true;     //执行完一次测试后，线程挂起
            unitpublic::testcmd[itag] = CMD_TEST_DONE;
        }
    }
}


//在工程中右键选择“添加库”，选在外部库 libsemielectricity.a
//本工程用gcc编译，所以把原来的semielectricity.lib文件改成qt库文件格式化名称libsemielectricity.a
//同时将libsemielectricity.a以及semielectricity.h、semielectricity.dll文件都放到工程路径下
//同时必须把semielectricity.dll以及对应的A/B/C/D四个支持dll文件都拷贝到执行程序所在的路径才可正常运行
//要正确调用函数，还需要将原来的 typedef 关键字去掉，否则无法调用，原因？？？

//extern "C"  bool WINAPI OpenDevices();

//定义函数指针

/*打开设备*/
/*
int：设备号： 0~3
return： 
*/
bool (SML_OpenEPDevices)(int index);//
//typedef bool (SML_OpenEPDevices)(int index);//

/*关闭设备*/
/*
int：设备号： 0~3
return：
*/
bool (SML_CloseEPDevices)(int index);//
//typedef bool (SML_CloseEPDevices)(int index);//


//
typedef bool (SML_GetEPDevSN)(int idex,unsigned char* pSN,int *iCnt);
typedef bool (SML_GetEPDevVN)(int idex,unsigned char* pVN,int *iCnt);

//定义函数
/*
通道号0~4 ，5个通道；
*/

/*设置晶片类型值：；
 int：设备号： 0~3
 int：通道号（无效）；
 int：档位值；*/
bool (SML_SetChipType)(int idex,int iVal);//
//typedef bool (SML_SetChipType)(int idex,int iVal);//
/*设置电源电压：
 int：设备号： 0~3
 int：通道号；
 double：电源电压值；*/
typedef bool (SML_SetPowerVol)(int idex,int iChan,double dVal);//
/*设置正向电流：
 int：设备号： 0~3
 int：通道号；
 double：正向电流值；*/
typedef bool (SML_SetFRWCur)(int idex,int iChan,double dVal);
/*设置反向电压：
 int：设备号： 0~3
 int：通道号；
 double：反向电压值；*/
typedef bool (SML_SetBKWVol)(int idex,int iChan,double dVal);
/*设置电流档位：0=小电流，1=大电流；
 int：设备号： 0~3
 int：通道号；
 int：电流档位值；*/
typedef bool (SML_SetCurGear)(int idex,int iChan,int iVal);
/*设置开关值：开关值 0=关闭 ，1=正向 ，2=反向；
 int：设备号： 0~3
 int：通道号；
 int：开关值；*/
bool (SML_SetSWCH)(int idex,int iChan,int iVal);
//typedef bool (SML_SetSWCH)(int idex,int iChan,int iVal);
/*设置电极值：0~3 ，4个状态；
 int：设备号： 0~3
 int：通道号；
 int：电极值；*/
typedef bool (SML_SetPoleVal)(int idex,int iChan,int iVal);
/*设置光探头档位值：0~3 ，4个档位；
 int：设备号： 0~3
 int：通道号；
 int：档位值；*/
typedef bool (SML_SetProbeGear)(int idex,int iChan,int iVal);
/*获取正向电压：
 int：设备号： 0~3
 int：通道号；
 double*：正向电压值；*/
typedef bool (SML_GetFRWVol)(int idex,int iChan,double *pVal);
/*获取反向漏流：
 int：设备号： 0~3
 int：通道号；
 double*：反向漏流值；*/
typedef bool (SML_GetBKWCur)(int idex,int iChan,double *pVal);
/*获取大电流：
 int：设备号： 0~3
 int：通道号；
 double*：大电流值；*/
typedef bool (SML_GetMAXCur)(int idex,int iChan,double *pVal);
/*获取小电流：
 int：设备号： 0~3
 int：通道号；
 double*：小电流值；*/
typedef bool (SML_GetMINCur)(int idex,int iChan,double *pVal);
//PowerSource,ForwardCurrent,ForwardVoltage,ReverseCurrent,ReverseVoltage,MaxCurrent,MinCurrent

/*加载校准参数至程序
 int：设备号： 0~3
*/
bool (SML_LoadCalibrate)(int idex);
//typedef bool (SML_LoadCalibrate)(int idex);


/*fromReal：
 int：设备号： 0~3
 double：输入值；
 int：转换类型：(0-PowerSource,1-ForwardCurrent,2-ForwardVoltage,3-ReverseCurrent,4-ReverseVoltage,5-MaxCurrent,6-MinCurrent,7-ForwardCurrentL)；
 int：通道号；
 返回值 double*/
typedef double (SML_FromReal)(int idex,double dval, int nType,int nChan);
/*toReal：
 int：设备号： 0~3
 double：输入值；
 int：转换类型：(0-PowerSource,1-ForwardCurrent,2-ForwardVoltage,3-ReverseCurrent,4-ReverseVoltage,5-MaxCurrent,6-MinCurrent,7-ForwardCurrentL)；
 int：通道号；
 返回值 double*/
typedef double (SML_ToReal)(int idex,double dval, int nType,int nChan);

/*FastTest：
 int：设备号： 0~3
 int：通道号；
 double*：pVal[0] 电压，pVal[1] 漏流；*/
typedef bool (SML_FastTest)(int idex,int iChan,double *pVal);

/*QueryEXTTrigger：查询外触发值
 int：设备号： 0~3
 返回值： false-未触发 true-已触发 */
typedef bool (SML_QueryEXTTrigger)(int idex);


/*QueryPoleVal：查询电极值
 int：设备号： 0~3
 int：通道号；
 int*：POL电极值；*/
typedef bool (SML_QueryPoleVal)(int idex,int iChan,int *pVal);

/*读取光探测器采样值：
 int：设备号： 0~3
 int：通道号；
 int*：光探测器采样值；*/
typedef bool (SML_GetOPTSensor)(int idex,int iChan,int *pVal);

/*校准参数保存FLASH
 int：设备号： 0~3
*/
typedef bool (SML_SaveCalToFlash)(int idex);
//-------------------------------------------------------------------------------------------
/*测试VFL：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestVFL)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试VF：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestVF)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试VRL：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestVRL)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试IF：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestIF)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试IR：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestIR)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试IV：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestIV)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试VRP：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestVRP)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*测试PROBE：
 int：设备号： 0~3
 int：延时时间ms
 int：通道号；
 double*：输入值；0~3：POL值，开关灯，电压，电流；
 double*：输出（返回）值；0~3：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestPROBE)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

//--------------------------------------------------------------------------
/*设置VFL：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDVFL)(int idex,int iChan,double *pValIn);

/*设置VF：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDVF)(int idex,int iChan,double *pValIn);

/*设置VRL：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDVRL)(int idex,int iChan,double *pValIn);

/*设置IF：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDIF)(int idex,int iChan,double *pValIn);

/*设置IR：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDIR)(int idex,int iChan,double *pValIn);

/*设置IV：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDIV)(int idex,int iChan,double *pValIn);

/*设置VRP：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDVRP)(int idex,int iChan,double *pValIn);

/*设置PROBE：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDPROBE)(int idex,int iChan,double *pValIn);

/*设置DF1：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDDF1)(int idex,int iChan,double *pValIn);

/*设置DF2：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDDF2)(int idex,int iChan,double *pValIn);//_SetPDDF2@8

/*设置DF3：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDDF3)(int idex,int iChan,double *pValIn);//_SetPDDF3@8

/*设置DF4：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：延时，电压，电流；*/
typedef bool (SML_SetPDDF4)(int idex,int iChan,double *pValIn);//_SetPDDF4@8

/*设置POL：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~4：延时，电压，电流，上限，下限；*/
bool (SML_SetPDPOL)(int idex,int iChan,double *pValIn);//_SetPDPOL@8
//typedef bool (SML_SetPDPOL)(int idex,int iChan,double *pValIn);//_SetPDPOL@8

/*组合测试：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~2：POL值，开关灯，组合项目；
 double*：输出（返回）值（38字节）；0~19：POL值，开关灯，预留，返回值；*/
typedef bool (SML_TestCOMBINED)(int idex,int iChan,double *pValIn,double *pValOut);//_TestCOMBINED@12

/*单项测试：
 int：设备号： 0~3
 int：通道号；
 int：iType:1.VFL;2.VF;3.VRL;4.IF;5.IR;6.IV;7.VPR;8.探针组
 double*：输入值；0~1：POL值，开关灯；
 double*：输入值；0~2：延时，电压，电流；
 double*：输出（返回）值；0~2：POL值（0失败，1开路，2短路，3正向，4反向，5不排向90度，6不排向270度），开关灯，对应单项返回值；*/
typedef bool (SML_TestSINGLED)(int idex,int iChan,int iType,double *pValIn1,double *pValIn2,double *pValOut);

/*编程测试：
 int：设备号： 0~3
 int：通道号；
 double*：输入值(202个字节)；0~1：POL值，开关灯；2~201：(50*4=200)：50个测试项目；
 double*：输出（返回）值(153个字节）；0-POL值，1-开关值，2-POL的电压值，3~152:(50*3=150):50个测试项目的结果值(3个数据：1-测试项目，2、3-对应的结果数据)*/
bool (SML_TestPROGRAM)(int idex,int iChan,double *pValIn,double *pValOut);//
//typedef bool (SML_TestPROGRAM)(int idex,int iChan,double *pValIn,double *pValOut);//

/*针脚短路测试：
 int：设备号： 0~3
 int：通道号；
 double*：输入值：2个数据（0-电源电压，1-正向电流）
 double*：输出（返回）值：8个数据（0-（1,2脚状态），1-正向电压，2-（2,3脚状态），3-正向电压，4-（3,4脚状态），5-正向电压,6-（4,1脚状态），7-正向电压）*/
typedef bool (SML_TestPINSHORT)(int idex,int iChan,double *pValIn,double *pValOut);//,double *pValOutOrg
/*
int;设备号： 0~3
double*:0~2：(延时,0,0);
double*:0~2：(电压,0,0);
double*:0~2：(电流,0,0);
double*:0~2：(Min,0,0);
double*:0~2：(Max,0,0);
*/
typedef bool (SML_SetVFLCondition)(int,double*,double*,double*,double*,double*);//_SML_SetVFLCondition@24
typedef bool (SML_SetVFCondition)(int,double*,double*,double*,double*,double*);//_SML_SetVFCondition@24
typedef bool (SML_SetIRCondition)(int,double*,double*,double*,double*,double*);//_SML_SetIRCondition@24

//typedef bool (SML_DoTest)(int,double*);//_SML_DoTest@8
 /*测试：
 int：设备号： 0~3
 int：通道号；
 double*：输出（返回）值；0~5：POL值（0失败，1开路，2短路，3正向，4反向，5不排向90度，6不排向270度），合格值，POL数值，VFL值，VF值，IR值；
*/
typedef bool (SML_DoTest)(int,int,double*);//

/*读取温度采样值：
 int：设备号： 0~3
 double*：温度采样值；*/
typedef bool (SML_GetTmpVal)(int idex,double *pVal);
/*读取湿度采样值：
 int：设备号： 0~3
 double*：湿度采样值；*/
typedef bool (SML_GetHumVal)(int idex,double *pVal);

typedef bool (SML_GetSVolVal)(int idex,int ichan,double *pVal);

/*测试：
 int：设备号： 0~3
 int：通道号；
 double*：输入值；0~5：POL值，开关灯，设置开关值，延时，电压，电流；
 int*：0-正常，1-开路；2-短路；
*/
//typedef bool (SML_ProTest)(int idex,int ichan,double *pValIn);//
typedef bool (SML_ProTest)(int idex,int ichan,double *pValIn,int *pSTOut);//

/*测试：
 int：设备号： 0~3
 int：通道号；
 double*：输出（返回）值；0~5：POL值（0失败，1开路，2短路，3正向，4反向，5不排向90度，6不排向270度），合格值，POL数值，VFL值，VF值，IR值；
 return:-1：失败；0：未触发；1：已触发
*/
//typedef int (SML_TrgTest)(int idex,int ichan,double *pDataout);
typedef int (SML_TrgTest)(int idex,int ichan,double *pDataout);


typedef int (SML_SaveToFlash)(int idex);

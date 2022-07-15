
//extern "C"  bool WINAPI OpenDevices();

//定义函数指针

/*打开光路盒*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_OpenDevices)(int index);//
//typedef bool (SML_OpenDevices)(int index);//

/*关闭光路盒*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_CloseDevices)(int index);//
//typedef bool (SML_CloseDevices)(int index);//

/*读取参数*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_InitCalibratePara)(int index);//
//typedef bool (SML_InitCalibratePara)(int index);//

/*发送获取光谱曲线数据命令*/
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_SendAllSP)(int index);//

/*获取光谱曲线数据*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param dx 400个值
@param dy 400个值
@param iCnt 值400
@return   
*/
typedef bool (SML_GetAllSPD)(int index,double* pPara,double *dx,double*dy,int *iCnt);//

/*获取光谱SS数据*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param pData 2048个原始采样值
@param iCnt 值2048
@return   
*/
typedef bool (SML_GetAllSS)(int index,double* pPara,double *pData,int *iCnt);//

/*获取光谱PI数据*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param pData 4001个PI值
@param iCnt 值4001
@return   
*/
typedef bool (SML_GetAllPI)(int index,double* pPara,double *pData,int *iCnt);//

/*获取光谱WD数据*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param pData 2048个波长校准值
@param iCnt 值2048
@return   
*/
typedef bool (SML_GetAllWD)(int index,double* pPara,double *pData,int *iCnt);//

/*获取STDK数据*/
/*
@param index devindex 0~3
@param pData 2048个STDK值
@param iCnt 值2048
@return   
*/
typedef bool (SML_GetStdKData)(int index,double *pData,int *iCnt);//

/*设置标准色温 单位:*/
/*
@param index devindex 0~3
@param dCT 标准色温值
@return   
*/
typedef bool (SML_SetStdCT)(int index,double dCT);//

/*获取标准色温 单位:*/
/*
@param index devindex 0~3
@return  double  标准色温值
*/
typedef double (SML_GetStdCT)(int index);//

/*设置曝光时间 单位:ms*/
/*
@param index devindex 0~3
@param dTime 曝光时间
@return   
*/
bool (SML_SetExposuretime)(int index,double dTime);//
//typedef bool (SML_SetExposuretime)(int index,double dTime);//

/*获取测试值*/
/*
@param index devindex 0~3
@param pTD 33个测试值
@param iCnt 值33
@return   
*/
typedef bool (SML_GetAllTestParaSPD)(int index,double* pTD,int *icnt);//

/*获取测试值*/
/*
@param index devindex 0~3
@param pTD 36个测试值
@param iCnt 值36
@return   
*/
typedef bool (SML_GetAllTestParaSPDXYZ)(int index,double* pTD,int *icnt);//
bool (SML_GetAllTestParaSPDPLUS)(int index,double* pTD,int *icnt);//
//typedef bool (SML_GetAllTestParaSPDPLUS)(int index,double* pTD,int *icnt);//

/*获取曝光时间*/
/*
@param index devindex 0~3
@return  double  曝光时间 ms
*/
typedef double (SML_GetExposureTime)(int index);//

/*获取SDCM*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param pEllipsePara 6个参数值,椭圆参数
@param nStdlight 选择基准光源时:// 0-6500K;1-5000K;2-4000K;3-3500K;4-3000K;5-2700K
@param iType 0-椭圆参数;1-基准光源
@return   
*/
typedef double (SML_GetSDCM)(int index,double* pPara,double *pEllipsePara,int nStdlight,int iType);//

/*获取序列号*/
/*
@param index devindex 0~3
@param pSN 3个值，序列号
@param iCnt 值3
@return   
*/
typedef bool (SML_GetDevSN)(int index,unsigned char* pSN,int *iCnt);//

/*获取版本号*/
/*
@param index devindex 0~3
@param pSN 3个值，版本号
@param iCnt 值3
@return   
*/
typedef bool (SML_GetDevVersion)(int index,unsigned char* pVersion,int *iCnt);//

/*获取采样温度值*/
/*
@param index devindex 0~3
@return  double  温度值
*/
typedef double (SML_GetSampleTmp)(int index);//

/*设置光谱平均帧数*/
/*
@param index devindex 0~3
@param dSPAF 光谱平均帧数
@return  
*/
typedef bool (SML_SetSPAvgFrame)(int index,double dSPAF);//

/*获取7200个数据*/
/*
@param index devindex 0~3
@param pData 7200个参数值
@param pPara 33个参数值
@param iDataCnt 值7200
@param iParaCnt 值33
@return   
*/
typedef bool (SML_Get01nmRealWaveData)(int index,double* pData,double *pPara,int *iDataCnt,int *iParaCnt);//


//获取ASCII码32位
/*
@param index devindex 0~3
@param pchData 32个值
@return   
*/
typedef bool (SML_GetAsciiCodeData)(int index,unsigned char*pchData);//

//设置暗底使能
/*
@param index devindex 0~3
@param iState 使能值0,1
@return   
*/
typedef bool (SML_SetEnabledDarkData)(int index,int iState);//

//更新暗底数据
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_UpdateDarkData)(int index);//

//从文件获取远方测试数据（401个）
/*
@param index devindex 0~3
@param iNum 
@param pChartData
@return   
*/
typedef bool (SML_SetReferChartData)(int index,int iNum,double *pChartData);//

//在本机进行校准生成系数数据（4001个）
/*
@param index devindex 0~3
@param iNum 
@param pPara
@return   
*/
typedef bool (SML_GetReferChartDataCoef)(int index,int iNum,double* pPara);//

/*选择当前标准曲线*/
/*
@param index devindex 0~3
@param iNum 
@return   
*/
typedef bool (SML_SetReferChartDataCoefId)(int index,int iNum);//

//在本机进行光通量校准生成系数数据（1个）
/*
@param index devindex 0~3
@param pPara 
@param dSTDF
@return   
*/
typedef bool (SML_GetReferFluxCoef)(int index,double* pPara,double dSTDF);//

//光通量系数置1
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_SetReferFluxData)(int index);//

//获取光通量（探头）修正系数
/*
@param index devindex 0~3
@param pPara 光通量修正系数
@return   
*/
typedef bool (SML_GetFluxCoeff)(int index,double *pData);//

//获取红外光功率
/*
@param index devindex 0~3
@param pData 外光功率
@return   
*/
typedef bool (SML_GetInfraredLPower)(int index,double* pData);//

/*获取光谱曲线数据*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param dx 400个值
@param dy 400个值
@param iCnt 值400
@param dss 2048个原始采样值
@param issCnt 值2048
@return   
*/
typedef bool (SML_GetAllSSPD)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从光路盒读取
typedef bool (SML_GetAllSSPDEX)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从文件读取
bool (SML_GetAllSSPDPLUS)(int index,double dTime,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从光路盒读取
//typedef bool (SML_GetAllSSPDPLUS)(int index,double dTime,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从光路盒读取

/*获取光谱曲线数据-401*/
/*
@param index devindex 0~3
@param pPara 4个参数值,暂时保留 
@param dx 401个值
@param dy 401个值
@param iCnt 值401
@param dss 2048个原始采样值
@param issCnt 值2048
@return   
*/
typedef bool (SML_GetAllSSPDCAL)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从光路盒读取
typedef bool (SML_GetAllSSPDCALEX)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK从文件读取
bool (SML_GetAllSSPDHWTRG)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//
//typedef bool (SML_GetAllSSPDHWTRG)(double*,double*,double*,int*,double*,int*);//
/*获取RgRf-RFI:double d1[2]-double d2[99]*/
/*
@param index devindex 0~3
@param pRgRf 2个值：0-Rg,1-Rf
@param pRFI 99个RFI值
@return   
*/
typedef bool (SML_GetRGRFRFIPara)(int index,double* pRgRf,double* pRFI);//


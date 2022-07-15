
//extern "C"  bool WINAPI OpenDevices();

//���庯��ָ��

/*�򿪹�·��*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_OpenDevices)(int index);//
//typedef bool (SML_OpenDevices)(int index);//

/*�رչ�·��*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_CloseDevices)(int index);//
//typedef bool (SML_CloseDevices)(int index);//

/*��ȡ����*/
/*
@param index devindex 0~3
@return   
*/
bool (SML_InitCalibratePara)(int index);//
//typedef bool (SML_InitCalibratePara)(int index);//

/*���ͻ�ȡ����������������*/
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_SendAllSP)(int index);//

/*��ȡ������������*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param dx 400��ֵ
@param dy 400��ֵ
@param iCnt ֵ400
@return   
*/
typedef bool (SML_GetAllSPD)(int index,double* pPara,double *dx,double*dy,int *iCnt);//

/*��ȡ����SS����*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param pData 2048��ԭʼ����ֵ
@param iCnt ֵ2048
@return   
*/
typedef bool (SML_GetAllSS)(int index,double* pPara,double *pData,int *iCnt);//

/*��ȡ����PI����*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param pData 4001��PIֵ
@param iCnt ֵ4001
@return   
*/
typedef bool (SML_GetAllPI)(int index,double* pPara,double *pData,int *iCnt);//

/*��ȡ����WD����*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param pData 2048������У׼ֵ
@param iCnt ֵ2048
@return   
*/
typedef bool (SML_GetAllWD)(int index,double* pPara,double *pData,int *iCnt);//

/*��ȡSTDK����*/
/*
@param index devindex 0~3
@param pData 2048��STDKֵ
@param iCnt ֵ2048
@return   
*/
typedef bool (SML_GetStdKData)(int index,double *pData,int *iCnt);//

/*���ñ�׼ɫ�� ��λ:*/
/*
@param index devindex 0~3
@param dCT ��׼ɫ��ֵ
@return   
*/
typedef bool (SML_SetStdCT)(int index,double dCT);//

/*��ȡ��׼ɫ�� ��λ:*/
/*
@param index devindex 0~3
@return  double  ��׼ɫ��ֵ
*/
typedef double (SML_GetStdCT)(int index);//

/*�����ع�ʱ�� ��λ:ms*/
/*
@param index devindex 0~3
@param dTime �ع�ʱ��
@return   
*/
bool (SML_SetExposuretime)(int index,double dTime);//
//typedef bool (SML_SetExposuretime)(int index,double dTime);//

/*��ȡ����ֵ*/
/*
@param index devindex 0~3
@param pTD 33������ֵ
@param iCnt ֵ33
@return   
*/
typedef bool (SML_GetAllTestParaSPD)(int index,double* pTD,int *icnt);//

/*��ȡ����ֵ*/
/*
@param index devindex 0~3
@param pTD 36������ֵ
@param iCnt ֵ36
@return   
*/
typedef bool (SML_GetAllTestParaSPDXYZ)(int index,double* pTD,int *icnt);//
bool (SML_GetAllTestParaSPDPLUS)(int index,double* pTD,int *icnt);//
//typedef bool (SML_GetAllTestParaSPDPLUS)(int index,double* pTD,int *icnt);//

/*��ȡ�ع�ʱ��*/
/*
@param index devindex 0~3
@return  double  �ع�ʱ�� ms
*/
typedef double (SML_GetExposureTime)(int index);//

/*��ȡSDCM*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param pEllipsePara 6������ֵ,��Բ����
@param nStdlight ѡ���׼��Դʱ:// 0-6500K;1-5000K;2-4000K;3-3500K;4-3000K;5-2700K
@param iType 0-��Բ����;1-��׼��Դ
@return   
*/
typedef double (SML_GetSDCM)(int index,double* pPara,double *pEllipsePara,int nStdlight,int iType);//

/*��ȡ���к�*/
/*
@param index devindex 0~3
@param pSN 3��ֵ�����к�
@param iCnt ֵ3
@return   
*/
typedef bool (SML_GetDevSN)(int index,unsigned char* pSN,int *iCnt);//

/*��ȡ�汾��*/
/*
@param index devindex 0~3
@param pSN 3��ֵ���汾��
@param iCnt ֵ3
@return   
*/
typedef bool (SML_GetDevVersion)(int index,unsigned char* pVersion,int *iCnt);//

/*��ȡ�����¶�ֵ*/
/*
@param index devindex 0~3
@return  double  �¶�ֵ
*/
typedef double (SML_GetSampleTmp)(int index);//

/*���ù���ƽ��֡��*/
/*
@param index devindex 0~3
@param dSPAF ����ƽ��֡��
@return  
*/
typedef bool (SML_SetSPAvgFrame)(int index,double dSPAF);//

/*��ȡ7200������*/
/*
@param index devindex 0~3
@param pData 7200������ֵ
@param pPara 33������ֵ
@param iDataCnt ֵ7200
@param iParaCnt ֵ33
@return   
*/
typedef bool (SML_Get01nmRealWaveData)(int index,double* pData,double *pPara,int *iDataCnt,int *iParaCnt);//


//��ȡASCII��32λ
/*
@param index devindex 0~3
@param pchData 32��ֵ
@return   
*/
typedef bool (SML_GetAsciiCodeData)(int index,unsigned char*pchData);//

//���ð���ʹ��
/*
@param index devindex 0~3
@param iState ʹ��ֵ0,1
@return   
*/
typedef bool (SML_SetEnabledDarkData)(int index,int iState);//

//���°�������
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_UpdateDarkData)(int index);//

//���ļ���ȡԶ���������ݣ�401����
/*
@param index devindex 0~3
@param iNum 
@param pChartData
@return   
*/
typedef bool (SML_SetReferChartData)(int index,int iNum,double *pChartData);//

//�ڱ�������У׼����ϵ�����ݣ�4001����
/*
@param index devindex 0~3
@param iNum 
@param pPara
@return   
*/
typedef bool (SML_GetReferChartDataCoef)(int index,int iNum,double* pPara);//

/*ѡ��ǰ��׼����*/
/*
@param index devindex 0~3
@param iNum 
@return   
*/
typedef bool (SML_SetReferChartDataCoefId)(int index,int iNum);//

//�ڱ������й�ͨ��У׼����ϵ�����ݣ�1����
/*
@param index devindex 0~3
@param pPara 
@param dSTDF
@return   
*/
typedef bool (SML_GetReferFluxCoef)(int index,double* pPara,double dSTDF);//

//��ͨ��ϵ����1
/*
@param index devindex 0~3
@return   
*/
typedef bool (SML_SetReferFluxData)(int index);//

//��ȡ��ͨ����̽ͷ������ϵ��
/*
@param index devindex 0~3
@param pPara ��ͨ������ϵ��
@return   
*/
typedef bool (SML_GetFluxCoeff)(int index,double *pData);//

//��ȡ����⹦��
/*
@param index devindex 0~3
@param pData ��⹦��
@return   
*/
typedef bool (SML_GetInfraredLPower)(int index,double* pData);//

/*��ȡ������������*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param dx 400��ֵ
@param dy 400��ֵ
@param iCnt ֵ400
@param dss 2048��ԭʼ����ֵ
@param issCnt ֵ2048
@return   
*/
typedef bool (SML_GetAllSSPD)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK�ӹ�·�ж�ȡ
typedef bool (SML_GetAllSSPDEX)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK���ļ���ȡ
bool (SML_GetAllSSPDPLUS)(int index,double dTime,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK�ӹ�·�ж�ȡ
//typedef bool (SML_GetAllSSPDPLUS)(int index,double dTime,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK�ӹ�·�ж�ȡ

/*��ȡ������������-401*/
/*
@param index devindex 0~3
@param pPara 4������ֵ,��ʱ���� 
@param dx 401��ֵ
@param dy 401��ֵ
@param iCnt ֵ401
@param dss 2048��ԭʼ����ֵ
@param issCnt ֵ2048
@return   
*/
typedef bool (SML_GetAllSSPDCAL)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK�ӹ�·�ж�ȡ
typedef bool (SML_GetAllSSPDCALEX)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//STDK���ļ���ȡ
bool (SML_GetAllSSPDHWTRG)(int index,double* pPara,double *dx,double*dy,int *iCnt,double*dss,int *issCnt);//
//typedef bool (SML_GetAllSSPDHWTRG)(double*,double*,double*,int*,double*,int*);//
/*��ȡRgRf-RFI:double d1[2]-double d2[99]*/
/*
@param index devindex 0~3
@param pRgRf 2��ֵ��0-Rg,1-Rf
@param pRFI 99��RFIֵ
@return   
*/
typedef bool (SML_GetRGRFRFIPara)(int index,double* pRgRf,double* pRFI);//


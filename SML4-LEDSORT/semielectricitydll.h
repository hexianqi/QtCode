//�ڹ������Ҽ�ѡ����ӿ⡱��ѡ���ⲿ�� libsemielectricity.a
//��������gcc���룬���԰�ԭ����semielectricity.lib�ļ��ĳ�qt���ļ���ʽ������libsemielectricity.a
//ͬʱ��libsemielectricity.a�Լ�semielectricity.h��semielectricity.dll�ļ����ŵ�����·����
//ͬʱ�����semielectricity.dll�Լ���Ӧ��A/B/C/D�ĸ�֧��dll�ļ���������ִ�г������ڵ�·���ſ���������
//Ҫ��ȷ���ú���������Ҫ��ԭ���� typedef �ؼ���ȥ���������޷����ã�ԭ�򣿣���

//extern "C"  bool WINAPI OpenDevices();

//���庯��ָ��

/*���豸*/
/*
int���豸�ţ� 0~3
return�� 
*/
bool (SML_OpenEPDevices)(int index);//
//typedef bool (SML_OpenEPDevices)(int index);//

/*�ر��豸*/
/*
int���豸�ţ� 0~3
return��
*/
bool (SML_CloseEPDevices)(int index);//
//typedef bool (SML_CloseEPDevices)(int index);//


//
typedef bool (SML_GetEPDevSN)(int idex,unsigned char* pSN,int *iCnt);
typedef bool (SML_GetEPDevVN)(int idex,unsigned char* pVN,int *iCnt);

//���庯��
/*
ͨ����0~4 ��5��ͨ����
*/

/*���þ�Ƭ����ֵ����
 int���豸�ţ� 0~3
 int��ͨ���ţ���Ч����
 int����λֵ��*/
bool (SML_SetChipType)(int idex,int iVal);//
//typedef bool (SML_SetChipType)(int idex,int iVal);//
/*���õ�Դ��ѹ��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double����Դ��ѹֵ��*/
typedef bool (SML_SetPowerVol)(int idex,int iChan,double dVal);//
/*�������������
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double���������ֵ��*/
typedef bool (SML_SetFRWCur)(int idex,int iChan,double dVal);
/*���÷����ѹ��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double�������ѹֵ��*/
typedef bool (SML_SetBKWVol)(int idex,int iChan,double dVal);
/*���õ�����λ��0=С������1=�������
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int��������λֵ��*/
typedef bool (SML_SetCurGear)(int idex,int iChan,int iVal);
/*���ÿ���ֵ������ֵ 0=�ر� ��1=���� ��2=����
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int������ֵ��*/
bool (SML_SetSWCH)(int idex,int iChan,int iVal);
//typedef bool (SML_SetSWCH)(int idex,int iChan,int iVal);
/*���õ缫ֵ��0~3 ��4��״̬��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int���缫ֵ��*/
typedef bool (SML_SetPoleVal)(int idex,int iChan,int iVal);
/*���ù�̽ͷ��λֵ��0~3 ��4����λ��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int����λֵ��*/
typedef bool (SML_SetProbeGear)(int idex,int iChan,int iVal);
/*��ȡ�����ѹ��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*�������ѹֵ��*/
typedef bool (SML_GetFRWVol)(int idex,int iChan,double *pVal);
/*��ȡ����©����
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������©��ֵ��*/
typedef bool (SML_GetBKWCur)(int idex,int iChan,double *pVal);
/*��ȡ�������
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*�������ֵ��*/
typedef bool (SML_GetMAXCur)(int idex,int iChan,double *pVal);
/*��ȡС������
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*��С����ֵ��*/
typedef bool (SML_GetMINCur)(int idex,int iChan,double *pVal);
//PowerSource,ForwardCurrent,ForwardVoltage,ReverseCurrent,ReverseVoltage,MaxCurrent,MinCurrent

/*����У׼����������
 int���豸�ţ� 0~3
*/
bool (SML_LoadCalibrate)(int idex);
//typedef bool (SML_LoadCalibrate)(int idex);


/*fromReal��
 int���豸�ţ� 0~3
 double������ֵ��
 int��ת�����ͣ�(0-PowerSource,1-ForwardCurrent,2-ForwardVoltage,3-ReverseCurrent,4-ReverseVoltage,5-MaxCurrent,6-MinCurrent,7-ForwardCurrentL)��
 int��ͨ���ţ�
 ����ֵ double*/
typedef double (SML_FromReal)(int idex,double dval, int nType,int nChan);
/*toReal��
 int���豸�ţ� 0~3
 double������ֵ��
 int��ת�����ͣ�(0-PowerSource,1-ForwardCurrent,2-ForwardVoltage,3-ReverseCurrent,4-ReverseVoltage,5-MaxCurrent,6-MinCurrent,7-ForwardCurrentL)��
 int��ͨ���ţ�
 ����ֵ double*/
typedef double (SML_ToReal)(int idex,double dval, int nType,int nChan);

/*FastTest��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*��pVal[0] ��ѹ��pVal[1] ©����*/
typedef bool (SML_FastTest)(int idex,int iChan,double *pVal);

/*QueryEXTTrigger����ѯ�ⴥ��ֵ
 int���豸�ţ� 0~3
 ����ֵ�� false-δ���� true-�Ѵ��� */
typedef bool (SML_QueryEXTTrigger)(int idex);


/*QueryPoleVal����ѯ�缫ֵ
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int*��POL�缫ֵ��*/
typedef bool (SML_QueryPoleVal)(int idex,int iChan,int *pVal);

/*��ȡ��̽��������ֵ��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int*����̽��������ֵ��*/
typedef bool (SML_GetOPTSensor)(int idex,int iChan,int *pVal);

/*У׼��������FLASH
 int���豸�ţ� 0~3
*/
typedef bool (SML_SaveCalToFlash)(int idex);
//-------------------------------------------------------------------------------------------
/*����VFL��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestVFL)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����VF��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestVF)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����VRL��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestVRL)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����IF��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestIF)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����IR��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestIR)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����IV��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestIV)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����VRP��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestVRP)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

/*����PROBE��
 int���豸�ţ� 0~3
 int����ʱʱ��ms
 int��ͨ���ţ�
 double*������ֵ��0~3��POLֵ�����صƣ���ѹ��������
 double*����������أ�ֵ��0~3��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestPROBE)(int idex,int nTMS,int iChan,double *pValIn,double *pValOut);

//--------------------------------------------------------------------------
/*����VFL��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDVFL)(int idex,int iChan,double *pValIn);

/*����VF��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDVF)(int idex,int iChan,double *pValIn);

/*����VRL��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDVRL)(int idex,int iChan,double *pValIn);

/*����IF��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDIF)(int idex,int iChan,double *pValIn);

/*����IR��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDIR)(int idex,int iChan,double *pValIn);

/*����IV��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDIV)(int idex,int iChan,double *pValIn);

/*����VRP��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDVRP)(int idex,int iChan,double *pValIn);

/*����PROBE��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDPROBE)(int idex,int iChan,double *pValIn);

/*����DF1��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDDF1)(int idex,int iChan,double *pValIn);

/*����DF2��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDDF2)(int idex,int iChan,double *pValIn);//_SetPDDF2@8

/*����DF3��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDDF3)(int idex,int iChan,double *pValIn);//_SetPDDF3@8

/*����DF4��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2����ʱ����ѹ��������*/
typedef bool (SML_SetPDDF4)(int idex,int iChan,double *pValIn);//_SetPDDF4@8

/*����POL��
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~4����ʱ����ѹ�����������ޣ����ޣ�*/
bool (SML_SetPDPOL)(int idex,int iChan,double *pValIn);//_SetPDPOL@8
//typedef bool (SML_SetPDPOL)(int idex,int iChan,double *pValIn);//_SetPDPOL@8

/*��ϲ��ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~2��POLֵ�����صƣ������Ŀ��
 double*����������أ�ֵ��38�ֽڣ���0~19��POLֵ�����صƣ�Ԥ��������ֵ��*/
typedef bool (SML_TestCOMBINED)(int idex,int iChan,double *pValIn,double *pValOut);//_TestCOMBINED@12

/*������ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 int��iType:1.VFL;2.VF;3.VRL;4.IF;5.IR;6.IV;7.VPR;8.̽����
 double*������ֵ��0~1��POLֵ�����صƣ�
 double*������ֵ��0~2����ʱ����ѹ��������
 double*����������أ�ֵ��0~2��POLֵ��0ʧ�ܣ�1��·��2��·��3����4����5������90�ȣ�6������270�ȣ������صƣ���Ӧ�����ֵ��*/
typedef bool (SML_TestSINGLED)(int idex,int iChan,int iType,double *pValIn1,double *pValIn2,double *pValOut);

/*��̲��ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ(202���ֽ�)��0~1��POLֵ�����صƣ�2~201��(50*4=200)��50��������Ŀ��
 double*����������أ�ֵ(153���ֽڣ���0-POLֵ��1-����ֵ��2-POL�ĵ�ѹֵ��3~152:(50*3=150):50��������Ŀ�Ľ��ֵ(3�����ݣ�1-������Ŀ��2��3-��Ӧ�Ľ������)*/
bool (SML_TestPROGRAM)(int idex,int iChan,double *pValIn,double *pValOut);//
//typedef bool (SML_TestPROGRAM)(int idex,int iChan,double *pValIn,double *pValOut);//

/*��Ŷ�·���ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��2�����ݣ�0-��Դ��ѹ��1-���������
 double*����������أ�ֵ��8�����ݣ�0-��1,2��״̬����1-�����ѹ��2-��2,3��״̬����3-�����ѹ��4-��3,4��״̬����5-�����ѹ,6-��4,1��״̬����7-�����ѹ��*/
typedef bool (SML_TestPINSHORT)(int idex,int iChan,double *pValIn,double *pValOut);//,double *pValOutOrg
/*
int;�豸�ţ� 0~3
double*:0~2��(��ʱ,0,0);
double*:0~2��(��ѹ,0,0);
double*:0~2��(����,0,0);
double*:0~2��(Min,0,0);
double*:0~2��(Max,0,0);
*/
typedef bool (SML_SetVFLCondition)(int,double*,double*,double*,double*,double*);//_SML_SetVFLCondition@24
typedef bool (SML_SetVFCondition)(int,double*,double*,double*,double*,double*);//_SML_SetVFCondition@24
typedef bool (SML_SetIRCondition)(int,double*,double*,double*,double*,double*);//_SML_SetIRCondition@24

//typedef bool (SML_DoTest)(int,double*);//_SML_DoTest@8
 /*���ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*����������أ�ֵ��0~5��POLֵ��0ʧ�ܣ�1��·��2��·��3����4����5������90�ȣ�6������270�ȣ����ϸ�ֵ��POL��ֵ��VFLֵ��VFֵ��IRֵ��
*/
typedef bool (SML_DoTest)(int,int,double*);//

/*��ȡ�¶Ȳ���ֵ��
 int���豸�ţ� 0~3
 double*���¶Ȳ���ֵ��*/
typedef bool (SML_GetTmpVal)(int idex,double *pVal);
/*��ȡʪ�Ȳ���ֵ��
 int���豸�ţ� 0~3
 double*��ʪ�Ȳ���ֵ��*/
typedef bool (SML_GetHumVal)(int idex,double *pVal);

typedef bool (SML_GetSVolVal)(int idex,int ichan,double *pVal);

/*���ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*������ֵ��0~5��POLֵ�����صƣ����ÿ���ֵ����ʱ����ѹ��������
 int*��0-������1-��·��2-��·��
*/
//typedef bool (SML_ProTest)(int idex,int ichan,double *pValIn);//
typedef bool (SML_ProTest)(int idex,int ichan,double *pValIn,int *pSTOut);//

/*���ԣ�
 int���豸�ţ� 0~3
 int��ͨ���ţ�
 double*����������أ�ֵ��0~5��POLֵ��0ʧ�ܣ�1��·��2��·��3����4����5������90�ȣ�6������270�ȣ����ϸ�ֵ��POL��ֵ��VFLֵ��VFֵ��IRֵ��
 return:-1��ʧ�ܣ�0��δ������1���Ѵ���
*/
//typedef int (SML_TrgTest)(int idex,int ichan,double *pDataout);
typedef int (SML_TrgTest)(int idex,int ichan,double *pDataout);


typedef int (SML_SaveToFlash)(int idex);

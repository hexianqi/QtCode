/***************************************************************************************************
**      2019-07-12  HLogRedirectService 日志重定向服务。
**                  http://www.qtcn.org/bbs/read-htm-tid-85387-ds-1.html#tpc
***************************************************************************************************/

#pragma once

#include "HAbstractService.h"
#include "HSingleton3.h"

HE_BEGIN_NAMESPACE

class HLogRedirectServicePrivate;

class HLogRedirectService : public HAbstractService
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLogRedirectService)
    H_SINGLETON3(HLogRedirectService)

public:
    enum MsgType
    {
        MsgType_Debug       = 0x00000001,
        MsgType_Info        = 0x00000002,
        MsgType_Warning     = 0x00000004,
        MsgType_Critical    = 0x00000008,
        MsgType_Fatal       = 0x00000010,
        MsgType_All         = 0xFFFFFFFF
     };
    Q_DECLARE_FLAGS(MsgTypes, MsgType)

private:
    HLogRedirectService(QObject *parent = nullptr);
    ~HLogRedirectService() override;

public:
signals:
    void output(const QString &value);

public:
    bool start() override;
    bool stop() override;

public:
    bool isFilter(const QtMsgType &);
    bool isUseTime();
    bool isUseContext();
    void setMsgType(const MsgType &);       // 设置输出消息类型
    void setUseTime(bool);                  // 设置是否输出时间
    void setUseContext(bool);               // 设置是否输出日志上下文
    void save(const QString &content);
};

HE_END_NAMESPACE

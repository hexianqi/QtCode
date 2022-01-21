/***************************************************************************************************
**      2018-06-19  HCoreGlobalInstance 全局进程类。[只能保证同一个Dll内唯一性，不同的Dll都初始化一次]
***************************************************************************************************/

#pragma once

#include "HSingleton.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HCoreGlobalInstance : public QObject, public HSingleton<HCoreGlobalInstance>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HCoreGlobalInstance)

public:
    void init();

protected:
    HCoreGlobalInstance(QObject *parent = nullptr);
    ~HCoreGlobalInstance();

protected:
    void initLogCommand();
    void initActionComment();
    void initErrorComment();
    void initDataFormatInfo();
    void initDataCaption();
    void initDataGroup();
    void initMimeType();

private:
    bool _initialized = false;
};

HE_END_NAMESPACE

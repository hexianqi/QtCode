/***************************************************************************************************
**      2018-06-19  HCoreGlobalInstance 全局进程类。[只能保证同一个Dll内唯一性，不同的Dll都初始化一次]
***************************************************************************************************/

#ifndef HCOREGLOBALINSTANCE_H
#define HCOREGLOBALINSTANCE_H

#include "HSingleton.h"
#include <QtCore/QObject>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HCoreGlobalInstance : public QObject, public HSingleton<HCoreGlobalInstance>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HCoreGlobalInstance)

protected:
    HCoreGlobalInstance(QObject *parent = nullptr);
    ~HCoreGlobalInstance();

protected:
    void initLogCommand();
    void initActionComment();
    void initErrorComment();
    void initDataFormatInfo();
    void initDataCaption();
    void initMimeType();
};

HE_CORE_END_NAMESPACE

#endif // HCOREGLOBALINSTANCE_H

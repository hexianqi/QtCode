/***************************************************************************************************
**      2018-06-19  HCoreGlobalInstance 全局进程类。[只能保证同一个Dll内唯一性，不同的Dll都初始化一次]
***************************************************************************************************/

#pragma once

#include "HSingleton3.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HCoreGlobalInstancePrivate;

class HCoreGlobalInstance : public QObject
{
    Q_OBJECT
    H_SINGLETON3(HCoreGlobalInstance)

public:
    void initialize();
    void startLogService();
    void stopLogService();

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
    QScopedPointer<HCoreGlobalInstancePrivate> d_ptr;
};

HE_END_NAMESPACE

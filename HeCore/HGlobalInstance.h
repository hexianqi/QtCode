/***************************************************************************************************
**      2018-06-19  HGlobalInstance 全局进程类。[只能保证同一个Dll内唯一性，不同的Dll都初始化一次]
***************************************************************************************************/

#ifndef HGLOBALINSTANCE_H
#define HGLOBALINSTANCE_H

#include "HSingleton.h"
#include <QObject>

HE_CORE_BEGIN_NAMESPACE

class HGlobalInstancePrivate;

class HE_CORE_EXPORT HGlobalInstance : public QObject, public HSingleton<HGlobalInstance>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HGlobalInstance)

protected:
    HGlobalInstance(QObject *parent = nullptr);
    HGlobalInstance(HGlobalInstancePrivate &p, QObject *parent = nullptr);
    ~HGlobalInstance();

protected:
    void initActionComment();
    void initErrorComment();
    void initDataFormatInfo();
    void initDataCaption();
    void initMimeType();

protected:
    QScopedPointer<HGlobalInstancePrivate> d_ptr;
};

HE_CORE_END_NAMESPACE

#endif // HGLOBALINSTANCE_H

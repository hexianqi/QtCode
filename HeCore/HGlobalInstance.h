/***************************************************************************************************
**      2018-06-19  HGlobalInstance 全局进程类。
***************************************************************************************************/

#ifndef HGLOBALINSTANCE_H
#define HGLOBALINSTANCE_H

#include "HSingleton.h"
#include <QObject>

HE_CORE_BEGIN_NAMESPACE

class HGlobalInstancePrivate;

class HGlobalInstance : public QObject, public HSingleton<HGlobalInstance>
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

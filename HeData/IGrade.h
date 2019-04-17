/***************************************************************************************************
**      2019-04-16  IGrade 分级数据接口。
***************************************************************************************************/

#ifndef IGRADE_H
#define IGRADE_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IGrade : public IInitializeable
{
public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADE_H

/***************************************************************************************************
**      2019-04-26  IDataCollection 数据集接口。
***************************************************************************************************/

#ifndef IDATACOLLECTION_H
#define IDATACOLLECTION_H

#include "HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class IFileStream;

class IDataCollection
{
public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
    // 设置使用索引
    virtual void setUseIndex(QString value) = 0;
    // 使用的索引
    virtual QString useIndex() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATACOLLECTION_H

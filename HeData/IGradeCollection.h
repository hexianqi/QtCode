/***************************************************************************************************
**      2019-04-16  IGradeCollection 分级数据集合接口。
***************************************************************************************************/

#ifndef IGRADECOLLECTION_H
#define IGRADECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream;
class IGrade;

class IGradeCollection : virtual public ICollection<IGrade>
{
public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADECOLLECTION_H

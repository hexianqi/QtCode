/***************************************************************************************************
**      2020-09-30  IXlsxStream Xlsx流接口。
***************************************************************************************************/


#pragma once

#include "IStream.h"

namespace QXlsx {
class Document;
}

using namespace QXlsx;

HE_BEGIN_NAMESPACE

class IXlsxStream : public virtual IStream
{
public:
    // 设置读取内容函数
    virtual void setReadContent(std::function<void(Document *)> func) = 0;
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(Document *)> func) = 0;
    // 读取内容
    virtual bool readContent(Document *) = 0;
    // 写入内容
    virtual bool writeContent(Document *) = 0;
};

HE_END_NAMESPACE

/***************************************************************************************************
**      2020-09-30  IXlsxStream Xlsx流接口。
***************************************************************************************************/


#pragma once

#include "HAbstractStream.h"
#include <functional>

namespace QXlsx {
class Document;
}
using namespace QXlsx;

HE_DATA_BEGIN_NAMESPACE

class IXlsxStream : public HAbstractStream
{
public:
    using HAbstractStream::HAbstractStream;

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

HE_DATA_END_NAMESPACE

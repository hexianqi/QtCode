/***************************************************************************************************
**      2020-09-29  ITextStream 文本流接口。
***************************************************************************************************/

#pragma once

#include "IStream.h"

class QTextStream;

HE_BEGIN_NAMESPACE

class ITextStream : public virtual IStream
{
public:
    // 设置内容
    virtual void setContent(QString value) = 0;
    // 获取内容
    virtual QString content() = 0;
    // 设置读取内容函数
    virtual void setReadContent(std::function<void(QTextStream &)> func) = 0;
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(QTextStream &)> func) = 0;
    // 读取内容
    virtual bool readContent(QTextStream &) = 0;
    // 写入内容
    virtual bool writeContent(QTextStream &) = 0;
    // 追加内容
    virtual bool appendFile(QString fileName) = 0;
};

HE_END_NAMESPACE


/***************************************************************************************************
**      2020-09-30  IXlsxStream Xlsx流接口。
***************************************************************************************************/


#pragma once

#include "HAbstractStream.h"
#include "xlsxglobal.h"
#include <functional>

QT_BEGIN_NAMESPACE_XLSX
class Document;
QT_END_NAMESPACE_XLSX

HE_DATA_BEGIN_NAMESPACE

class IXlsxStream : public HAbstractStream
{
public:
    using HAbstractStream::HAbstractStream;

public:
    // 设置读取内容函数
    virtual void setReadContent(std::function<void(QXlsx::Document *)> func) = 0;
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(QXlsx::Document *)> func) = 0;
    // 读取内容
    virtual bool readContent(QXlsx::Document *) = 0;
    // 写入内容
    virtual bool writeContent(QXlsx::Document *) = 0;
};

HE_DATA_END_NAMESPACE

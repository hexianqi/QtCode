/***************************************************************************************************
**      2019-06-10  ILogFile 日志文件接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QStringList>

HE_BEGIN_NAMESPACE

class ILogFile
{
public:
    // 设置文件存放路径
    virtual void setPath(const QString &) = 0;
    // 设置文件名称
    virtual void setName(const QString &) = 0;
    // 设置日期格式
    virtual void setDataTimeFormat(const QString &) = 0;
    // 读取
    virtual QStringList readLines() = 0;
    virtual QString readAll() = 0;
    // 写入
    virtual bool write(const QStringList &) = 0;
    virtual bool write(const QString &) = 0;
    // 追加
    virtual bool append(const QStringList &) = 0;
    virtual bool append(const QString &) = 0;
};

HE_END_NAMESPACE

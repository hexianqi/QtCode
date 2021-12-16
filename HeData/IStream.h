/***************************************************************************************************
**      2020-09-29  IStream 流接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <functional>

HE_BEGIN_NAMESPACE

class IStream : public IInitializeable
{
public:
    // 获取文件过滤
    virtual QString fileFilter() = 0;
    // 设置文件过滤
    virtual void setFileFilter(QString value) = 0;
    // 打开文件
    virtual bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) = 0;
    // 另存文件
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) = 0;
    // 读取文件
    virtual bool readFile(QString fileName) = 0;
    // 写入文件
    virtual bool writeFile(QString fileName) = 0;
};

HE_END_NAMESPACE

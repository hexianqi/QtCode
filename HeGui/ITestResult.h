/***************************************************************************************************
**      2021-01-26
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeData/HDataGlobal.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestResult : public IInitializeable
{
public:
    //
    virtual ITestData *at(int i) = 0;
    // 最后一次结果
    virtual ITestData *last() = 0;
    // 是否为空
    virtual bool isEmpty() = 0;
    // 大小
    virtual int size() = 0;
    // 清除
    virtual void clear() = 0;
    // 保存
    virtual void save(bool append = true) = 0;
    // 删除
    virtual void remove(int index, int count) = 0;
    // 设置修改
    virtual void setModified(bool b = true) = 0;
    // 设置同步项
    virtual void setSyncType(QStringList) = 0;
    // 设置同步文件
    virtual void setSyncFile(const QString &) = 0;
    // 同步文件
    virtual void syncFile() = 0;
};

HE_GUI_END_NAMESPACE

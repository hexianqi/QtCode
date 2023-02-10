/***************************************************************************************************
**      2021-01-26  ISyncTestResult 测试结果同步集接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class ITestData;

class ISyncTestResult : public IInitializeable
{
public:
    // 结果
    virtual ITestData *at(int i) = 0;
    // 最后结果
    virtual ITestData *last() = 0;
    // 是否为空
    virtual bool isEmpty() = 0;
    // 大小
    virtual int size() = 0;
    // 清除
    virtual void clear() = 0;
    // 更新
    virtual void update(bool append) = 0;
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

HE_END_NAMESPACE

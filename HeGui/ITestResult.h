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
    virtual ITestData *at(int i) = 0;
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
    // 设置导出项
    virtual void setExportTypes(QStringList) = 0;
    // 设置导出路径
    virtual void setExportPathName(const QString &) = 0;
    // 设置同步文件名
    virtual void setSyncFileName(const QString &) = 0;
    // 打印预览
    virtual void printPreviewLast() = 0;
    // 导出到数据库
    virtual void exportDatabase(int index, int count) = 0;
    virtual void exportDatabaseLast() = 0;
    virtual void exportDatabaseAll() = 0;
    // 导出到Excel
    virtual void exportExcel(int index, int count) = 0;
    virtual void exportExcelLast() = 0;
    virtual void exportExcelAppend() = 0;
    // 同步文件
    virtual void syncFile() = 0;
};

HE_GUI_END_NAMESPACE

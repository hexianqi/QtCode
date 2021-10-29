/***************************************************************************************************
**      2018-06-19  ITestData 测试数据接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtCore/QVariant>

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ITestData : public IInitializeable
{
public:
    virtual ~ITestData() = default;

public:
    // 设置后继者
    virtual ITestData *setSuccessor(ITestData *) = 0;
    // 设置校准数据
    virtual bool setCalibrate(void *) = 0;
    // 是否包含
    virtual bool contains(QString type) = 0;
    // 设置数据
    virtual void setData(QString type, QVariant value) = 0;
    // 设置数据
    virtual void setData(QVariantMap value) = 0;
    // 添加数据
    virtual void addData(QString type, QVariant value) = 0;
    // 添加数据
    virtual void addData(QVariantMap value) = 0;
    // 获取数据
    virtual QVariant data(QString type) = 0;
    // 挑选数据
    virtual QVariantMap select(QStringList type) = 0;
    // 复制数据
    virtual QVariantMap cloneData() = 0;
    // 创建当前实例副本的新对象。
    virtual ITestData *clone() = 0;
    // 获取数据-按字符串格式
    virtual QString toString(QString type) = 0;
    // 获取数据-按字符串格式
    virtual QStringList toString(QStringList type) = 0;
    // 获取数据-按Html表格方式
    virtual QString toHtmlTable(QStringList type, QColor bgcolor) = 0;
    // 处理操作
    virtual QVariant handleOperation(QString type, QVariant value = QVariant()) = 0;
};

HE_DATA_END_NAMESPACE

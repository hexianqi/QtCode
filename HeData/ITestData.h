/***************************************************************************************************
**      2018-06-19  ITestData 测试数据接口。
***************************************************************************************************/

#ifndef ITESTDATA_H
#define ITESTDATA_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtCore/QVariant>

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ITestData : public IInitializeable
{
public:
    // 设置后继者
    virtual void setSuccessor(ITestData *) = 0;
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

#endif // ITESTDATA_H

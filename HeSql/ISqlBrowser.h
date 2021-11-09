/***************************************************************************************************
**      2019-05-09  ISqlBrowser 数据库浏览器接口。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;
class ISqlHandle;
class ISqlOutput;

class ISqlBrowser : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;
    // 设置记录处理
    virtual void setRecordHandle(ISqlHandle *) = 0;
    // 设置记录输出
    virtual void setRecordOutput(ISqlOutput *) = 0;
    // 记录还原
    virtual void revert() = 0;
};

HE_SQL_END_NAMESPACE

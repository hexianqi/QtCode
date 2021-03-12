/***************************************************************************************************
**      2019-04-30  IDataEditWidget 数据编辑窗体接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

template <typename T>
class IDataEditWidget : public QWidget, public IInitializeable
{
public:
    using QWidget::QWidget;

public:
    // 创建数据
    virtual T *createData() = 0;
    // 设置数据
    virtual void setData(T *) = 0;
    // 清除数据
    virtual void clearData() = 0;
    // 保存数据
    virtual void saveData() = 0;
    // 显示数据
    virtual void showData() = 0;
};

HE_GUI_END_NAMESPACE

/***************************************************************************************************
**      2019-04-30  IDataEditWidget 数据编辑窗体接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"

class QWidget;

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

template <typename T>
class IDataEditer : public IInitializeable
{
public:
    // 编辑窗体
    virtual QWidget *widget() = 0;
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

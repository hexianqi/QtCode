/***************************************************************************************************
**      2019-06-12  IStyle 样式接口。
***************************************************************************************************/

#ifndef ISTYLE_H
#define ISTYLE_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IStyle : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 按钮样式
    virtual QString pushButton(QVariantMap param = QVariantMap()) = 0;
    // 文本框样式
    virtual QString lineEdit(QVariantMap param = QVariantMap()) = 0;
    // 进度条样式
    virtual QString progressBar(QVariantMap param = QVariantMap()) = 0;
    // 滑块条样式
    virtual QString slider(QVariantMap param = QVariantMap()) = 0;
    // 单选框样式
    virtual QString radioButton(QVariantMap param = QVariantMap()) = 0;
    // 复选框样式
    virtual QString checkBox(QVariantMap param = QVariantMap()) = 0;
    // 滚动条样式
    virtual QString scrollBar(QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ISTYLE_H

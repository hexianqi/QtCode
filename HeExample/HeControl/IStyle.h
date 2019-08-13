/***************************************************************************************************
**      2019-07-19  IStyle 样式接口。
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
    // 样式表
    virtual QString toStyleSheet() = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ISTYLE_H

/***************************************************************************************************
**      2019-07-19  IQssStyle Qss样式接口。
***************************************************************************************************/

#ifndef IQSSSTYLE_H
#define IQSSSTYLE_H

#include "IStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class IQssStyle : public IStyle
{
    Q_OBJECT

public:
    using IStyle::IStyle;

public:
    // 所有样式
    virtual QStringList keys() = 0;
    // 选择样式
    virtual bool selectStyle(QString vlaue) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // IQSSSTYLE_H

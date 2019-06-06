/***************************************************************************************************
**      2019-06-04  HControlHelper 帮助类。
***************************************************************************************************/

#ifndef HCONTROLHELPER_H
#define HCONTROLHELPER_H

#include "HControlGlobal.h"

class QWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HControlHelper
{
public:
    // 窗体居中桌面
    static void centerWidget(QWidget *);
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLHELPER_H

/***************************************************************************************************
**      2019-06-04  HControlHelper 控件帮助类。
***************************************************************************************************/

#ifndef HCONTROLHELPER_H
#define HCONTROLHELPER_H

#include "HControlGlobal.h"

class QWidget;
class QDateTime;

HE_CONTROL_BEGIN_NAMESPACE

class HControlHelper
{
public:
    // 初始化翻译
    static void initTranslator();
    // 窗体居中桌面
    static void centerWidget(QWidget *);
    // 运行时间
    static QString runTime(QDateTime start, QDateTime end);
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLHELPER_H

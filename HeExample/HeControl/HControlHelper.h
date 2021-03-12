/***************************************************************************************************
**      2019-06-04  HControlHelper 控件帮助类。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QStringList;
class QDateTime;
class QWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HControlHelper : public QObject
{
public:
    // 初始化翻译
    static void initTranslator();
    // 运行时间
    static QString runTime(const QDateTime &start, const QDateTime &end);
    // 转为HH:mm:ss格式
    static QString secsToTime(qlonglong value);

public:
    // 窗体居中桌面
    static void centerWidget(QWidget *);
    // 无边框窗体
    static void framelessWidget(QWidget *, bool moveEnable = true, bool resizeEnable = true);
    // 无边框背景窗体
    static void translucentWidget(QWidget *, const QStringList &files, bool moveEnable = true);

public:
    // 添加关闭
    static void addClose(QWidget *);
};

HE_CONTROL_END_NAMESPACE

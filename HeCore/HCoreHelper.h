/***************************************************************************************************
**      2019-05-07  HCoreHelper 帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HCoreHelper
{
public:
    // 选择
    static QStringList unselected(QStringList optional, QStringList selected);
    // 合并
    static QVariantMap unite(QVariantMap m1, const QVariantMap &m2);
    // 延时
    static void msleep(int msecs);
    static void msleep2(int msecs);
    // 根据背景色自动计算合适的前景色
    static QColor calcForeColor(QColor backColor);
    // 读取配置文件
    static void readSettings(const QString &fileName, const QString &prefix, QVariantMap &params);
    // 写入配置文件
    static void writeSettings(const QString &fileName, const QString &prefix, const QVariantMap &params);
};

HE_END_NAMESPACE

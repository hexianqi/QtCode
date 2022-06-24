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

public:
    // 延时
    static void msleep(int msecs);
    static void msleep2(int msecs);

public:
    // 根据背景色自动计算合适的前景色
    static QColor calcForeColor(QColor backColor);

public:
    // 读取配置文件
    static void readSettings(const QString &fileName, const QString &prefix, QVariantMap &params);
    // 写入配置文件
    static void writeSettings(const QString &fileName, const QString &prefix, const QVariantMap &params);

public:
    // 安装翻译文件
    static void installTranslator(const QString &fileName);
};

HE_END_NAMESPACE

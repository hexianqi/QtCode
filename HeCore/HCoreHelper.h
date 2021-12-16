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
    // 延时
    static void msleep(int msecs);
    static void msleep2(int msecs);
    // 转储结构
    static void dumpStructure(const QObject *obj, int spaceCount);
    // 读取配置文件
    static void readSettings(QString fileName, QString prefix, QVariantMap &params);
    // 写入配置文件
    static void writeSettings(QString fileName, QString prefix, QVariantMap params);
};

HE_END_NAMESPACE

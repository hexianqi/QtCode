/***************************************************************************************************
**      2018-06-19  各种转换函数。
***************************************************************************************************/

#pragma once

#include "HLogType.h"
#include "HActionType.h"
#include "HErrorType.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HDataFormatInfo;

class HCore
{
public:
    static const char *toCommand(HLogType type);

public:
    static QString toJson(QVariantMap);
    static QVariantMap fromJson(QString);

public:
    static QString toComment(HActionType type);
    static QString toComment(HErrorType type);

public:
    static HDataFormatInfo *toFormatInfo(const QString &type);
    static QString toString(const QString &type, double value, char f = 'f');
    static QString toString(const QString &type, const QVariant &value);
    static QStringList toString(const QString &type, QVector<double> value, char f = 'f');
    static QString toUnit(const QString &type);
    static QString toCaption(const QString &type);
    static QStringList toCaption(QStringList type);
    static QString toCaptionUnit(const QString &type);
    static QStringList toCaptionUnit(const QStringList &type);

public:
    static QStringList membership(const QString &name);
    static QStringList membership(const QStringList &name);

public:
    static QString fileNameFilter(const QString &name, const QList<QByteArray> &formats);
    static QString fileNameFilter(const QString &name, const QStringList &mimeTypes);

public:
    static QString typeAddition(const QString &type, const QString &addition);
};

HE_END_NAMESPACE

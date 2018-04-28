#ifndef HCORE_H
#define HCORE_H

#include "HActionType.h"
#include "HErrorType.h"

class QVariant;
class QStringList;

HE_CORE_BEGIN_NAMESPACE

class HDataFormatInfo;

HE_CORE_EXPORT QString toComment(HActionType type);
HE_CORE_EXPORT QString toComment(HErrorType type);

HE_CORE_EXPORT HDataFormatInfo *toFormatInfo(QString type);
HE_CORE_EXPORT QString toString(QString type, double value, char f = 'f');
HE_CORE_EXPORT QString toString(QString type, QVariant value);

HE_CORE_EXPORT QString toUnit(QString type);
HE_CORE_EXPORT QString toCaption(QString type);
HE_CORE_EXPORT QStringList toCaption(QStringList types);
HE_CORE_EXPORT QString toCaptionUnit(QString type);
HE_CORE_EXPORT QStringList toCaptionUnit(QStringList types);

HE_CORE_EXPORT void msleep(int msecs);

HE_CORE_EXPORT QString filenameFilter(const QString &name, const QList<QByteArray> formats);
HE_CORE_EXPORT QString filenameFilter(const QString &name, const QStringList &mimeTypes);

HE_CORE_END_NAMESPACE

#endif // HCORE_H

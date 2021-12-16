/***************************************************************************************************
**      2018-06-19  HDataFormatInfo 数据格式信息类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QSharedDataPointer>
#include <QtGui/QColor>

class QObject;
class QDoubleValidator;
class QIntValidator;

HE_BEGIN_NAMESPACE

class HDataFormatInfoPrivate;

class HDataFormatInfo
{
public:
    HDataFormatInfo();
    HDataFormatInfo(const QString &typeName, double min = 0, double max = 65535, int decimals = 0, double singleStep = 1);
    HDataFormatInfo(const QString &typeName, const QString &unit, double min, double max, int decimals = 0, double singleStep = 1, const QColor &color = Qt::black);
    HDataFormatInfo(const HDataFormatInfo &);
    HDataFormatInfo &operator=(const HDataFormatInfo &);
    ~HDataFormatInfo();

public:
    void setTypeName(const QString &value);
    void setUnit(const QString &value);
    void setColor(const QColor &value);
    void setDecimals(int value);
    void setMin(double value);
    void setMax(double value);
    void setRange(double min, double max, int decimals = 0);
    void setSingleStep(double value);

public:
    QString typeName() const;
    QString unit(bool withColor = true) const;
    QColor color() const;
    int decimals() const;
    double min() const;
    double max() const;
    double singleStep() const;

public:
    QDoubleValidator *toDoubleValidator(QObject *parent);
    QIntValidator *toIntValidator(QObject *parent);

protected:
    HDataFormatInfo(HDataFormatInfoPrivate &);

protected:
    QSharedDataPointer<HDataFormatInfoPrivate> d_ptr;
};

HE_END_NAMESPACE

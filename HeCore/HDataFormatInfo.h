#ifndef HDATAFORMATINFO_H
#define HDATAFORMATINFO_H

#include "HCoreGlobal.h"
#include <QSharedDataPointer>
#include <QColor>

class QObject;
class QDoubleValidator;
class QIntValidator;

HE_CORE_BEGIN_NAMESPACE

class HDataFormatInfoPrivate;

// 数据格式信息类
class HE_CORE_EXPORT HDataFormatInfo
{
public:
    HDataFormatInfo();
    HDataFormatInfo(QString typeName, double min = 0, double max = 0, int decimals = 0, double singleStep = 1);
    HDataFormatInfo(QString typeName, QString unit, double min, double max, int decimals = 0, double singleStep = 1, QColor color = Qt::black);
    HDataFormatInfo(const HDataFormatInfo &);
    HDataFormatInfo &operator=(const HDataFormatInfo &);
    ~HDataFormatInfo();

public:
    void setTypeName(QString value);
    void setUnit(QString value);
    void setColor(QColor value);
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
    QDoubleValidator *toDoubleValidator(QObject * parent);
    QIntValidator *toIntValidator(QObject * parent);

protected:
    HDataFormatInfo(HDataFormatInfoPrivate &p);

protected:
    QSharedDataPointer<HDataFormatInfoPrivate> d_ptr;
};

HE_CORE_END_NAMESPACE

#endif // HDATAFORMATINFO_H

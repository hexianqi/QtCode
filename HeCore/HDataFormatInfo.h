#ifndef HDATAFORMATINFO_H
#define HDATAFORMATINFO_H

#include "HeCore_global.h"
#include <QColor>

class QObject;
class QDoubleValidator;
class QIntValidator;

namespace He {
namespace Core {

// 数据格式信息类
class HECORE_EXPORT HDataFormatInfo
{
public:
    HDataFormatInfo();
    HDataFormatInfo(QString type, double min = 0, double max = 0, int decimals = 0, double singleStep = 1);
    HDataFormatInfo(QString type, QString unit, double min, double max, int decimals = 0, double singleStep = 1, QColor color = Qt::black);

public:
    void initialize(QString type, QString unit = "", double min = 0, double max = 65535, int decimals = 0, double singleStep = 1, QColor color = Qt::red);
    void setType(QString value);
    void setUnit(QString value);
    void setColor(QColor value);
    void setDecimals(int value);
    void setBotton(double value);
    void setTop(double value);
    void setRange(double min, double max, int decimals = 0);
    void setSingleStep(double value);

public:
    QString type() const { return _type; }
    QString unit(bool color = true) const;
    QColor color() const { return _color; }
    int decimals() const { return _decimals; }
    double botton() const { return _botton; }
    double top() const { return _top; }
    double singleStep() const { return _singleStep; }

public:
    QDoubleValidator *toDoubleValidator(QObject * parent);
    QIntValidator *toIntValidator(QObject * parent);

protected:
    QString _type;
    QString _unit;
    QColor _color;
    int _decimals;
    double _botton;
    double _top;
    double _singleStep;
};

} // Core
} // He

#endif // HDATAFORMATINFO_H

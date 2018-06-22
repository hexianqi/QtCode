/***************************************************************************************************
**      2018-06-19  HSpecFitting 光谱拟合数据类。
***************************************************************************************************/

#ifndef HSPECFITTING_H
#define HSPECFITTING_H

#include "HDataGlobal.h"
#include <QVariant>

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate;

class HSpecFitting
{
public:
    explicit HSpecFitting();
    ~HSpecFitting();

public:
    void restoreDefault();
    void setData(QString name, QVariant value);
    QVariant data(QString name);

public:
    double handle(double value, bool abovezero = true);
    QVector<double> handle(QVector<double> value, bool abovezero = true);

protected:
    HSpecFitting(HSpecFittingPrivate &p);

protected:
    QScopedPointer<HSpecFittingPrivate> d_ptr;

private:
    friend QDataStream &operator<<(QDataStream &, const HSpecFitting &);
    friend QDataStream &operator>>(QDataStream &, HSpecFitting &);
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_H

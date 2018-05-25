#ifndef HSPECLUMINOUS_H
#define HSPECLUMINOUS_H

#include "HDataGlobal.h"
#include <QVariant>

HE_DATA_BEGIN_NAMESPACE

class HSpecLuminousPrivate;

class HSpecLuminous
{
public:
    explicit HSpecLuminous();
    ~HSpecLuminous();

public:
    void restoreDefault();
    void setData(QString name, QVariant value);
    QVariant data(QString name);

public:
    double handle(double value);

protected:
    HSpecLuminous(HSpecLuminousPrivate &p);

protected:
    QScopedPointer<HSpecLuminousPrivate> d_ptr;

private:
    friend QDataStream &operator<<(QDataStream &, const HSpecLuminous &);
    friend QDataStream &operator>>(QDataStream &, HSpecLuminous &);
};

HE_DATA_END_NAMESPACE

#endif // HSPECLUMINOUS_H

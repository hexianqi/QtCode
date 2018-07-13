/***************************************************************************************************
**      2018-07-10  HAbstractCalibrateItem 抽象校准子项。
***************************************************************************************************/

#ifndef HABSTRACTCALIBRATEITEM_H
#define HABSTRACTCALIBRATEITEM_H

#include "HDataGlobal.h"
#include <QVariant>

HE_DATA_BEGIN_NAMESPACE

class HAbstractCalibrateItemPrivate;

class HAbstractCalibrateItem
{
public:
    explicit HAbstractCalibrateItem();
    ~HAbstractCalibrateItem();

public:
    virtual void restoreDefault() = 0;
    virtual void setData(QString name, QVariant value);
    virtual QVariant data(QString name);

public:
    virtual void readContent(QDataStream &) = 0;
    virtual void writeContent(QDataStream &) = 0;

protected:
    HAbstractCalibrateItem(HAbstractCalibrateItemPrivate &p);

protected:
    QScopedPointer<HAbstractCalibrateItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTCALIBRATEITEM_H

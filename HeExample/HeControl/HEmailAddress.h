/***************************************************************************************************
**      2019-12-25  HEmailAddress
***************************************************************************************************/

#ifndef HEMAILADDRESS_H
#define HEMAILADDRESS_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HEmailAddressPrivate;

class HEmailAddress : public QObject
{
    Q_OBJECT

public:
    explicit HEmailAddress(QObject *parent = nullptr);
    explicit HEmailAddress(const QString &address, const QString &name = QString(), QObject *parent = nullptr);
    ~HEmailAddress();

public:
    static HEmailAddress *fromString(const QString &value, QObject *parent = nullptr);

public:
    QString name() const;
    QString address() const;

public:
    void setName(const QString &value);
    void setAddress(const QString &value);

protected:
    QScopedPointer<HEmailAddressPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HEMAILADDRESS_H

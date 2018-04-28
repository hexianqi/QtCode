#ifndef HDATAOBJECT_H
#define HDATAOBJECT_H

#include "HCoreGlobal.h"
#include <QVariantMap>
#include <QSharedDataPointer>

HE_CORE_BEGIN_NAMESPACE

class HDataObjectPrivate;

class HE_CORE_EXPORT HDataObject
{
    Q_DECLARE_PRIVATE(HDataObject)

public:
    HDataObject(QString type = QString());
    HDataObject(const HDataObject &);
    HDataObject &operator=(const HDataObject &);
    virtual ~HDataObject();

public:
    static QString tr(const char *sourceText, const char *comment = 0, int n = -1);

public:
    virtual void initialize(QVariantMap param);
    virtual void setType(QString value);

public:
    QString type(bool bracket = true) const;

protected:
    HDataObject(HDataObjectPrivate &p);

protected:
    QExplicitlySharedDataPointer<HDataObjectPrivate> d_ptr;
};

HE_CORE_END_NAMESPACE

#endif // HDATAOBJECT_H

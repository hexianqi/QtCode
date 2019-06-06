/***************************************************************************************************
**      2018-06-19  HDPointer D指针范例。
***************************************************************************************************/

#ifndef HDPOINTER_H
#define HDPOINTER_H

#include "HReferenceGlobal.h"
#include <QtCore/QObject>
#include <QtCore/QSharedDataPointer>

HE_REFERENCE_BEGIN_NAMESPACE

class HDPointerPrivate;

class HDPointer : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDPointer)
    Q_DISABLE_COPY(HDPointer)

public:
    explicit HDPointer(QObject *parent = nullptr);
    ~HDPointer();

protected:
    void test();

protected:
    HDPointer(HDPointerPrivate &p, QObject *parent = nullptr);
};

HE_REFERENCE_END_NAMESPACE

#endif // HDPOINTER_H

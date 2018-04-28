#ifndef HDPOINTER_P_H
#define HDPOINTER_P_H

#include "HExampleGlobal.h"
#include <private/qobject_p.h>
#include "HDPointer.h"

HE_EXAMPLE_BEGIN_NAMESPACE

class HDPointerPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(HDPointer)

public:
    void init();

public:
    int da;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HDPOINTER_P_H

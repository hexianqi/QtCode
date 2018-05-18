#ifndef HUSBPORTLPC214_P_H
#define HUSBPORTLPC214_P_H

#include "HUsbPortLpc214.h"
#include "HAbstractPort_p.h"

#ifndef Q_CC_MSVC
    class QLibrary;
#endif

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortLpc214Private : public HAbstractPortPrivate
{
public:
    void loadDll();
    void unloadDLL();

public:
    bool isLoaded;
#ifndef Q_CC_MSVC
public:
    using Fn = int(*)(int, uchar *, int, int);
    Fn readData;
    Fn writeData;
    QScopedPointer<QLibrary> lib;
#endif
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTLPC214_P_H

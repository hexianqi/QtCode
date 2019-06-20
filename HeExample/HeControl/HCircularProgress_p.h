#ifndef HCIRCULARPROGRESS_P_H
#define HCIRCULARPROGRESS_P_H

#include "HCircularProgress.h"
#include <QtCore/QMap>

HE_CONTROL_BEGIN_NAMESPACE

class IWaitFactory;

class HCircularProgressPrivate
{
public:
    bool reverse = false;
    int step = 36;
    int value = 0;
    QTimer *timer = nullptr;
    IWait *wait = nullptr;
    IWaitFactory *factory = nullptr;
    QMap<QString, IWait *> waitCache;
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCULARPROGRESS_P_H

#ifndef HMIMEFILE_P_H
#define HMIMEFILE_P_H

#include "HMimeFile.h"
#include "HMimePart_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeFilePrivate : public HMimePartPrivate
{
public:
    HMimeFilePrivate();

public:
    QString fileName;
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMEFILE_P_H

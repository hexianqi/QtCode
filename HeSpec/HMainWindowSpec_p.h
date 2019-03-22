#ifndef HMAINWINDOWSPEC_P_H
#define HMAINWINDOWSPEC_P_H

#include "HMainWindowSpec.h"
#include "HeGui/HAbstractMainWindow_p.h"

class HMainWindowSpecPrivate : public HMainWindowPrivate
{
    Q_DECLARE_PUBLIC(HMainWindowSpec)

public:
    HMainWindowSpecPrivate(HMainWindowSpec *);
};

#endif // HMAINWINDOWSPEC_P_H

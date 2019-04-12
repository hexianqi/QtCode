#ifndef HMAINWINDOW2100_P_H
#define HMAINWINDOW2100_P_H

#include "HMainWindow2000.h"
#include "HeGui/HAbstractMainWindow_p.h"

class HMainWindow2000Private : public HMainWindowPrivate
{
public:
    HMainWindow2000Private(HMainWindow2000 *);

public:
    QAction *actionCalibrateSpectrum;
    QMenu *menuCalibrate;
};

#endif // HMAINWINDOW2100_P_H

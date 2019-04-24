#ifndef HMAINWINDOW2100_P_H
#define HMAINWINDOW2100_P_H

#include "HMainWindow2000.h"
#include "HeGui/HAbstractMainWindow_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HMainWindow2000Private : public HMainWindowPrivate
{
public:
    HMainWindow2000Private(HMainWindow2000 *);

public:
    IConfigManage *configManage;
    QStringList gradeOptionals;

public:
    QAction *actionCalibrateSpectrum;
    QAction *actionGradeEdit;
    QAction *actionGradeSelect;

public:
    QMenu *menuCalibrate;
    QMenu *menuGrade;
};

#endif // HMAINWINDOW2100_P_H

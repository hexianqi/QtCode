#pragma once

#include "HSeekSlider.h"
#include <QtCore/QTime>

class QCommonStyle;
class QPropertyAnimation;
class QSequentialAnimationGroup;

HE_BEGIN_NAMESPACE

class HTimeTooltip;
class HSeekPoints;

class HSeekSliderPrivate
{
public:
    bool classic = false;
    bool sliding = false;               // Whether we are currently sliding by user action
    bool jumping = false;               // if we requested a jump to another chapter
    int inputLength = 0;                // InputLength that can change */
    QTimer *seekLimitTimer = nullptr;   // Timer used to fire intermediate updatePos() when sliding
    HTimeTooltip *timeTooltip = nullptr;
    double buffering;
    QTime bufferingStart;
    bool seekable = true;
    HSeekPoints *chapters = nullptr;
    QCommonStyle *alternativeStyle = nullptr;

    // Handle's
    int handleLength = -1;
    double opacity = 1.0;
    double loading = 0.0;
    QPropertyAnimation *animationOpacity = nullptr;
    QSequentialAnimationGroup *animationLoading = nullptr;
    QTimer *hideHandleTimer = nullptr;
    QTimer *startLoadingTimer = nullptr;
};

HE_END_NAMESPACE


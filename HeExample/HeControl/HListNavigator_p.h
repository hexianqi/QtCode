#ifndef HLISTNAVIGATOR_P_H
#define HLISTNAVIGATOR_P_H

#include "HListNavigator.h"

class QSlider;
class QToolButton;

HE_CONTROL_BEGIN_NAMESPACE

class HListNavigatorPrivate
{
public:
    QSlider *slider;
    QToolButton *first;
    QToolButton *previous;
    QToolButton *next;
    QToolButton *last;
    QListWidget *listWidget = nullptr;


//    Qt::Orientation m_orientation;
//    bool m_autoRaise;
//    Qt::ToolButtonStyle m_toolButtonStyle;

};

HE_CONTROL_END_NAMESPACE

#endif // HLISTNAVIGATOR_P_H

#pragma once

#include "HTaskHeader.h"
#include <QtGui/QIcon>

class QLabel;
class QSpacerItem;

HE_CONTROL_BEGIN_NAMESPACE

class HTaskHeaderPrivate
{
public:
    QIcon icon;
    QLabel *label;
    QSpacerItem *spacer;
    QToolButton *button;
};

HE_CONTROL_END_NAMESPACE

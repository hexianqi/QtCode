#pragma once

#include "HTaskHeader.h"
#include <QtGui/QIcon>

class QLabel;
class QSpacerItem;

HE_BEGIN_NAMESPACE

class HTaskHeaderPrivate
{
public:
    QIcon icon;
    QLabel *label;
    QSpacerItem *spacer;
    QToolButton *button;
};

HE_END_NAMESPACE

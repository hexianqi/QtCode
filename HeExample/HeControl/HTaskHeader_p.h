#ifndef HTASKHEADER_P_H
#define HTASKHEADER_P_H

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

#endif // HTASKHEADER_P_H

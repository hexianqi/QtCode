#pragma once

#include "HTaskWidget.h"

class QTimeLine;
class QVBoxLayout;

HE_CONTROL_BEGIN_NAMESPACE

class HTaskHeader;

class HTaskWidgetPrivate
{
public:
    HTaskHeader *header;
    QWidget *body;
    QWidget *animateWidget;
    QVBoxLayout *layout;
    QTimeLine *timeLine;
    QPixmap pixmap;
};

HE_CONTROL_END_NAMESPACE

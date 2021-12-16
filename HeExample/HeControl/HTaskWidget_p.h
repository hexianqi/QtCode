#pragma once

#include "HTaskWidget.h"

class QTimeLine;
class QVBoxLayout;

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE

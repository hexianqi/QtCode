#ifndef HTASKWIDGET_P_H
#define HTASKWIDGET_P_H

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

#endif // HTASKWIDGET_P_H

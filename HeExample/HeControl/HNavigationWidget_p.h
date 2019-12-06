#ifndef HNAVIGATIONWIDGET_P_H
#define HNAVIGATIONWIDGET_P_H

#include "HNavigationWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationWidgetPrivate
{
public:
    QStringList items;
    QColor background = QColor("#E4E4E4");
    QColor selectedColor = QColor("#2CA7F8");
    int rowHeight = 40;
    int currentIndex = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVIGATIONWIDGET_P_H

#ifndef HABSTRACTTESTWIDGET_P_H
#define HABSTRACTTESTWIDGET_P_H

#include "HAbstractTestWidget.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractTestWidgetPrivate
{
public:
    HAbstractTestWidgetPrivate();

public:
    IModel *model;
    bool testing;
    QVector<QMenu *> menus;
    QVector<QToolBar *> toolBars;
};

HE_GUI_END_NAMESPACE


#endif // HABSTRACTTESTWIDGET_P_H

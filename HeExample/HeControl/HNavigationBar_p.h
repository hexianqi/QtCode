#ifndef HNAVIGATIONBAR_P_H
#define HNAVIGATIONBAR_P_H

#include "HNavigationBar.h"
#include "HAbstractMultiWidget_p.h"

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationBarPrivate : public HAbstractMultiWidgetPrivate
{
public:
    QPushButton *topButton;
    QStackedWidget *stack;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *bottomLayout;
    QList<QPushButton *> buttons;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVIGATIONBAR_P_H

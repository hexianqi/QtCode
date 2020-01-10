#ifndef HNAVIGATIONPANEL_P_H
#define HNAVIGATIONPANEL_P_H

#include "HNavigationPanel.h"
#include "HAbstractMultiPanel_p.h"

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationPanelPrivate : public HAbstractMultiPanelPrivate
{
public:
    QPushButton *topButton;
    QStackedWidget *stack;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *bottomLayout;
    QList<QPushButton *> buttons;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVIGATIONPANEL_P_H

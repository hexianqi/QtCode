#pragma once

#include "HNavigationPanel.h"
#include "HAbstractMultiPanel_p.h"

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;

HE_BEGIN_NAMESPACE

class HNavigationPanelPrivate : public HAbstractMultiPanelPrivate
{
public:
    QPushButton *topButton;
    QStackedWidget *stack;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *bottomLayout;
    QList<QPushButton *> buttons;
};

HE_END_NAMESPACE

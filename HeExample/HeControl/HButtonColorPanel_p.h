#pragma once

#include "HButtonColorPanel.h"
#include "HAbstractColorPanel_p.h"

class QGridLayout;
class QPushButton;

HE_BEGIN_NAMESPACE

class HButtonColorPanelPrivate : public HAbstractColorPanelPrivate
{
public:
    int columnCount = 11;
    int borderRadius = 0;
    int borderWidth = 2;
    QColor borderColor = QColor(192, 57, 43);

public:
    QGridLayout *gridLayout;
    QList<QPushButton *> buttons;
    QStringList colors;
};

HE_END_NAMESPACE

#ifndef HBUTTONCOLORPANEL_P_H
#define HBUTTONCOLORPANEL_P_H

#include "HButtonColorPanel.h"
#include "HAbstractColorPanel_p.h"

class QGridLayout;
class QPushButton;

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HBUTTONCOLORPANEL_P_H

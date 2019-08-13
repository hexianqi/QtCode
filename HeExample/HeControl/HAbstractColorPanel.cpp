#include "HAbstractColorPanel_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractColorPanel::HAbstractColorPanel(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractColorPanelPrivate)
{
}

HAbstractColorPanel::HAbstractColorPanel(HAbstractColorPanelPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HAbstractColorPanel::~HAbstractColorPanel()
{
}

QColor HAbstractColorPanel::currentColor() const
{
    return d_ptr->currentColor;
}

void HAbstractColorPanel::setCurrentColor(const QColor &value)
{
    if (d_ptr->currentColor == value)
        return;
    d_ptr->currentColor = value;
    emit currentColorChanged(value);
}

HE_CONTROL_END_NAMESPACE

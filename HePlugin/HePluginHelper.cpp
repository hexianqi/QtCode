#include "HPluginHelper.h"
#include <QWidget>
#include <QAction>

QAction *HPluginHelper::addSeparator(QWidget *widget)
{
    QAction *action = new QAction(widget);
    action->setSeparator(true);
    widget->addAction(action);
    return action;
}

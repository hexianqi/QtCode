#include "HPluginHelper.h"
#include <QWidget>
#include <QAction>
#include <QtMath>

QAction *HPluginHelper::addSeparator(QWidget *widget)
{
    QAction *action = new QAction(widget);
    action->setSeparator(true);
    widget->addAction(action);
    return action;
}


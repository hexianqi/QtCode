#pragma once

#include <QtCore/QHash>
#include <QtCore/QPoint>

uint qHash(const QPoint &key)
{
    return qHash(QPair<int, int>(key.x(), key.y()));
}

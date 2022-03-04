#pragma once

#include <QtCore/QHash>
#include <QtCore/QPointF>

uint qHash(const QPoint &key);

bool operator<(QPointF p1, QPointF p2);

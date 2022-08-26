#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

class QGraphicsItem;

HE_BEGIN_NAMESPACE

class HGraphicsHelper
{
public:
    // 限制图形项拖动范围
    static QVariant fixByScene(QGraphicsItem *, const QVariant &value);
    // 限制图形项不重叠
    static QVariant fixByOverlap(QGraphicsItem *, const QVariant &value);
};

HE_END_NAMESPACE


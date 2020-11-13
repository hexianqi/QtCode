#pragma once

#include "HGameLevel.h"
#include <QtCore/QVector>

HE_CONTROL_BEGIN_NAMESPACE

class HGameLevelPrivate
{
public:
    QVector<HBrick *> bricks;
};

HE_CONTROL_END_NAMESPACE


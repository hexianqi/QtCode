#pragma once

#include "HGameLevel.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HGameLevelPrivate
{
public:
    QVector<HBrick *> bricks;
};

HE_END_NAMESPACE


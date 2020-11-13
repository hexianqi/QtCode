#pragma once

#include "HGameLevel.h"
#include <QtCore/QVector>

HE_REFERENCE_BEGIN_NAMESPACE

class HGameLevelPrivate
{
public:
    QVector<HBrick *> bricks;
};

HE_REFERENCE_END_NAMESPACE


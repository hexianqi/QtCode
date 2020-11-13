#pragma once

#include "HPropManager.h"
#include <QtCore/QVector>
#include <QtCore/QHash>

HE_CONTROL_BEGIN_NAMESPACE

class HPropManagerPrivate
{
public:
    HPropManagerPrivate();

public:
    QHash<QString, QVector3D> colors;
    QHash<QString, float> durations;
    QHash<QString, QString> textures;
    QVector<HProp *> props;
};

HE_CONTROL_END_NAMESPACE


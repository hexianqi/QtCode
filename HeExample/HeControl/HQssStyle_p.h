#pragma once

#include "HQssStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class HQssStylePrivate
{
public:
    QString current;
    QMap<QString, QPalette> palette;
    QMap<QString, QString> styleSheet;
};

HE_CONTROL_END_NAMESPACE

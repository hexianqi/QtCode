#pragma once

#include "HQssStyle.h"

HE_BEGIN_NAMESPACE

class HQssStylePrivate
{
public:
    QString current;
    QMap<QString, QPalette> palette;
    QMap<QString, QString> styleSheet;
};

HE_END_NAMESPACE

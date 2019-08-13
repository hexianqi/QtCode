#ifndef HQSSSTYLE_P_H
#define HQSSSTYLE_P_H

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

#endif // HQSSSTYLE_P_H

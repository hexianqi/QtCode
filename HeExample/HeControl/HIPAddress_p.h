#pragma once

#include "HIPAddress.h"

class QLineEdit;

HE_BEGIN_NAMESPACE

class HIPAddressPrivate
{
public:
    QString ip;
    QColor background = QColor("#FFFFFF");
    QColor borderColor = QColor("#A6B5B8");
    int borderRadius = 3;
    QList<QLineEdit *> lineEdits;
};

HE_END_NAMESPACE

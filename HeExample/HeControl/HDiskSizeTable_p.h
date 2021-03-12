#pragma once

#include "HDiskSizeTable.h"

class QProcess;

HE_CONTROL_BEGIN_NAMESPACE

class HDiskSizeTablePrivate
{
public:
    QColor background = Qt::white;
    QColor chunkColor1 = QColor(100, 184, 255);
    QColor chunkColor2 = QColor(24, 189, 155);
    QColor chunkColor3 = QColor(255, 107, 107);
    QColor textColor1 = QColor(10, 10, 10);
    QColor textColor2 = QColor(255, 255, 255);
    QColor textColor3 = QColor(255, 255, 255);
#ifndef Q_OS_WIN
    QProcess *process;      // linux执行命令
#endif
};

HE_CONTROL_END_NAMESPACE

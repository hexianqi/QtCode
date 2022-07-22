#pragma once

#include "HKeepLogFile.h"
#include "HAbstractLogFile_p.h"

class QFile;

HE_BEGIN_NAMESPACE

class HKeepLogFilePrivate : public HAbstractLogFilePrivate
{
public:
    QFile *file;
    QString fileName;
    int maxRow = 0;     // 文件最大行数（0 = 不启用）
    int currentRow = 0; // 文件当前行
    int maxSize = 0;    // 文件最大大小（0 = 不启用，单位KB）
};

HE_END_NAMESPACE


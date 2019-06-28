#ifndef HCPUMEMORYLABEL_P_H
#define HCPUMEMORYLABEL_P_H

#include "HCpuMemoryLabel.h"

class QProcess;

HE_CONTROL_BEGIN_NAMESPACE

class HCpuMemoryLabelPrivate
{
public:
    int cpuPercent = 0;
    int memoryPercent = 0;
    int memoryAll = 0;
    int memoryUse = 0;
    int memoryFree = 0;
    QTimer *timerCpu;       // 定时器获取CPU信息
    QTimer *timerMemory;    // 定时器获取内存信息
#ifndef Q_OS_WIN
    QProcess *process;      // linux执行命令
    int totalNew = 0;
    int totalOld = 0;
    int idleNew = 0;
    int idleOld = 0;
#endif
};

HE_CONTROL_END_NAMESPACE

#endif // HCPUMEMORYLABEL_P_H

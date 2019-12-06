#include "HWmicHelper.h"
#include <QtCore/QProcess>

HE_CONTROL_BEGIN_NAMESPACE

// 获取cpu名称：      wmic cpu get Name
// 获取cpu核心数：    wmic cpu get NumberOfCores
// 获取cpu线程数：    wmic cpu get NumberOfLogicalProcessors
// 查询cpu序列号：    wmic cpu get processorid
// 查询主板序列号：   wmic baseboard get serialnumber
// 查询BIOS序列号：   wmic bios get serialnumber
// 查看硬盘：         wmic diskdrive get serialnumber
QString wmicInfo(const QString &cmd)
{
    QProcess p;
    p.start(cmd);
    p.waitForFinished();
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    QStringList list = cmd.split(" ");
    result = result.remove(list.last(), Qt::CaseInsensitive);
    result = result.replace("\r", "");
    result = result.replace("\n", "");
    result = result.simplified();
    return result;
}

QString HWmicHelper::cpuName()
{
    return wmicInfo("wmic cpu get name");
}

QString HWmicHelper::cpuId()
{
    return wmicInfo("wmic cpu get processorid");
}

QString HWmicHelper::diskNum()
{
    return wmicInfo("wmic diskdrive where index=0 get serialnumber");
}

HE_CONTROL_END_NAMESPACE

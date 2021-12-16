#include "HCpuMemoryLabel_p.h"
#include <QtCore/QTimer>

#ifdef Q_OS_WIN
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x502
#endif
#include <windows.h>
#else
#include <QtCore/QProcess>
#endif

#define MB (1024 * 1024)
#define KB (1024)

HE_BEGIN_NAMESPACE

HCpuMemoryLabel::HCpuMemoryLabel(QWidget *parent) :
    QLabel(parent),
    d_ptr(new HCpuMemoryLabelPrivate)
{
    init();
}

HCpuMemoryLabel::HCpuMemoryLabel(HCpuMemoryLabelPrivate &p, QWidget *parent) :
    QLabel(parent),
    d_ptr(&p)
{
    init();
}

HCpuMemoryLabel::~HCpuMemoryLabel()
{
    stop();
}

QSize HCpuMemoryLabel::sizeHint() const
{
    return {300, 30};
}

QSize HCpuMemoryLabel::minimumSizeHint() const
{
    return {30, 20};
}

void HCpuMemoryLabel::start(int interval)
{
    getCpu();
    getMemory();
    d_ptr->timerCpu->start(interval);
    d_ptr->timerMemory->start(interval + 200);
}

void HCpuMemoryLabel::stop()
{
    d_ptr->timerCpu->stop();
    d_ptr->timerMemory->stop();
}

void HCpuMemoryLabel::getCpu()
{
#ifdef Q_OS_WIN
    static FILETIME preidleTime, prekernelTime, preuserTime;
    FILETIME idleTime, kernelTime, userTime;
    quint64 idle, kernel, user;
    quint64 a, b;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b - a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b - a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b - a;

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime;

    d_ptr->cpuPercent = static_cast<int>((kernel + user - idle) * 100 / (kernel + user));
    setData();
#else
    if (d_ptr->process->state() == QProcess::NotRunning)
    {
        d_ptr->totalNew = 0;
        d_ptr->idleNew = 0;
        d_ptr->process->start("cat /proc/stat");
    }
#endif
}

void HCpuMemoryLabel::getMemory()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    d_ptr->memoryPercent = static_cast<int>(statex.dwMemoryLoad);
    d_ptr->memoryAll = static_cast<int>(statex.ullTotalPhys / MB);
    d_ptr->memoryFree = static_cast<int>(statex.ullAvailPhys / MB);
    d_ptr->memoryUse = d_ptr->memoryAll - d_ptr->memoryFree;
    setData();
#else
    if (d_ptr->process->state() == QProcess::NotRunning)
        d_ptr->process->start("cat /proc/meminfo");
#endif
}

#ifndef Q_OS_WIN
void HCpuMemoryLabel::readData()
{
    while (!d_ptr->process->atEnd())
    {
        QString s = QLatin1String(d_ptr->process->readLine());
        if (s.startsWith("cpu"))
        {
            auto list = s.split(" ");
            d_ptr->idleNew = list.at(5).toInt();
            for (auto v : list)
                d_ptr->totalNew += v.toInt();
            auto total = d_ptr->totalNew - d_ptr->totalOld;
            auto idle = d_ptr->idleNew - d_ptr->idleOld;
            d_ptr->cpuPercent = 100 * (total - idle) / total;
            d_ptr->totalOld = d_ptr->totalNew;
            d_ptr->idleOld = d_ptr->idleNew;
            break;
        }
        else if (s.startsWith("MemTotal"))
        {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            d_ptr->memoryAll = s.left(s.length() - 3).toInt() / KB;
        }
        else if (s.startsWith("MemFree"))
        {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            d_ptr->memoryFree = s.left(s.length() - 3).toInt() / KB;
        }
        else if (s.startsWith("Buffers"))
        {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            d_ptr->memoryFree += s.left(s.length() - 3).toInt() / KB;
        }
        else if (s.startsWith("Cached"))
        {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            d_ptr->memoryFree += s.left(s.length() - 3).toInt() / KB;
            d_ptr->memoryUse = d_ptr->memoryAll - d_ptr->memoryFree;
            d_ptr->memoryPercent = 100 * d_ptr->memoryUse / d_ptr->memoryAll;
            break;
        }
    }
    setData();
}
#endif

void HCpuMemoryLabel::setData()
{
    if (d_ptr->cpuPercent < 0)
        d_ptr->cpuPercent = 0;
    auto text = tr("CPU %1%  Mem %2% ( 已用 %3 MB / 共 %4 MB )").arg(d_ptr->cpuPercent).arg(d_ptr->memoryPercent).arg(d_ptr->memoryUse).arg(d_ptr->memoryAll);
    this->setText(text);
    emit textChanged(text);
    emit valueChanged(d_ptr->cpuPercent, d_ptr->memoryPercent, d_ptr->memoryAll, d_ptr->memoryUse, d_ptr->memoryFree);
}

void HCpuMemoryLabel::init()
{
    d_ptr->timerCpu = new QTimer(this);
    d_ptr->timerMemory = new QTimer(this);
    connect(d_ptr->timerCpu, &QTimer::timeout, this, &HCpuMemoryLabel::getCpu);
    connect(d_ptr->timerMemory, &QTimer::timeout, this, &HCpuMemoryLabel::getMemory);
#ifndef Q_OS_WIN
    d_ptr->process = new QProcess(this);
    connect(d_ptr->process, &QProcess::readyRead, this, &HCpuMemoryLabel::readData);
#endif
    setAlignment(Qt::AlignCenter);
}

HE_END_NAMESPACE

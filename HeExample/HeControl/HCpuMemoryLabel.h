/***************************************************************************************************
**      2019-06-28  HCpuMemoryLabel CPU内存显示控件
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1:实时显示当前CPU及内存使用情况
**                  2:全平台通用,包括windows,linux,ARM
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QLabel>

HE_CONTROL_BEGIN_NAMESPACE

class HCpuMemoryLabelPrivate;

class HCpuMemoryLabel : public QLabel
{
    Q_OBJECT

public:
    explicit HCpuMemoryLabel(QWidget *parent = nullptr);
    ~HCpuMemoryLabel() override;

signals:
    void textChanged(QString text);
    void valueChanged(int cpuPercent, int memoryPercent, int memoryAll, int memoryUse, int memoryFree);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public:
    void start(int interval);
    void stop();

protected:
    HCpuMemoryLabel(HCpuMemoryLabelPrivate &p, QWidget *parent = nullptr);

protected:
    void getCpu();      // 获取cpu
    void getMemory();   // 获取内存
#ifndef Q_OS_WIN
    void readData();    // 读取数据
#endif
    void setData();     // 设置数据

protected:
    QScopedPointer<HCpuMemoryLabelPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

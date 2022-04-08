/***************************************************************************************************
**      2019-04-09  IMainWindow 主窗口接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QMainWindow>

HE_BEGIN_NAMESPACE

class IMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    using QMainWindow::QMainWindow;

public:
    // 设置权限
    virtual void setAuthority(int) = 0;
    // 插入菜单
    virtual QAction *insertMenu(QMenu *) = 0;
    // 阻塞测试窗体
    virtual bool blockTestWidget(bool block) = 0;
    // 阻塞并运行
    virtual bool blockAndRun(QDialog *) = 0;
    virtual void blockAndRun(QWidget *) = 0;
    // 阻塞并连接销毁
    virtual void blockAndConnect(QWidget *) = 0;
};

HE_END_NAMESPACE

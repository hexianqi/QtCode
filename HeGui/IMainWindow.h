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
    // 打开对话框
    virtual bool openDialog(QDialog *) = 0;
    // 打开窗体
    virtual void openWidget(QWidget *) = 0;
};

HE_END_NAMESPACE

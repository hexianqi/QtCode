/***************************************************************************************************
**      2019-04-09  IMainWindow 主窗口接口。
***************************************************************************************************/

#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include "HGuiGlobal.h"
#include <QMainWindow>

HE_GUI_BEGIN_NAMESPACE

class IMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    using QMainWindow::QMainWindow;
};

HE_GUI_END_NAMESPACE

#endif // IMAINWINDOW_H

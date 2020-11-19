/***************************************************************************************************
**      2019-03-01  HGuiHelper Gui帮助类。
***************************************************************************************************/

#ifndef HGUIHELPER_H
#define HGUIHELPER_H

#include "HGuiGlobal.h"

class QWidget;
class QDialog;
class QMainWindow;

HE_GUI_BEGIN_NAMESPACE

class ITestWidget;

class HE_GUI_EXPORT HGuiHelper
{
public:
    static QMainWindow *decoratorInMainWindow(ITestWidget *widget, QWidget *parent = nullptr);
    static QDialog *decoratorInDialog(QWidget *widget, QWidget *parent = nullptr);
};

HE_GUI_END_NAMESPACE

#endif // HGUIHELPER_H

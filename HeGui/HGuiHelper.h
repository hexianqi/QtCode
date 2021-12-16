/***************************************************************************************************
**      2019-03-01  HGuiHelper Gui帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QString;
class QWidget;
class QDialog;
class QMainWindow;

HE_BEGIN_NAMESPACE

class ITestWidget;

class HGuiHelper
{
public:
    static QMainWindow *decoratorInMainWindow(ITestWidget *widget, QWidget *parent = nullptr);
    static QDialog *decoratorInDialog(QWidget *widget, QWidget *parent = nullptr);
    static QString encodePassword(QString);
};

HE_END_NAMESPACE

/***************************************************************************************************
**      2022-05-16  HDecoratorMainWindow 装饰窗口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QMainWindow>

HE_BEGIN_NAMESPACE

class ITestWidget;
class IMainWindow;

class HDecoratorMainWindowPrivate;

class HDecoratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HDecoratorMainWindow(IMainWindow *parent);
    ~HDecoratorMainWindow() override;

public:
    void run(ITestWidget *);

protected :
    void closeEvent(QCloseEvent *) override;

protected:
    QScopedPointer<HDecoratorMainWindowPrivate> d_ptr;
};

HE_END_NAMESPACE


#include "HGuiHelper.h"
#include "ITestWidget.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>

HE_GUI_BEGIN_NAMESPACE

QMainWindow *HGuiHelper::decoratorInMainWindow(ITestWidget *widget, QWidget *parent)
{
    auto main = new QMainWindow(parent);
    main->setWindowTitle(widget->windowTitle());
    main->setCentralWidget(widget);
    for (auto menu : widget->menus())
        main->menuBar()->addMenu(menu);
    for (auto toolBar : widget->toolBars())
        main->addToolBar(toolBar);
    widget->start();
    return main;
}

HE_GUI_END_NAMESPACE

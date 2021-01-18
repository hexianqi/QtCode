#include "HGuiHelper.h"
#include "ITestWidget.h"
#include <QtWidgets/QLayout>
#include <QtWidgets/QDialog>
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

QDialog *HGuiHelper::decoratorInDialog(QWidget *widget, QWidget *parent)
{
    auto dlg = new QDialog(parent);
    auto layout = new QGridLayout(dlg);
    layout->addWidget(widget);
    dlg->setWindowTitle(widget->windowTitle());
    dlg->setWindowIcon(widget->windowIcon());
    return dlg;
}

HE_GUI_END_NAMESPACE

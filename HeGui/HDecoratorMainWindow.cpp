#include "HDecoratorMainWindow_p.h"
#include "ITestWidget.h"
#include "IMainWindow.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QMenuBar>

HE_BEGIN_NAMESPACE

HDecoratorMainWindow::HDecoratorMainWindow(IMainWindow *parent) :
    QMainWindow(parent),
    d_ptr(new HDecoratorMainWindowPrivate)
{
    d_ptr->mainWindow = parent;
}

HDecoratorMainWindow::~HDecoratorMainWindow() = default;

void HDecoratorMainWindow::run(ITestWidget *widget)
{
    d_ptr->widget = widget;
    setWindowTitle(widget->windowTitle());
    setWindowIcon(widget->windowIcon());
    setCentralWidget(widget);
    for (auto menu : widget->menus())
        menuBar()->addMenu(menu);
    for (auto toolBar : widget->toolBars())
        addToolBar(toolBar);
    d_ptr->mainWindow->blockAndConnect(d_ptr->widget);
    d_ptr->widget->start();
    show();
    HPluginHelper::centerWidget(this, d_ptr->mainWindow);
}

void HDecoratorMainWindow::closeEvent(QCloseEvent *event)
{
    if (d_ptr->widget)
    {
        d_ptr->widget->stop();
        d_ptr->widget->close();
    }
    QMainWindow::closeEvent(event);
}

HE_END_NAMESPACE

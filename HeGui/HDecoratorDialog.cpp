#include "HDecoratorDialog_p.h"
#include "ITestWidget.h"
#include "IMainWindow.h"
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HDecoratorDialog::HDecoratorDialog(IMainWindow *parent) :
    QDialog(parent),
    d_ptr(new HDecoratorDialogPrivate)
{
    d_ptr->mainWindow = parent;
    d_ptr->layout = new QGridLayout(this);
}

HDecoratorDialog::~HDecoratorDialog() = default;

int HDecoratorDialog::run(ITestWidget *widget)
{
    if (d_ptr->widget != nullptr)
        d_ptr->layout->removeWidget(widget);
    d_ptr->widget = widget;
    setMinimumSize(800, 600);
    setWindowTitle(widget->windowTitle());
    setWindowIcon(widget->windowIcon());
    d_ptr->layout->addWidget(widget);
    d_ptr->mainWindow->blockTestWidget(true);
    d_ptr->widget->start();
    auto result = exec();
    d_ptr->widget->stop();
    d_ptr->mainWindow->blockTestWidget(false);
    return result;
}

HE_END_NAMESPACE

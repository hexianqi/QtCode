#include "HMainWindow_p.h"
#include "HeCore/HAppContext.h"
#include <QStatusBar>
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HMainWindowPrivate::HMainWindowPrivate(HMainWindow *p)
    : q_ptr(p)
{
}

HMainWindow::HMainWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new HMainWindowPrivate(this))
{
    init();
}

HMainWindow::HMainWindow(HMainWindowPrivate &p, QWidget *parent)
    : QMainWindow(parent), d_ptr(&p)
{
    init();
}

HMainWindow::~HMainWindow()
{
    qDebug() << "HMainWindow Destroy";
}

void HMainWindow::init()
{
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    setAttribute(Qt::WA_DeleteOnClose, true);
}

//void HMainWindow::setModel(IModel *model)
//{
//}

HE_GUI_END_NAMESPACE

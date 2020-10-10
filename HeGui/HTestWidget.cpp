#include "HTestWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>

HE_GUI_BEGIN_NAMESPACE

HTestWidgetPrivate::HTestWidgetPrivate()
{
    stream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
}

HTestWidget::HTestWidget(QWidget *parent) :
    HAbstractTestWidget(*new HTestWidgetPrivate, parent)
{
}

HTestWidget::HTestWidget(HTestWidgetPrivate &p, QWidget *parent) :
    HAbstractTestWidget(p, parent)
{
}

void HTestWidget::init()
{
    createAction();
    createWidget();
    createMenu();
    createToolBar();
    initToolBar();
}

void HTestWidget::createAction()
{
    Q_D(HTestWidget);
    d->actionStart = new QAction(tr("测量(&S)"), this);
    d->actionStart->setIcon(QIcon(":/image/Start02.png"));
    d->actionStart->setIconText(tr("测量"));
    d->actionStart->setShortcut(Qt::Key_Space);
    d->actionStop = new QAction(tr("停止(&T)"), this);
    d->actionStop->setIcon(QIcon(":/image/Stop02.png"));
    d->actionStop->setIconText(tr("停止"));
    d->actionStop->setShortcut(Qt::Key_F4);
    d->actionStop->setEnabled(false);
    d->actionClear = new QAction(tr("清除结果(&R)..."), this);
    d->actionClear->setIcon(QIcon(":/image/Clear.png"));
    d->actionClear->setIconText(tr("清除结果"));
    d->actionExportExcel = new QAction(tr("导出结果(&E)"), this);
    d->actionExportExcel->setIcon(QIcon(":/image/Excel.png"));
    d->actionExportExcel->setIconText(tr("导出结果"));
    d->actionExportExcel->setEnabled(false);
    connect(d->actionStart, &QAction::triggered, this, [=] { setTest(true); });
    connect(d->actionStop, &QAction::triggered, this, [=] { setTest(false); });
    connect(d->actionClear, &QAction::triggered, this, &HTestWidget::clearResult);
    connect(d->actionExportExcel, &QAction::triggered, this, &HTestWidget::exportExcel);
}

void HTestWidget::initToolBar()
{
    for (auto bar : toolBars())
        bar->setMovable(false);
}

HE_GUI_END_NAMESPACE

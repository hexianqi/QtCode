#include "HStationWidget_p.h"
#include "HTestWidget3000.h"
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>

HStationWidget::HStationWidget(int index, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HStationWidgetPrivate)
{
    initialize(index);
}

HStationWidget::~HStationWidget()
{
}

void HStationWidget::initialize(int index)
{
    d_ptr->index = index;
//  readSettings();
    createAction();
    createToolBar();
    createWidget();
    initWidget();
    setWindowIcon(QIcon(QString(":/image/%1-0.png").arg(index + 1)));
}

void HStationWidget::createAction()
{
    d_ptr->actionStart = new QAction(tr("测量(&S)"), this);
    d_ptr->actionStart->setIcon(QIcon(":/image/Start02.png"));
    d_ptr->actionStart->setIconText(tr("测量"));
    d_ptr->actionStart->setShortcut(Qt::Key_Space);
    d_ptr->actionStop = new QAction(tr("停止(&T)"), this);
    d_ptr->actionStop->setIcon(QIcon(":/image/Stop02.png"));
    d_ptr->actionStop->setIconText(tr("停止"));
    d_ptr->actionStop->setShortcut(Qt::Key_F4);
    d_ptr->actionStop->setEnabled(false);
    d_ptr->actionSetp = new QAction(tr("单次测试(&P)"), this);
    d_ptr->actionClear = new QAction(tr("清除结果(&R)"), this);
    d_ptr->actionClear->setIcon(QIcon(":/image/Clear.png"));
    d_ptr->actionClear->setIconText(tr("清除结果"));
    d_ptr->actionCie = new QAction(tr("显示色品图"), this);
    d_ptr->actionEnergy = new QAction(tr("显示能量图"), this);
    d_ptr->actionTest = new QAction(tr("测试结果"), this);
    d_ptr->actionTestSet = new QAction(tr("测试设置"), this);

//    connect(d_ptr->actionStart, &QAction::triggered, this, [=] { setTest(true); });
//    connect(d_ptr->actionStop, &QAction::triggered, this, [=] { setTest(false); });
    //    connect(d_ptr->actionClear, &QAction::triggered, this, &HTestWidget::clearResult);
}

void HStationWidget::createToolBar()
{
    d_ptr->toolBar = new QToolBar;
    d_ptr->toolBar->addAction(d_ptr->actionStart);
    d_ptr->toolBar->addAction(d_ptr->actionStop);
    d_ptr->toolBar->addAction(d_ptr->actionSetp);
    d_ptr->toolBar->addAction(d_ptr->actionClear);
    d_ptr->toolBar->addSeparator();
    d_ptr->toolBar->addAction(d_ptr->actionCie);
    d_ptr->toolBar->addAction(d_ptr->actionEnergy);
    d_ptr->toolBar->addSeparator();
    d_ptr->toolBar->addAction(d_ptr->actionTest);
    d_ptr->toolBar->addAction(d_ptr->actionTestSet);
    d_ptr->toolBar->setIconSize(QSize(32, 32));
    d_ptr->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void HStationWidget::createWidget()
{
    d_ptr->stackedWidget = new QStackedWidget;
    d_ptr->testWidget = new HTestWidget3000;
    d_ptr->stackedWidget->addWidget(d_ptr->testWidget);
}

void HStationWidget::initWidget()
{
    auto layout = new QGridLayout(this);
    layout->setSpacing(9);
    layout->addWidget(d_ptr->toolBar, 0, 0);
    layout->addWidget(d_ptr->stackedWidget, 1, 0);
}



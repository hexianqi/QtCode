#include "HControlDemoWidget_p.h"
#include "HIconFontFactory.h"
#include "HFlatStyle.h"
#include "HNavigationWidget.h"
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

HControlDemoWidget::HControlDemoWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HControlDemoWidgetPrivate)
{
    init();
}

HControlDemoWidget::HControlDemoWidget(HControlDemoWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HControlDemoWidget::~HControlDemoWidget()
{
}

void HControlDemoWidget::init()
{
    d_ptr->iconFactory = new HIconFontFactory(this);
    d_ptr->style = new HFlatStyle(this);
    initWidget();
    addLiuDianWu();
    addStyle();
    addTool();
    addElse();
}

void HControlDemoWidget::initWidget()
{
    auto layout = new QGridLayout(this);
    auto splitter = new QSplitter;
    auto nav = new HNavigationWidget;
    auto stacked = new QStackedWidget;
    auto keys = QStringList() << tr("ludianwu") << tr("ww") << tr("DEMO") << tr("工具") << tr("其他");

    for (auto key : keys)
    {
        auto w = new QTabWidget;
        stacked->addWidget(w);
        nav->addItem(key);
        d_ptr->tabWidgets.insert(key, w);
    }

    splitter->addWidget(nav);
    splitter->addWidget(stacked);
    layout->addWidget(splitter);
    connect(nav, &HNavigationWidget::currentItemChanged, stacked, &QStackedWidget::setCurrentIndex);
    resize(1000, 800);
}

void HControlDemoWidget::addTab(QString key, QWidget *w)
{
    addTab(key, w->windowTitle(), w);
}

void HControlDemoWidget::addTab(QString key, QString title, QWidget *w)
{
    if (d_ptr->tabWidgets.contains(key))
        d_ptr->tabWidgets[key]->addTab(w, title);
}

void HControlDemoWidget::addTab(QString key, QString title, QLayout *layout)
{
    auto w = new QWidget;
    w->setLayout(layout);
    addTab(key, title, w);
}

HE_CONTROL_END_NAMESPACE

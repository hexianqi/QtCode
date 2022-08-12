#include "HControlDemoWidget_p.h"
#include "HIconFontFactory.h"
#include "HFlatStyle.h"
#include "HNavigationWidget.h"
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

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

HControlDemoWidget::~HControlDemoWidget() = default;

void HControlDemoWidget::init()
{
    d_ptr->iconFactory = new HIconFontFactory(this);
    d_ptr->style = new HFlatStyle(this);
    initWidget();
    addFYQY();
    addLiuDianWu();
    addWw();
    addDemo();
    addLayout();
    addStyle();
    addUI();
    addTool();
    addMedia();
    addElse();
}

void HControlDemoWidget::initWidget()
{
    d_ptr->navigationWidget = new HNavigationWidget;
    d_ptr->stackedWidget = new QStackedWidget;
    auto layout = new QGridLayout(this);
    auto splitter = new QSplitter;
    splitter->addWidget(d_ptr->navigationWidget);
    splitter->addWidget(d_ptr->stackedWidget);
    layout->addWidget(splitter);
    connect(d_ptr->navigationWidget, &HNavigationWidget::currentItemChanged, d_ptr->stackedWidget, &QStackedWidget::setCurrentIndex);
    resize(1000, 800);
}

void HControlDemoWidget::addTab(const QString &key, QWidget *widget)
{
    addTab(key, widget->windowTitle(), widget);
}

void HControlDemoWidget::addTab(const QString &key, const QString &title, QWidget *widget)
{
    if (!d_ptr->tabWidgets.contains(key))
    {
        auto tab = new QTabWidget;
        d_ptr->navigationWidget->addItem(key);
        d_ptr->stackedWidget->addWidget(tab);
        d_ptr->tabWidgets.insert(key, tab);
    }
    d_ptr->tabWidgets[key]->addTab(widget, title);
}

void HControlDemoWidget::addTab(const QString &key, const QString &title, QLayout *layout)
{
    auto widget = new QWidget;
    widget->setLayout(layout);
    addTab(key, title, widget);
}

HE_END_NAMESPACE

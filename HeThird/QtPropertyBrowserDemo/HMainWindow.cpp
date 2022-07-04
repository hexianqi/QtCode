#include "HMainWindow.h"
#include "HDemoWidget.h"
#include "HPropertyBrowser.h"
#include "HVariantWidget.h"
#include "HeControl/HNavigationWidget.h"
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QSplitter>

HE_USE_NAMESPACE

HMainWindow::HMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto navigation = new HNavigationWidget;
    auto stacked = new QStackedWidget;
    auto splitter = new QSplitter;
    auto browser = new HPropertyBrowser;
    browser->setObject(this);
    navigation->addItem("Demo");
    navigation->addItem("Variant");
    navigation->addItem("Browser");
    stacked->addWidget(new HDemoWidget);
    stacked->addWidget(new HVariantWidget);
    stacked->addWidget(browser);
    splitter->addWidget(navigation);
    splitter->addWidget(stacked);
    setCentralWidget(splitter);
    connect(navigation, SIGNAL(currentItemChanged(int)), stacked, SLOT(setCurrentIndex(int)));
    resize(1400, 800);
}

HMainWindow::~HMainWindow()
{

}

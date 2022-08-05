#include "HNetworkWidget_p.h"
#include "HTcpClientWidget.h"
#include "HTcpServerWidget.h"
#include "HUdpClientWidget.h"
#include "HUdpServerWidget.h"
#include "HWebClientWidget.h"
#include "HWebServerWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>

HE_BEGIN_NAMESPACE

HNetworkWidget::HNetworkWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HNetworkWidgetPrivate)
{
    init();
}

HNetworkWidget::HNetworkWidget(HNetworkWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HNetworkWidget::~HNetworkWidget() = default;

void HNetworkWidget::init()
{
    auto gridLayout = new QGridLayout(this);
    auto tabWidget = new QTabWidget;
    auto tcpClient = new HTcpClientWidget;
    auto tcpServer = new HTcpServerWidget;
    auto udpClient = new HUdpClientWidget;
    auto udpServer = new HUdpServerWidget;
    auto webClient = new HWebClientWidget;
    auto webServer = new HWebServerWidget;
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->addTab(tcpClient, tcpClient->windowTitle());
    tabWidget->addTab(tcpServer, tcpServer->windowTitle());
    tabWidget->addTab(udpClient, udpClient->windowTitle());
    tabWidget->addTab(udpServer, udpServer->windowTitle());
    tabWidget->addTab(webClient, webClient->windowTitle());
    tabWidget->addTab(webServer, webServer->windowTitle());
    gridLayout->addWidget(tabWidget, 0, 0, 1, 1);
    setWindowTitle(tr("网络调试工具"));
}

HE_END_NAMESPACE

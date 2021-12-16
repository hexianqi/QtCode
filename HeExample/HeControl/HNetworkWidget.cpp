#include "HNetworkWidget_p.h"
#include "HTcpClientWidget.h"
#include "HTcpServerWidget.h"
#include "HUdpClientWidget.h"
#include "HUdpServerWidget.h"
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
    d_ptr->tabWidget = new QTabWidget;
    d_ptr->tcpClient = new HTcpClientWidget;
    d_ptr->tcpServer = new HTcpServerWidget;
    d_ptr->udpClient = new HUdpClientWidget;
    d_ptr->udpServer = new HUdpServerWidget;
    d_ptr->tabWidget->addTab(d_ptr->tcpClient, d_ptr->tcpClient->windowTitle());
    d_ptr->tabWidget->addTab(d_ptr->tcpServer, d_ptr->tcpServer->windowTitle());
    d_ptr->tabWidget->addTab(d_ptr->udpClient, d_ptr->udpClient->windowTitle());
    d_ptr->tabWidget->addTab(d_ptr->udpServer, d_ptr->udpServer->windowTitle());
    gridLayout->addWidget(d_ptr->tabWidget, 0, 0, 1, 1);
    setWindowTitle(tr("网络调试工具"));
}

HE_END_NAMESPACE

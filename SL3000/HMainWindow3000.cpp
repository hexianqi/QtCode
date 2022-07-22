#include "HMainWindow3000_p.h"
#include "ui_HMainWindow3000.h"
#include "HHelper.h"
#include "HStationWidget.h"
#include "HStatusWidget.h"
#include "HeCore/HAppContext.h"
#include "HeSql/HSqlHelper.h"
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>

HE_USE_NAMESPACE

HMainWindow3000Private::HMainWindow3000Private()
{
    logo.load(":/image/Logo.png");
}

HMainWindow3000::HMainWindow3000(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new HMainWindow3000Private),
    ui(new Ui::HMainWindow3000)
{
    ui->setupUi(this);
    initialize();
}

HMainWindow3000::~HMainWindow3000()
{
    d_ptr->timer->stop();
    writeSettings();
    delete ui;
}

void HMainWindow3000::initialize()
{
    readSettings();
//    createAction();
//    createMenu();
//    createToolBar();
    createToolBarLogo();
//    initMenu();
    initToolBar();
    initStatusBar();
//    initBuilder();
//    initModel();
    initCentralWidget();
    initWindow();
    initTimer();
    HSqlHelper::truncateTable("testdata", HHelper::mysql);
}

void HMainWindow3000::createToolBarLogo()
{
    d_ptr->toolBarLogo = new QToolBar(tr("商标(&L)"));
    d_ptr->toolBarLogo->setMovable(false);
    if (d_ptr->showLogo)
    {
        auto label = new QLabel;
        label->setPixmap(d_ptr->logo);
        label->setScaledContents(true);
        label->setMaximumSize(355, 80);
        d_ptr->toolBarLogo->addWidget(label);
    }
    else
        d_ptr->toolBarLogo->setVisible(false);
}

void HMainWindow3000::initToolBar()
{
    addToolBar(d_ptr->toolBarLogo);
    setIconSize(QSize(40, 40));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void HMainWindow3000::initWindow()
{
    setWindowIcon(QIcon(":/image/Icon.ico"));
}

void HMainWindow3000::initTimer()
{
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, &HMainWindow3000::updateTime);
    d_ptr->timer->start(1000);
}

void HMainWindow3000::initStatusBar()
{
    QVector<int> indexs;
    for (int i = 0; i < d_ptr->stationEnable.size(); i++)
    {
        if (d_ptr->stationEnable.at(i))
            indexs << i;
    }

    d_ptr->time = new QLabel(QDateTime::currentDateTime().toString(" yyyy-MM-dd hh:mm:ss "));
    d_ptr->workStatusWidget = new HStatusWidget(tr("工位运行状态："), indexs);
    d_ptr->specStatusWidget = new HStatusWidget(tr("光谱连接状态："), indexs);
    d_ptr->elecStatusWidget = new HStatusWidget(tr("电源连接状态："), indexs);
    statusBar()->addPermanentWidget(d_ptr->time);
    statusBar()->addWidget(new QLabel(tr(" 当前登录用户：%1 ").arg(HAppContext::getContextValue<QString>("User"))));
    statusBar()->addWidget(d_ptr->workStatusWidget);
    statusBar()->addWidget(d_ptr->specStatusWidget);
    statusBar()->addWidget(d_ptr->elecStatusWidget);

 //   statusBar()->setStyleSheet("QStatusBar::item { border:2px solid red; }");
}

void HMainWindow3000::initCentralWidget()
{
    for (int i = 0; i < d_ptr->stationEnable.size(); i++)
    {
        if (!d_ptr->stationEnable.at(i))
            continue;
        auto widget = new HStationWidget(i);
        ui->tabWidget->addTab(widget, widget->windowIcon(), "");
        d_ptr->stationWidget.insert(i, widget);
        connect(widget, &HStationWidget::workStateChanged, d_ptr->workStatusWidget, &HStatusWidget::setStatus);
        connect(widget, &HStationWidget::specStateChanged, d_ptr->specStatusWidget, &HStatusWidget::setStatus);
        connect(widget, &HStationWidget::elecStateChanged, d_ptr->elecStatusWidget, &HStatusWidget::setStatus);
    }

    //    for (int i = 0; i < d_ptr->stationEnable.size(); i++)
    //    {
    //        auto widget = new HStationWidget(i);
    //        ui->tabWidget->addTab(widget, widget->windowIcon(), "");
    //        ui->tabWidget->setTabEnabled(i ,d_ptr->stationEnable.at(i));
    //    }
    //    ui->tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
}

void HMainWindow3000::readSettings()
{
    d_ptr->stationEnable.clear();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("MainWindow");
    d_ptr->showLogo = settings->value("Logo", true).toBool();
    d_ptr->stationEnable.resize(settings->value("StationCount", 4).toInt());
    for (int i = 0; i < d_ptr->stationEnable.size(); i++)
        d_ptr->stationEnable[i] = settings->value(QString("Station%1").arg(i+1), true).toBool();
    settings->endGroup();
}

void HMainWindow3000::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("MainWindow");
    settings->setValue("Logo", d_ptr->showLogo);
    settings->setValue("StationCount", d_ptr->stationEnable.size());
    for (int i = 0; i < d_ptr->stationEnable.size(); i++)
        settings->setValue(QString("Station%1").arg(i+1), d_ptr->stationEnable.at(i));
    settings->endGroup();
}

void HMainWindow3000::updateTime()
{
    d_ptr->time->setText(QDateTime::currentDateTime().toString(" yyyy-MM-dd hh:mm:ss "));
}

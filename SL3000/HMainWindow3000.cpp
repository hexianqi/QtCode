#include "HMainWindow3000_p.h"
#include "ui_HMainWindow3000.h"
#include "HStationWidget.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
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

void HMainWindow3000::initStatusBar()
{
//    statusBar()->addWidget(new QLabel(tr("当前登录用户：%1").arg()))
//    for (auto w : d_ptr->labels)
//        statusBar()->removeWidget(w);
//    d_ptr->labels.clear();
//    for (const auto &s : list)
//    {
//        auto l = new QLabel;
//        l->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(s));
//        d_ptr->labels.insert(s, l);
//        statusBar()->addWidget(l);
//    }



    statusBar()->setStyleSheet("QStatusBar::item { border: 0px }");
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

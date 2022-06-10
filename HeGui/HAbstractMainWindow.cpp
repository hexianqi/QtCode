#include "HAbstractMainWindow_p.h"
#include "ITestWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeController/IModel.h"
#include "HeController/IMementoCollection.h"
#include <QtCore/QSettings>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>

HE_BEGIN_NAMESPACE

HAbstractMainWindowPrivate::HAbstractMainWindowPrivate(HAbstractMainWindow *p) :
    q_ptr(p)
{
    HAppContext::setContextValue("Settings", QString("Ini\\%1.ini").arg(QApplication::applicationName()));
    HAppContext::setContextValue("ConfigFileName", QString("%1.cfg").arg(QApplication::applicationName()));
    HAppContext::setContextPointer("IMainWindow", p);
    logo.load(":/image/Logo.png");
}

HAbstractMainWindow::HAbstractMainWindow(QWidget *parent) :
    IMainWindow(parent),
    d_ptr(new HAbstractMainWindowPrivate(this))
{
    initialize();
}

HAbstractMainWindow::HAbstractMainWindow(HAbstractMainWindowPrivate &p, const HConstructionCallHelper &helper, QWidget *parent) :
    IMainWindow(parent),
    d_ptr(&p)
{
    helper.initialize(this);
}

HAbstractMainWindow::~HAbstractMainWindow()
{
    writeSettings();
    d_ptr->testWidget->close();
    d_ptr->model->saveFile();
    if (d_ptr->mementos)
        d_ptr->mementos->writeFile();
}

void HAbstractMainWindow::setAuthority(int value)
{
    updateAuthority(menuBar()->actions(), value);
}

void HAbstractMainWindow::updateAuthority(QList<QAction *> actions, int value)
{
    for (auto action : actions)
    {
        action->setVisible(value >= action->property("authority").toInt());
        auto menu = action->menu();
        if (menu != nullptr)
            updateAuthority(menu->actions(), value);
    }
}

QAction *HAbstractMainWindow::insertMenu(QMenu *menu)
{
    return menuBar()->insertMenu(d_ptr->actionSeparator, menu);
}

bool HAbstractMainWindow::blockTestWidget(bool block)
{
    if (d_ptr->testWidget == nullptr)
        return false;
    if (block)
        return d_ptr->testWidget->stop();
    return d_ptr->testWidget->start();
}

QVariant HAbstractMainWindow::blockAndRun(std::function<QVariant (QVariantMap)> func, QVariantMap param)
{
    d_ptr->testWidget->stop();
    auto result = func(param);
    d_ptr->testWidget->start();
    return result;
}

QString HAbstractMainWindow::summary()
{
    return QString();
}

void HAbstractMainWindow::initialize()
{
    readSettings();
    initImportExport();
    createAction();
    createMenu();
    createToolBar();
    createToolBarLogo();
    initMenu();
    initToolBar();
    initStatusBar();
    initBuilder();
    initModel();
    initCentralWidget();
    initWindow();
    d_ptr->mementos = HAppContext::getContextPointer<IMementoCollection>("IMementoCollection");
}

void HAbstractMainWindow::initImportExport()
{
    d_ptr->importExport.clear();
}

void HAbstractMainWindow::createAction()
{
    d_ptr->actionOpen = new QAction(tr("打开(&O)..."), this);
    d_ptr->actionOpen->setIcon(QIcon(":/image/Open.png"));
    d_ptr->actionOpen->setIconText(tr("\n打开"));
    d_ptr->actionOpen->setShortcut(QKeySequence::Open);
    d_ptr->actionSave = new QAction(tr("保存(&S)"), this);
    d_ptr->actionSave->setIcon(QIcon(":/image/Save.png"));
    d_ptr->actionSave->setIconText(tr("\n保存"));
    d_ptr->actionSave->setShortcut(QKeySequence::Save);
    d_ptr->actionSaveAs = new QAction(tr("另存为(&A)..."), this);
    d_ptr->actionSaveAs->setIcon(QIcon(":/image/SaveAs.png"));
    d_ptr->actionSaveAs->setIconText(tr("\n另存为"));
    d_ptr->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    d_ptr->actionExit = new QAction(tr("退出(&X)"), this);
    d_ptr->actionExit->setIcon(QIcon(":/image/Exit.png"));
    d_ptr->actionExit->setIconText(tr("\n退出"));
    d_ptr->actionExit->setShortcut(tr("Ctrl+Q"));
    d_ptr->actionAbout = new QAction(tr("关于(&A)..."), this);
    d_ptr->actionGroupImport = new QActionGroup(this);
    d_ptr->actionGroupExport = new QActionGroup(this);
    for (auto i = d_ptr->importExport.begin(); i != d_ptr->importExport.end(); i++)
    {
        d_ptr->actionGroupImport->addAction(i.key())->setData(i.value());
        d_ptr->actionGroupExport->addAction(i.key())->setData(i.value());
    }
    connect(d_ptr->actionOpen, &QAction::triggered, this, &HAbstractMainWindow::openFile);
    connect(d_ptr->actionSave, &QAction::triggered, this, &HAbstractMainWindow::saveFile);
    connect(d_ptr->actionSaveAs, &QAction::triggered, this, &HAbstractMainWindow::saveAsFile);
    connect(d_ptr->actionExit, &QAction::triggered, this, &HAbstractMainWindow::close);
    connect(d_ptr->actionAbout, &QAction::triggered, this, &HAbstractMainWindow::about);
    connect(d_ptr->actionGroupImport, &QActionGroup::triggered, this, &HAbstractMainWindow::importFile);
    connect(d_ptr->actionGroupExport, &QActionGroup::triggered, this, &HAbstractMainWindow::exportFile);
}

void HAbstractMainWindow::createMenu()
{
    d_ptr->menuFile = new QMenu(tr("文件(&F)"));
    d_ptr->menuFile->addAction(d_ptr->actionOpen);
    d_ptr->menuFile->addAction(d_ptr->actionSave);
    d_ptr->menuFile->addAction(d_ptr->actionSaveAs);
    if (!d_ptr->importExport.isEmpty())
    {
        d_ptr->menuFile->addSeparator();
        d_ptr->menuImport = d_ptr->menuFile->addMenu(tr("导入(&I)"));
        d_ptr->menuImport->addActions(d_ptr->actionGroupImport->actions());
        d_ptr->menuImport->menuAction()->setProperty("authority", 1);
        d_ptr->menuExport = d_ptr->menuFile->addMenu(tr("导出(&E)"));
        d_ptr->menuExport->addActions(d_ptr->actionGroupExport->actions());
        d_ptr->menuExport->menuAction()->setProperty("authority", 1);
    }
    d_ptr->menuFile->addSeparator();
    d_ptr->menuFile->addAction(d_ptr->actionExit);
    d_ptr->menuHelp = new QMenu(tr("帮助(&H)"));
    d_ptr->menuHelp->addAction(d_ptr->actionAbout);
}

void HAbstractMainWindow::createToolBar()
{
}

void HAbstractMainWindow::createToolBarLogo()
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

void HAbstractMainWindow::initMenu()
{
    menuBar()->addMenu(d_ptr->menuFile);
    d_ptr->actionSeparator = menuBar()->addSeparator();
    menuBar()->addMenu(d_ptr->menuHelp);
}

void HAbstractMainWindow::initToolBar()
{
    addToolBar(d_ptr->toolBarLogo);
    setIconSize(QSize(40, 40));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void HAbstractMainWindow::initStatusBar()
{
    statusBar()->setStyleSheet("QStatusBar::item { border: 0px }");
}

void HAbstractMainWindow::initModel()
{
    d_ptr->model = HAppContext::getContextPointer<IModel>("IModel");
    connect(d_ptr->model, &IModel::threadInitFinished, this, &HAbstractMainWindow::updateStatusBar);
    connect(d_ptr->model, &IModel::threadStartFailed, this, &HAbstractMainWindow::showDeviceFailed);
    connect(d_ptr->model, &IModel::threadStateChanged, this, &HAbstractMainWindow::updateLabel);
    connect(d_ptr->model, &IModel::actionFailed, this, &HAbstractMainWindow::showActionFailed);
    d_ptr->model->start();
}

void HAbstractMainWindow::initCentralWidget()
{
    d_ptr->testWidget = HAppContext::getContextPointer<ITestWidget>("ITestWidget");
    setCentralWidget(d_ptr->testWidget);
    for (auto menu : d_ptr->testWidget->menus())
        insertMenu(menu);
    for (auto toolBar : d_ptr->testWidget->toolBars())
        insertToolBar(d_ptr->toolBarLogo, toolBar);
    d_ptr->testWidget->start();
}

void HAbstractMainWindow::initWindow()
{
    updatetWindowTitle();
    setWindowIcon(QIcon(":/image/Icon.ico"));
}

void HAbstractMainWindow::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("MainWindow");
    d_ptr->showLogo = settings->value("Logo", true).toBool();
    settings->endGroup();
}

void HAbstractMainWindow::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("MainWindow");
    settings->setValue("Logo", d_ptr->showLogo);
    settings->endGroup();
}

void HAbstractMainWindow::showDeviceFailed(const QString &port, const QString &text)
{
    auto msg = tr("\n“%1”设备连接失败！错误原因“%2”。\n").arg(port, text);
    QMessageBox::critical(this, "", msg);
#ifndef QT_DEBUG
    close();
#endif
}

void HAbstractMainWindow::showActionFailed(HActionType action, const QString &text)
{
    Q_UNUSED(action);
    auto msg = tr("\n指令“%1”错误！错误原因是“%2”\n").arg(HCore::toComment(action), text);
    QMessageBox::warning(this, "", msg);
}

void HAbstractMainWindow::updateStatusBar(QStringList list)
{
    for (auto w : d_ptr->labels)
        statusBar()->removeWidget(w);
    d_ptr->labels.clear();
    for (const auto &s : list)
    {
        auto l = new QLabel;
        l->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(s));
        d_ptr->labels.insert(s, l);
        statusBar()->addWidget(l);
    }
}

void HAbstractMainWindow::updateLabel(const QString &name, int state)
{
    if (!d_ptr->labels.contains(name))
        return;
    QString text = state == 1 ? tr("%1:<font color=#00FF00>开启</font>").arg(name) : tr("%1:<font color=#FF0000>关闭</font>").arg(name);
    d_ptr->labels.value(name)->setText(text);
}

void HAbstractMainWindow::updatetWindowTitle()
{
    auto fileName = HAppContext::getContextValue<QString>("ConfigFileName");
    setWindowTitle(QApplication::applicationName() + " - " + fileName);
}

void HAbstractMainWindow::openFile()
{
    if (!d_ptr->model->openFile())
        return;
    QMessageBox::information(this, "", tr("\n打开文件成功！\n"));
    updatetWindowTitle();
}

void HAbstractMainWindow::saveFile()
{
    if (!d_ptr->model->saveFile())
        return;
    QMessageBox::information(this, "", tr("\n保存文件成功！\n"));
}

void HAbstractMainWindow::saveAsFile()
{
    if (!d_ptr->model->saveAsFile())
        return;
    QMessageBox::information(this, "", tr("\n保存文件成功！\n"));
    updatetWindowTitle();
}

void HAbstractMainWindow::importFile(QAction *p)
{
    if (p == nullptr || !d_ptr->model->importFile(p->data().toUInt()))
        return;
    QMessageBox::information(this, "", tr("\n导入成功！\n"));
}

void HAbstractMainWindow::exportFile(QAction *p)
{
    if (p == nullptr || !d_ptr->model->exportFile(p->data().toUInt()))
        return;
    QMessageBox::information(this, "", tr("\n导出成功！\n"));
}

void HAbstractMainWindow::about()
{
    QString abbreviation,text;

    abbreviation = QApplication::applicationName().split(" ").first();
    text = tr("<h2>%1</h2><p>").arg(abbreviation)
            + tr("<p>版本 %1<p>").arg(QApplication::applicationVersion())
            + tr("<p>%1<p>").arg(QApplication::applicationName())
            + tr("<p>版权所有：2017-2019 %1 保留所有权利。<p>").arg(QApplication::organizationName())
            + tr("<p>%1<p>").arg(summary());
    QMessageBox::about(this, tr("关于 %1").arg(abbreviation), text);
}

HE_END_NAMESPACE

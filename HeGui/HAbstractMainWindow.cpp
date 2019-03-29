#include "HAbstractMainWindow_p.h"
#include "ITestWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HMainWindowPrivate::HMainWindowPrivate(HAbstractMainWindow *p)
    : q_ptr(p)
{
    logo.load(":/image/Logo.png");
}

HAbstractMainWindow::HAbstractMainWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new HMainWindowPrivate(this))
{
    initialize();
}

HAbstractMainWindow::HAbstractMainWindow(HMainWindowPrivate &p, const HCallorHelper &helper, QWidget *parent)
    : QMainWindow(parent), d_ptr(&p)
{
    helper.initialize(this);
}

HAbstractMainWindow::~HAbstractMainWindow()
{
    qDebug() << __func__;
}

void HAbstractMainWindow::initialize()
{
    initImportExport();
    createBuilder();
    createAction();
    createActionGroup();
    createMenu();
    createToolBar();
    createToolBarLogo();
    createConnect();
    initMenu();
    initToolBar();
    initStatusBar();
    initModel();
    initCentralWidget();
    updatetWindowTitle();
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
}

void HAbstractMainWindow::createActionGroup()
{
    d_ptr->actionGroupImport = new QActionGroup(this);
    d_ptr->actionGroupExport = new QActionGroup(this);
    auto it = d_ptr->importExport.constBegin();
    while (it != d_ptr->importExport.constEnd())
    {
        d_ptr->actionGroupImport->addAction(it.key())->setData(it.value());
        d_ptr->actionGroupExport->addAction(it.key())->setData(it.value());
        it++;
    }
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
        d_ptr->menuExport = d_ptr->menuFile->addMenu(tr("导出(&E)"));
        d_ptr->menuImport->addActions(d_ptr->actionGroupImport->actions());
        d_ptr->menuExport->addActions(d_ptr->actionGroupImport->actions());
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
#ifdef HAVE_LOGO
    auto label = new QLabel;
    label->setPixmap(d_ptr->logo);
    label->setScaledContents(true);
    label->setMaximumSize(400, 80);
    d_ptr->toolBarLogo->addWidget(label);
#else
    d_ptr->toolBarLogo->setVisible(false);
#endif
}

void HAbstractMainWindow::createConnect()
{
    connect(d_ptr->actionOpen, &QAction::triggered, this, &HAbstractMainWindow::open);
    connect(d_ptr->actionSave, &QAction::triggered, this, &HAbstractMainWindow::save);
    connect(d_ptr->actionSaveAs, &QAction::triggered, this, &HAbstractMainWindow::saveAs);
    connect(d_ptr->actionExit, &QAction::triggered, this, &HAbstractMainWindow::close);
    connect(d_ptr->actionAbout, &QAction::triggered, this, &HAbstractMainWindow::about);
    connect(d_ptr->actionGroupImport, &QActionGroup::triggered, this, &HAbstractMainWindow::importFile);
    connect(d_ptr->actionGroupExport, &QActionGroup::triggered, this, &HAbstractMainWindow::exportFile);
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
    setIconSize(QSize(40,40));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void HAbstractMainWindow::initStatusBar()
{
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

void HAbstractMainWindow::initModel()
{
    d_ptr->model = HAppContext::getContextPointer<IModel>("IModel");
    connect(d_ptr->model, &IModel::threadInitFinished, this, &HAbstractMainWindow::updateStatusBar);
    connect(d_ptr->model, &IModel::threadStartFailed, this, &HAbstractMainWindow::showDeviceFailed);
    connect(d_ptr->model, &IModel::threadStateChanged, this, &HAbstractMainWindow::updateLabel);
    connect(d_ptr->model, &IModel::actionFailed, this, &HAbstractMainWindow::showActionFailed);
 //   d_ptr->model->start();
}

void HAbstractMainWindow::initCentralWidget()
{
    d_ptr->testWidget = HAppContext::getContextPointer<ITestWidget>("ITestWidget");
    setCentralWidget(d_ptr->testWidget);
    for (auto menu : d_ptr->testWidget->menus())
        menuBar()->insertMenu(d_ptr->actionSeparator, menu);
    for (auto toolBar : d_ptr->testWidget->toolBars())
        insertToolBar(d_ptr->toolBarLogo, toolBar);
    d_ptr->testWidget->start();
}

void HAbstractMainWindow::showDeviceFailed(QString text)
{
    QMessageBox::critical(this, "", text);
#ifndef QT_DEBUG
    close();
#endif
}

void HAbstractMainWindow::showActionFailed(HActionType action, QString text)
{
    Q_UNUSED(action);
    QMessageBox::warning(this, "", text);
}

void HAbstractMainWindow::updateStatusBar(QStringList list)
{
    for (auto w : d_ptr->labels)
        statusBar()->removeWidget(w);
    d_ptr->labels.clear();
    for (auto s : list)
    {
        auto l = new QLabel;
        l->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(s));
        d_ptr->labels.insert(s, l);
        statusBar()->addWidget(l);
    }
}

void HAbstractMainWindow::updateLabel(QString name, int state)
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

void HAbstractMainWindow::open()
{
    if (!d_ptr->model->openFile())
        return;
    QMessageBox::information(this, "", tr("\n打开文件成功！\n"));
    updatetWindowTitle();
}

void HAbstractMainWindow::save()
{
    if (!d_ptr->model->saveFile())
        return;
    QMessageBox::information(this, "", tr("\n保存文件成功！\n"));
}

void HAbstractMainWindow::saveAs()
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
            + tr("<p>版权 2017-2019 %1. 保留所有权利. <p>").arg(QApplication::organizationName())
            + tr("<p>%1<p>").arg(summary());
    QMessageBox::about(this, tr("关于 %1").arg(abbreviation), text);
}

QString HAbstractMainWindow::summary()
{
    return QString();
}

HE_GUI_END_NAMESPACE

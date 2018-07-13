#include "HMainWindow_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/IFileStream.h"
#include "HeData/IConfigManage.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QApplication>

HE_GUI_BEGIN_NAMESPACE

HMainWindowPrivate::HMainWindowPrivate(HMainWindow *p)
    : q_ptr(p)
{
}

HMainWindow::HMainWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new HMainWindowPrivate(this))
{
    init();
}

HMainWindow::HMainWindow(HMainWindowPrivate &p, QWidget *parent)
    : QMainWindow(parent), d_ptr(&p)
{
    init();
}

HMainWindow::~HMainWindow()
{
    qDebug() << __func__;
}

void HMainWindow::setConfigFile(QString fileName)
{
    d_ptr->cfgFileName = fileName;
    setWindowFilePath(fileName);
}

bool HMainWindow::setConfigManage(IConfigManage *p)
{
    d_ptr->configManage = p;
    if (!d_ptr->configManage->fileStream()->readFile(d_ptr->cfgFileName))
    {
        QMessageBox::warning(this, "", tr("找不到校准文件，正在使用默认的校准。"));
        return false;
    }
    return true;
}

void HMainWindow::setModel(IModel *p)
{
    d_ptr->model = p;
    d_ptr->model->setParent(this);
    connect(d_ptr->model, &IModel::threadStartFailed, this, &HMainWindow::showDeviceFailed);
    connect(d_ptr->model, &IModel::actionFailed, this, &HMainWindow::showActionFailed);
    connect(d_ptr->model, &IModel::threadInitFinished, this, &HMainWindow::updateStatusBar);
    connect(d_ptr->model, &IModel::threadStateChanged, this, &HMainWindow::updateLabel);
    //    connect(d->model, &IModel::actionFinished, this, [=](HActionType action) { QMessageBox::information(this, "", toComment(action)); });
    d_ptr->model->start();
}

void HMainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    initImportExport();
    createAction();
    createActionGroup();
    createMenu();
    createToolBar();
    createToolBarLogo();
    createConnect();
    initMenu();
    initToolBar();
    initStatusBar();
}

void HMainWindow::initImportExport()
{
    d_ptr->importExport.clear();
}

void HMainWindow::createAction()
{
    d_ptr->actionOpen = new QAction(tr("打开(&O)..."), this);
    d_ptr->actionOpen->setIcon(QIcon(":/images/Open.png"));
    d_ptr->actionOpen->setIconText(tr("\n打开"));
    d_ptr->actionOpen->setShortcut(QKeySequence::Open);
    d_ptr->actionSave = new QAction(tr("保存(&S)"), this);
    d_ptr->actionSave->setIcon(QIcon(":/images/Save.png"));
    d_ptr->actionSave->setIconText(tr("\n保存"));
    d_ptr->actionSave->setShortcut(QKeySequence::Save);
    d_ptr->actionSaveAs = new QAction(tr("另存为(&A)..."), this);
    d_ptr->actionSaveAs->setIcon(QIcon(":/images/SaveAs.png"));
    d_ptr->actionSaveAs->setIconText(tr("\n另存为"));
    d_ptr->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    d_ptr->actionExit = new QAction(tr("退出(&X)"), this);
    d_ptr->actionExit->setIcon(QIcon(":/images/Exit.png"));
    d_ptr->actionExit->setIconText(tr("\n退出"));
    d_ptr->actionExit->setShortcut(tr("Ctrl+Q"));
    d_ptr->actionAbout = new QAction(tr("关于(&A)..."), this);
}

void HMainWindow::createActionGroup()
{
    d_ptr->actionGroupImport = new QActionGroup(this);
    d_ptr->actionGroupExport = new QActionGroup(this);
    auto i = d_ptr->importExport.constBegin();
    while (i != d_ptr->importExport.constEnd())
    {
        d_ptr->actionGroupImport->addAction(i.key())->setData(i.value());
        d_ptr->actionGroupExport->addAction(i.key())->setData(i.value());
    }
}

void HMainWindow::createMenu()
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
        d_ptr->menuImport->addActions(d_ptr->actionGroupImport->actions());
    }
    d_ptr->menuFile->addSeparator();
    d_ptr->menuFile->addAction(d_ptr->actionExit);
    d_ptr->menuHelp = new QMenu(tr("帮助(&H)"));
    d_ptr->menuHelp->addAction(d_ptr->actionAbout);
}

void HMainWindow::createToolBar()
{

}

void HMainWindow::createToolBarLogo()
{

}

void HMainWindow::createConnect()
{
    connect(d_ptr->actionOpen, &QAction::triggered, this, open);
    connect(d_ptr->actionSave, &QAction::triggered, this, save);
    connect(d_ptr->actionSaveAs, &QAction::triggered, this, saveAs);
    connect(d_ptr->actionExit, &QAction::triggered, this, close);
    connect(d_ptr->actionAbout, &QAction::triggered, this, about);
    connect(d_ptr->actionGroupImport, &QActionGroup::triggered, this, importFile);
    connect(d_ptr->actionGroupExport, &QActionGroup::triggered, this, exportFile);
}

void HMainWindow::initMenu()
{
    menuBar()->addMenu(d_ptr->menuFile);
//    menuBar()->addMenu(m_pMenuCommunication);
//    menuBar()->addMenu(m_pMenuCalibrate);
//    menuBar()->addMenu(m_pMenuSet);
//    menuBar()->addMenu(m_pMenuGrade);
//    menuBar()->addMenu(m_pMenuJudgment);
//    menuBar()->addMenu(m_pMenuAdjustment);
    d_ptr->actionSeparator = menuBar()->addSeparator();
//    menuBar()->addMenu(m_pMenuAccount);
//    menuBar()->addMenu(m_pMenuDatabase);
    menuBar()->addMenu(d_ptr->menuHelp);
}

void HMainWindow::initToolBar()
{

}

void HMainWindow::initStatusBar()
{
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

void HMainWindow::showDeviceFailed(QString text)
{
    QMessageBox::critical(this, "", text);
#ifndef QT_DEBUG
    close();
#endif
}

void HMainWindow::showActionFailed(HActionType action, QString text)
{
    Q_UNUSED(action);
    QMessageBox::warning(this, "", text);
}

void HMainWindow::updateStatusBar(QStringList list)
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

void HMainWindow::updateLabel(QString name, int state)
{
    if (!d_ptr->labels.contains(name))
        return;
    if (state == 1)
        d_ptr->labels.value(name)->setText(tr("%1:<font color=#00FF00>开启</font>").arg(name));
    else
        d_ptr->labels.value(name)->setText(tr("%1:<font color=#FF0000>关闭</font>").arg(name));
}

void HMainWindow::open()
{
    QString fileName;
    if (!d_ptr->configManage->fileStream()->openFile("", ".", &fileName))
        return;
    QMessageBox::information(this, "", tr("\n打开文件成功！\n"));
    setConfigFile(fileName);
    emit configManageChanged(d_ptr->configManage->contain());
}

void HMainWindow::save()
{
    if (!d_ptr->configManage->fileStream()->writeFile(d_ptr->cfgFileName))
        return;
    QMessageBox::information(this, "", tr("\n保存文件成功！\n"));
}

void HMainWindow::saveAs()
{
    QString fileName;
    if (!d_ptr->configManage->fileStream()->saveAsFile("", ".", &fileName))
        return;
    QMessageBox::information(this, "", tr("\n保存文件成功！\n"));
    setConfigFile(fileName);
}

void HMainWindow::about()
{
    QString abbreviation,text;

    abbreviation = QApplication::applicationName().split(" ").first();
    text = tr("<h2>%1</h2><p>").arg(abbreviation)
            + tr("<p>版本 %1<p>").arg(QApplication::applicationVersion())
            + tr("<p>%1<p>").arg(QApplication::applicationName())
            + tr("<p>版权 2017-2019 %1. 保留所有权利. <p>").arg(QApplication::organizationName())
            + tr("<p>%1<p>").arg(d_ptr->summary);
    QMessageBox::about(this, tr("关于 %1").arg(abbreviation), text);
}

void HMainWindow::importFile(QAction *p)
{
    if (p == nullptr)
        return;
    auto type = p->data().toUInt();
    if (!d_ptr->configManage->importPart(type))
        return;
    QMessageBox::information(this, "", tr("\n导入成功！\n"));
    emit configManageChanged(type);
}

void HMainWindow::exportFile(QAction *p)
{
    if (p == nullptr || d_ptr->configManage->exportPart(p->data().toUInt()))
        return;
    QMessageBox::information(this, "", tr("\n导出成功！\n"));
}

HE_GUI_END_NAMESPACE

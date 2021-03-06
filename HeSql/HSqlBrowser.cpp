#include "HSqlBrowser_p.h"
#include "ISqlHandle.h"
#include "ISqlPrint.h"
#include "HSqlTableView.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QToolBar>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlBrowser::HSqlBrowser(QWidget *parent) :
    ISqlBrowser(parent),
    d_ptr(new HSqlBrowserPrivate)
{
    init();
}

HSqlBrowser::HSqlBrowser(HSqlBrowserPrivate &p, QWidget *parent) :
    ISqlBrowser(parent),
    d_ptr(&p)
{
    init();
}

HSqlBrowser::~HSqlBrowser()
{
    qDebug() << __func__;
}

void HSqlBrowser::initialize(QVariantMap /*param*/)
{
}

QString HSqlBrowser::typeName()
{
    return "HSqlBrowser";
}

void HSqlBrowser::setRecordHandle(ISqlHandle *p)
{
    d_ptr->handle = p;
    if (d_ptr->handle != nullptr && d_ptr->model != nullptr)
        d_ptr->handle->setModel(d_ptr->model);
}

void HSqlBrowser::setRecordPrint(ISqlPrint *p)
{
    d_ptr->print = p;
    if (d_ptr->print != nullptr && d_ptr->model != nullptr)
        d_ptr->print->setModel(d_ptr->model);
}

void HSqlBrowser::setModel(ISqlTableModel *p)
{
    if (d_ptr->model == p)
        return;
    d_ptr->model = p;
    d_ptr->view->setModel(p);
    if (d_ptr->handle != nullptr)
        d_ptr->handle->setModel(p);
    if (d_ptr->print != nullptr)
        d_ptr->print->setModel(p);
}

void HSqlBrowser::removeRecord()
{
    auto s = d_ptr->view->selectionModel()->selection();
    if (s.isEmpty())
        return;
    d_ptr->handle->removeRecord(s.first().top(), s.first().height());
}

void HSqlBrowser::exportExcel()
{
    auto s = d_ptr->view->selectionModel()->selection();
    if (s.isEmpty())
        return;
    if (s.first().height() == 1)
        d_ptr->print->exportExcel();
    else
        d_ptr->print->exportExcel(s.first().top(), s.first().height());
}

void HSqlBrowser::init()
{
    createAction();
    createToolBar();
    createTableView();
    createLayout();
    resize(1000, 700);
    setWindowFlags(Qt::Window);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("数据库浏览"));
}

void HSqlBrowser::createAction()
{
    d_ptr->actionRevert = new QAction(tr("所有记录(&R)"), this);
    d_ptr->actionRevert->setIcon(QIcon(":/image/Reset.png"));
    d_ptr->actionRevert->setIconText(tr("所有记录"));
    d_ptr->actionFind = new QAction(tr("查询记录(&F)"), this);
    d_ptr->actionFind->setIcon(QIcon(":/image/Find.png"));
    d_ptr->actionFind->setIconText(tr("查询记录"));
    d_ptr->actionRemove = new QAction(tr("删除记录(&R)"), this);
    d_ptr->actionRemove->setIcon(QIcon(":/image/Remove.png"));
    d_ptr->actionRemove->setIconText(tr("删除记录"));
    d_ptr->actionExportExcel = new QAction(tr("导出记录(&E)"), this);
    d_ptr->actionExportExcel->setIcon(QIcon(":/image/Excel.png"));
    d_ptr->actionExportExcel->setIconText(tr("导出记录"));
    d_ptr->actionExportPdf = new QAction(tr("导出记录(&D)"), this);
    d_ptr->actionExportPdf->setIcon(QIcon(":/image/Pdf.png"));
    d_ptr->actionExportPdf->setIconText(tr("导出记录"));
    d_ptr->actionPrint = new QAction(tr("打印(&P)"), this);
    d_ptr->actionPrint->setIcon(QIcon(":/image/Printer.png"));
    d_ptr->actionPrint->setIconText(tr("打印"));
    d_ptr->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d_ptr->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d_ptr->actionPrintPreview->setIconText(tr("打印预览"));
    connect(d_ptr->actionRevert, &QAction::triggered, this, [=]{ if (d_ptr->handle != nullptr) d_ptr->handle->revertRecord(); });
    connect(d_ptr->actionFind, &QAction::triggered, this, [=]{ if (d_ptr->handle != nullptr) d_ptr->handle->findRecord(); });
    connect(d_ptr->actionRemove, &QAction::triggered, this, &HSqlBrowser::removeRecord);
    connect(d_ptr->actionExportExcel, &QAction::triggered, this, &HSqlBrowser::exportExcel);
    connect(d_ptr->actionExportPdf, &QAction::triggered, this, [=]{ if (d_ptr->print != nullptr) d_ptr->print->exportPdf(); });
    connect(d_ptr->actionPrint, &QAction::triggered, this, [=]{ if (d_ptr->print != nullptr) d_ptr->print->print(); });
    connect(d_ptr->actionPrintPreview, &QAction::triggered, [=]{ if (d_ptr->print != nullptr) d_ptr->print->printPreview(); });
}

void HSqlBrowser::createToolBar()
{
    d_ptr->toolBar = new QToolBar(tr("数据操作(&S)"));
    d_ptr->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d_ptr->toolBar->setMovable(false);
    d_ptr->toolBar->setIconSize(QSize(40,40));
    d_ptr->toolBar->addAction(d_ptr->actionRevert);
    d_ptr->toolBar->addAction(d_ptr->actionFind);
    d_ptr->toolBar->addAction(d_ptr->actionRemove);
    d_ptr->toolBar->addAction(d_ptr->actionExportExcel);
    d_ptr->toolBar->addAction(d_ptr->actionExportPdf);
    d_ptr->toolBar->addAction(d_ptr->actionPrint);
    d_ptr->toolBar->addAction(d_ptr->actionPrintPreview);
}

void HSqlBrowser::createTableView()
{
    d_ptr->view = new HSqlTableView;
    HPluginHelper::addSeparator(d_ptr->view);
    d_ptr->view->addAction(d_ptr->actionRemove);
    d_ptr->view->addAction(d_ptr->actionExportExcel);
    d_ptr->view->addAction(d_ptr->actionExportPdf);
    d_ptr->view->addAction(d_ptr->actionPrint);
    d_ptr->view->addAction(d_ptr->actionPrintPreview);
}

void HSqlBrowser::createLayout()
{
    auto layout = new QGridLayout(this);
    layout->setSpacing(9);
    layout->addWidget(d_ptr->toolBar, 0, 0);
    layout->addWidget(d_ptr->view, 1, 0);
}

HE_SQL_END_NAMESPACE

#include "HSqlBrowser_p.h"
#include "ISqlRecordHandle.h"
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

void HSqlBrowser::setModel(ISqlTableModel *p)
{
    d_ptr->view->setModel(p);
}

void HSqlBrowser::setRecordHandle(ISqlRecordHandle *p)
{
    d_ptr->recordHandle = p;

}

void HSqlBrowser::init()
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
    auto toolBar = new QToolBar(tr("数据操作(&S)"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(40,40));
    toolBar->addAction(d_ptr->actionRevert);
    toolBar->addAction(d_ptr->actionFind);
    toolBar->addAction(d_ptr->actionRemove);
    toolBar->addAction(d_ptr->actionExportExcel);
    toolBar->addAction(d_ptr->actionExportPdf);
    toolBar->addAction(d_ptr->actionPrint);
    toolBar->addAction(d_ptr->actionPrintPreview);
    d_ptr->view = new HSqlTableView;
    HPluginHelper::addSeparator(d_ptr->view);
    d_ptr->view->addAction(d_ptr->actionRemove);
    d_ptr->view->addAction(d_ptr->actionExportExcel);
    d_ptr->view->addAction(d_ptr->actionExportPdf);
    d_ptr->view->addAction(d_ptr->actionPrint);
    d_ptr->view->addAction(d_ptr->actionPrintPreview);
    auto layout = new QGridLayout(this);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(20);
    layout->addWidget(toolBar, 0, 0);
    layout->addWidget(d_ptr->view, 1, 0);

    connect(d_ptr->actionRevert, &QAction::triggered, this, [=]{ d_ptr->recordHandle->revertRecord(); });
    connect(d_ptr->actionFind, &QAction::triggered , this, [=]{ d_ptr->recordHandle->findRecord(); });
//    connect(m_pActionRemove, SIGNAL(triggered()), this, SLOT(recordRemove()));
//    connect(m_pActionExportExcel, SIGNAL(triggered()), this, SLOT(exportExcel()));
//    connect(m_pActionExportPdf, SIGNAL(triggered()), m_pTableModel, SLOT(exportPdf()));
//    connect(m_pActionPrint, SIGNAL(triggered()), m_pTableModel, SLOT(recordPrint()));
//    connect(m_pActionPrintPreview, SIGNAL(triggered()), m_pTableModel, SLOT(recordPrintPreview()));

    resize(1000, 700);
    setWindowFlags(Qt::Window);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("数据库浏览"));
}

HE_SQL_END_NAMESPACE

#include "HTableView_p.h"
#include "HPluginHelper.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QHeaderView>

HTableView::HTableView(QWidget *parent) :
    QTableView(parent),
    d_ptr(new HTableViewPrivate)
{
    init();
}

HTableView::HTableView(HTableViewPrivate &p, QWidget *parent) :
    QTableView(parent),
    d_ptr(&p)
{
    init();
}

HTableView::~HTableView() = default;

void HTableView::setEditTriggers(EditTriggers triggers)
{
    d_ptr->actionPaste->setVisible(triggers != QAbstractItemView::NoEditTriggers);
    d_ptr->actionImport->setVisible(d_ptr->exportImport && triggers != QAbstractItemView::NoEditTriggers);
    QTableView::setEditTriggers(triggers);
}

void HTableView::setExportImport(bool b)
{
    if (d_ptr->exportImport == b)
        return;
    d_ptr->exportImport = b;
    d_ptr->actionExport->setVisible(b);
    d_ptr->actionImport->setVisible(b && editTriggers() != QAbstractItemView::NoEditTriggers);
}

void HTableView::copy()
{
    HPluginHelper::copy(this);
}

void HTableView::paste()
{
    if (!HPluginHelper::paste(this).isEmpty())
        emit contentChanged();
}

void HTableView::exportExcel()
{
    HPluginHelper::exportExcel(model());
}

void HTableView::importExcel()
{
    if (HPluginHelper::importExcel(model()))
        emit contentChanged();
}

void HTableView::init()
{
    d_ptr->actionCopy = new QAction(tr("复制(&C)"), this);
    d_ptr->actionCopy->setIcon(QIcon(":/image/Copy.png"));
    d_ptr->actionCopy->setShortcut(QKeySequence::Copy);
    d_ptr->actionPaste = new QAction(tr("粘贴(&V)"), this);
    d_ptr->actionPaste->setIcon(QIcon(":/image/Paste.png"));
    d_ptr->actionPaste->setShortcut(QKeySequence::Paste);
    d_ptr->actionExport = new QAction(tr("导出表(&E)"), this);
    d_ptr->actionImport = new QAction(tr("导入表(&I)"), this);
    addAction(d_ptr->actionCopy);
    addAction(d_ptr->actionPaste);
    addAction(d_ptr->actionExport);
    addAction(d_ptr->actionImport);
    connect(d_ptr->actionCopy, &QAction::triggered, this, &HTableView::copy);
    connect(d_ptr->actionPaste, &QAction::triggered, this, &HTableView::paste);
    connect(d_ptr->actionExport, &QAction::triggered, this, &HTableView::exportExcel);
    connect(d_ptr->actionImport, &QAction::triggered, this, &HTableView::importExcel);
    horizontalHeader()->setDefaultSectionSize(80);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setMinimumSectionSize(60);
    verticalHeader()->setDefaultSectionSize(35);
    verticalHeader()->setHighlightSections(false);
    verticalHeader()->setMinimumSectionSize(30);
    setAlternatingRowColors(true);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setWindowIcon(QIcon(":/image/Table.png"));
}

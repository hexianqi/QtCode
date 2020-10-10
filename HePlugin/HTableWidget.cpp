#include "HTableWidget_p.h"
#include "HPluginHelper.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QHeaderView>

HTableWidget::HTableWidget(QWidget *parent) :
    QTableWidget(parent),
    d_ptr(new HTableWidgetPrivate)
{
    init();
}

HTableWidget::HTableWidget(HTableWidgetPrivate &p, QWidget *parent) :
    QTableWidget(parent),
    d_ptr(&p)
{
    init();
}

HTableWidget::~HTableWidget() = default;

void HTableWidget::removeRows(int row, int count)
{
    if (count < 1 || row < 0)
        return;

    int i,n;
    n = qMin(rowCount() - row, count);
    for (i = 0; i < n; i++)
        removeRow(row);
}

void HTableWidget::setEditTriggers(EditTriggers triggers)
{
    d_ptr->actionPaste->setVisible(triggers != QAbstractItemView::NoEditTriggers);
    d_ptr->actionImport->setVisible(triggers != QAbstractItemView::NoEditTriggers);
    QTableWidget::setEditTriggers(triggers);
}

QTableWidgetItem *HTableWidget::item(int row, int column)
{
    auto item = QTableWidget::item(row, column);
    if (!item)
    {
        item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        setItem(row, column, item);
    }
    return item;
}

void HTableWidget::init()
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
    connect(d_ptr->actionCopy, &QAction::triggered, this, [=] { HPluginHelper::copy(this); });
    connect(d_ptr->actionPaste, &QAction::triggered, this, [=] { HPluginHelper::paste(this); });
    connect(d_ptr->actionExport, &QAction::triggered, this, [=] { HPluginHelper::exportExcel(model()); });
    connect(d_ptr->actionImport, &QAction::triggered, this, [=] { HPluginHelper::importExcel(model()); });
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

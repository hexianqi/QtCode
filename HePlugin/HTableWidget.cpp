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

void HTableWidget::setEditTriggers(EditTriggers triggers)
{
    d_ptr->actions.value(ActionPaste)->setEnabled(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionPaste)->setVisible(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionImport)->setEnabled(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
    d_ptr->actions.value(ActionImport)->setVisible(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
    QTableWidget::setEditTriggers(triggers);
}

void HTableWidget::setActionContain(quint32 value)
{
    if (d_ptr->actionContain == value)
        return;
    d_ptr->actionContain = value;
    d_ptr->actions.value(ActionCopy)->setEnabled(d_ptr->actionContain & ActionCopy);
    d_ptr->actions.value(ActionCopy)->setVisible(d_ptr->actionContain & ActionCopy);
    d_ptr->actions.value(ActionExport)->setEnabled(d_ptr->actionContain & ActionExport);
    d_ptr->actions.value(ActionExport)->setVisible(d_ptr->actionContain & ActionExport);
    d_ptr->actions.value(ActionPaste)->setEnabled(editTriggers() != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionPaste)->setVisible(editTriggers() != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionImport)->setEnabled(editTriggers() != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
    d_ptr->actions.value(ActionImport)->setVisible(editTriggers() != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
}

void HTableWidget::removeRows(int row, int count)
{
    if (count < 1 || row < 0)
        return;

    int i,n;
    n = qMin(rowCount() - row, count);
    for (i = 0; i < n; i++)
        removeRow(row);
}

void HTableWidget::copy()
{
    HPluginHelper::copy(this);
}

void HTableWidget::paste()
{
    if (!HPluginHelper::paste(this).isEmpty())
        emit contentChanged();
}

void HTableWidget::exportExcel()
{
    HPluginHelper::exportExcel(this);
}

void HTableWidget::importExcel()
{
    if (HPluginHelper::importExcel(this))
        emit contentChanged();
}

void HTableWidget::init()
{
    auto actionCopy = new QAction(tr("复制(&C)"), this);
    actionCopy->setIcon(QIcon(":/image/Copy.png"));
    actionCopy->setShortcut(QKeySequence::Copy);
    auto actionPaste = new QAction(tr("粘贴(&V)"), this);
    actionPaste->setIcon(QIcon(":/image/Paste.png"));
    actionPaste->setShortcut(QKeySequence::Paste);
    auto actionExport = new QAction(tr("导出表(&E)"), this);
    auto actionImport = new QAction(tr("导入表(&I)"), this);
    connect(actionCopy, &QAction::triggered, this, &HTableWidget::copy);
    connect(actionPaste, &QAction::triggered, this, &HTableWidget::paste);
    connect(actionExport, &QAction::triggered, this, &HTableWidget::exportExcel);
    connect(actionImport, &QAction::triggered, this, &HTableWidget::importExcel);
    d_ptr->actions.insert(ActionCopy, actionCopy);
    d_ptr->actions.insert(ActionPaste, actionPaste);
    d_ptr->actions.insert(ActionExport, actionExport);
    d_ptr->actions.insert(ActionImport, actionImport);
    for (auto i : d_ptr->actions)
        addAction(i);
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

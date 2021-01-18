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
    d_ptr->actions.value(ActionPaste)->setEnabled(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionPaste)->setVisible(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionPaste));
    d_ptr->actions.value(ActionImport)->setEnabled(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
    d_ptr->actions.value(ActionImport)->setVisible(triggers != QAbstractItemView::NoEditTriggers && (d_ptr->actionContain & ActionImport));
    QTableView::setEditTriggers(triggers);
}

void HTableView::setActionContain(quint32 value)
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
    HPluginHelper::exportExcel(this);
}

void HTableView::importExcel()
{
    if (HPluginHelper::importExcel(this))
        emit contentChanged();
}

void HTableView::init()
{
    auto actionCopy = new QAction(tr("复制(&C)"), this);
    actionCopy->setIcon(QIcon(":/image/Copy.png"));
    actionCopy->setShortcut(QKeySequence::Copy);
    auto actionPaste = new QAction(tr("粘贴(&V)"), this);
    actionPaste->setIcon(QIcon(":/image/Paste.png"));
    actionPaste->setShortcut(QKeySequence::Paste);
    auto actionExport = new QAction(tr("导出表(&E)"), this);
    auto actionImport = new QAction(tr("导入表(&I)"), this);
    connect(actionCopy, &QAction::triggered, this, &HTableView::copy);
    connect(actionPaste, &QAction::triggered, this, &HTableView::paste);
    connect(actionExport, &QAction::triggered, this, &HTableView::exportExcel);
    connect(actionImport, &QAction::triggered, this, &HTableView::importExcel);
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

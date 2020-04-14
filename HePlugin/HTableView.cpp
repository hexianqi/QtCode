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
    QTableView::setEditTriggers(triggers);
}

void HTableView::init()
{
    d_ptr->actionCopy = new QAction(tr("复制(&C)"), this);
    d_ptr->actionCopy->setIcon(QIcon(":/image/Copy.png"));
    d_ptr->actionCopy->setShortcut(QKeySequence::Copy);
    d_ptr->actionPaste = new QAction(tr("粘贴(&V)"), this);
    d_ptr->actionPaste->setIcon(QIcon(":/image/Paste.png"));
    d_ptr->actionPaste->setShortcut(QKeySequence::Paste);
    addAction(d_ptr->actionCopy);
    addAction(d_ptr->actionPaste);
    connect(d_ptr->actionCopy, &QAction::triggered, this, [=] { HPluginHelper::copy(this); });
    connect(d_ptr->actionPaste, &QAction::triggered, this, [=] { HPluginHelper::paste(this); });
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

#include "HConfigWidget_p.h"
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

HConfigWidgetDelegate::HConfigWidgetDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void HConfigWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    auto ds = option.decorationSize;
    auto decorationRect = QRect(option.rect.x() + 4, option.rect.top() + 4, option.rect.width() - 8, ds.height());
    auto icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    icon.paint(painter, decorationRect, Qt::AlignHCenter|Qt::AlignTop, option.state & QStyle::State_Enabled ? ((option.state & QStyle::State_Selected) && option.showDecorationSelected ? QIcon::Selected : QIcon::Normal) : QIcon::Disabled);

    auto displayText = index.data(Qt::DisplayRole).toString();
    auto displayRect = option.rect.adjusted(2, ds.height() + 2, -2, -2);
    painter->setPen(option.palette.color(option.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text));
    painter->drawText(displayRect, Qt::AlignHCenter|Qt::AlignBottom|Qt::TextWordWrap, option.fontMetrics.elidedText(displayText, option.textElideMode, displayRect.width()));
}

QSize HConfigWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto ds = option.decorationSize;
    auto width = option.fontMetrics.width(index.data(Qt::DisplayRole).toString());
    auto ts = QSize(width, option.fontMetrics.height());
    return QSize(qBound(ds.width(), ts.width(), option.rect.width()), ds.height() + 6 + ts.height());
}

HConfigWidget::HConfigWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HConfigWidgetPrivate)
{
    init();
}

HConfigWidget::HConfigWidget(HConfigWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

bool HConfigWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::WindowTitleChange)
    {
        auto w = qobject_cast<QWidget *>(object);
        for (int i = 0; i < count(); i++)
        {
            if (group(i) == w)
                setGroupLabel(i, w->windowTitle());
        }
        return false;
    }
    return QWidget::eventFilter(object, event);
}

HConfigWidget::~HConfigWidget()
{
}

int HConfigWidget::currentIndex() const
{
    return d_ptr->stack->currentIndex();
}

QSize HConfigWidget::iconSize() const
{
    return d_ptr->view->iconSize();
}

int HConfigWidget::count() const
{
    return d_ptr->stack->count();
}

QWidget *HConfigWidget::group(int index) const
{
    return d_ptr->stack->widget(index);
}

QWidget *HConfigWidget::currentGroup() const
{
    return d_ptr->stack->currentWidget();
}

void HConfigWidget::addGroup(QWidget *group, const QIcon &icon, const QString &name)
{
    insertGroup(d_ptr->stack->count(), group, icon, name);
}

void HConfigWidget::insertGroup(int index, QWidget *group, const QIcon &icon, const QString &name)
{
    d_ptr->stack->insertWidget(index, group);

    auto item = new QListWidgetItem;
    if (name.isNull())
    {
        item->setText(group->windowTitle());
    }
    else
    {
        item->setText(name);
        group->setWindowTitle(name);
    }
    if (icon.isNull())
    {
        item->setIcon(group->windowIcon());
    }
    else
    {
        item->setIcon(icon);
        group->setWindowIcon(icon);
    }
    d_ptr->view->insertItem(index, item);

    if (d_ptr->stack->count() == 1)
    {
        d_ptr->titleLabel->setText(d_ptr->view->item(index)->text());
        setCurrentIndex(0);
    }
    group->installEventFilter(this);
}

void HConfigWidget::removeGroup(QWidget *group)
{
    int index = d_ptr->stack->indexOf(group);
    if (index < 0)
        return;
    auto item = d_ptr->view->takeItem(index);
    d_ptr->stack->removeWidget(group);
    group->removeEventFilter(this);
    delete item;
    delete group;
}

void HConfigWidget::removeGroup(int index)
{
    removeGroup(d_ptr->stack->widget(index));
}

void HConfigWidget::setCurrentIndex(int value)
{
    if (value == currentIndex() || value < 0 || value >= d_ptr->view->count())
        return;

    d_ptr->stack->setCurrentIndex(value);
    d_ptr->view->setCurrentRow(value);
    d_ptr->titleLabel->setText(d_ptr->view->item(value)->text());
    emit currentIndexChanged(value);
}

void HConfigWidget::setIconSize(const QSize &value)
{
    d_ptr->view->setIconSize(value);
}

void HConfigWidget::setCurrentGroup(QWidget *group)
{
    setCurrentIndex(d_ptr->stack->indexOf(group));
}

void HConfigWidget::setGroupIcon(int index, const QIcon &icon)
{
    auto w = group(index);
    w->setWindowIcon(icon);
    d_ptr->view->item(index)->setIcon(icon);
}

void HConfigWidget::setGroupLabel(int index, const QString &title)
{
    auto w = group(index);
    w->setWindowTitle(title);
    d_ptr->view->item(index)->setText(title);
    if (index == currentIndex())
        d_ptr->titleLabel->setText(title);
}

void HConfigWidget::save()
{
    if (d_ptr->saving)
        return;
    d_ptr->saving = true;
    emit saving();
    d_ptr->saving = false;
}

void HConfigWidget::apply()
{
    if (d_ptr->applying)
        return;
    d_ptr->applying = true;
    emit applying(currentIndex());
    QMetaObject::invokeMethod(currentGroup(), "apply");
    d_ptr->applying = false;
}

void HConfigWidget::discard()
{
    if (d_ptr->discarding)
        return;
    d_ptr->discarding = true;
    emit discarding(currentIndex());
    QMetaObject::invokeMethod(currentGroup(), "discard");
    d_ptr->discarding = false;
}

void HConfigWidget::init()
{
    d_ptr->titleLabel = new QLabel;
    auto f = d_ptr->titleLabel->font();
    f.setBold(true);
    d_ptr->titleLabel->setFont(f);
    auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    d_ptr->stack = new QStackedWidget;
    d_ptr->view = new QListWidget;
    d_ptr->view->setSelectionMode(QAbstractItemView::SingleSelection);
    d_ptr->view->setIconSize(QSize(48, 48));
    d_ptr->view->setMaximumWidth(150);
    d_ptr->view->setItemDelegate(new HConfigWidgetDelegate(this));
    auto pol = d_ptr->view->sizePolicy();
    pol.setHorizontalStretch(1);
    d_ptr->view->setSizePolicy(pol);
    pol = d_ptr->stack->sizePolicy();
    pol.setHorizontalStretch(5);
    d_ptr->stack->setSizePolicy(pol);
    pol = d_ptr->titleLabel->sizePolicy();
    pol.setHorizontalStretch(5);
    d_ptr->titleLabel->setSizePolicy(pol);
    pol = line->sizePolicy();
    pol.setHorizontalStretch(5);
    line->setSizePolicy(pol);
    auto l = new QGridLayout(this);
    l->addWidget(d_ptr->view, 0, 0, 3, 1);
    l->addWidget(d_ptr->titleLabel, 0, 1);
    l->addWidget(line, 1, 1);
    l->addWidget(d_ptr->stack, 2, 1);/*





    auto vl = new QVBoxLayout;
    vl->setMargin(0);
    vl->setSpacing(2);
    vl->addWidget(d_ptr->titleLabel);
    vl->addWidget(line);
    vl->addWidget(d_ptr->stack);
    d_ptr->layout = new QHBoxLayout(this);
    d_ptr->layout->addWidget(d_ptr->view);
    d_ptr->layout->setMargin(0);
    d_ptr->layout->addLayout(vl);*/
    connect(d_ptr->view, &QListWidget::currentRowChanged, this, &HConfigWidget::setCurrentIndex);
}

HE_CONTROL_END_NAMESPACE

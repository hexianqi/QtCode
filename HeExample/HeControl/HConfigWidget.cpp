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
    icon.paint(painter, decorationRect, Qt::AlignHCenter | Qt::AlignTop, option.state & QStyle::State_Enabled ? ((option.state & QStyle::State_Selected) && option.showDecorationSelected ? QIcon::Selected : QIcon::Normal) : QIcon::Disabled);

    auto displayText = index.data(Qt::DisplayRole).toString();
    auto displayRect = option.rect.adjusted(2, ds.height() + 2, -2, -2);
    painter->setPen(option.palette.color(option.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text));
    painter->drawText(displayRect, Qt::AlignHCenter | Qt::AlignBottom | Qt::TextWordWrap, option.fontMetrics.elidedText(displayText, option.textElideMode, displayRect.width()));
}

QSize HConfigWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto ds = option.decorationSize;
    auto width = option.fontMetrics.width(index.data(Qt::DisplayRole).toString());
    auto ts = QSize(width, option.fontMetrics.height());
    return QSize(qBound(ds.width(), ts.width(), option.rect.width()), ds.height() + 6 + ts.height());
}

HConfigWidget::HConfigWidget(QWidget *parent) :
    HAbstractMultiWidget(*new HConfigWidgetPrivate, parent)
{
    init();
}

HConfigWidget::HConfigWidget(HConfigWidgetPrivate &p, QWidget *parent) :
     HAbstractMultiWidget(p, parent)
{
    init();
}

HConfigWidget::~HConfigWidget()
{
}

int HConfigWidget::count() const
{
    Q_D(const HConfigWidget);
    return d->stack->count();
}

int HConfigWidget::indexOf(QWidget *p) const
{
    Q_D(const HConfigWidget);
    return d->stack->indexOf(p);
}

QWidget *HConfigWidget::widget(int index) const
{
    Q_D(const HConfigWidget);
    return d->stack->widget(index);
}

QWidget *HConfigWidget::currentWidget() const
{
    Q_D(const HConfigWidget);
    return d->stack->currentWidget();
}

QSize HConfigWidget::iconSize() const
{
    Q_D(const HConfigWidget);
    return d->view->iconSize();
}

void HConfigWidget::insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    Q_D(HConfigWidget);
    HAbstractMultiWidget::insertWidget(index, widget, icon, label);
    widget->installEventFilter(this);

    auto item = new QListWidgetItem;
    item->setText(widget->windowTitle());
    item->setIcon(widget->windowIcon());

    d->stack->insertWidget(index, widget);
    d->view->insertItem(index, item);
    if (count() == 1)
        setCurrentIndex(0);
}

void HConfigWidget::removeWidget(int index)
{
    Q_D(HConfigWidget);
    if (index < 0 || index >= count())
        return;

    auto w = widget(index);
    w->removeEventFilter(this);
    d->stack->removeWidget(w);
    d->currentIndex = d->stack->currentIndex();
    delete w;
    delete d->view->takeItem(index);

    if (d->currentIndex > -1)
        d->title->setText(d->view->item(d->currentIndex)->text());
    else
        d->title->setText("");
}

bool HConfigWidget::setCurrentIndex(int value)
{
    Q_D(HConfigWidget);
    if (!HAbstractMultiWidget::setCurrentIndex(value))
        return false;
    d->stack->setCurrentIndex(value);
    d->view->setCurrentRow(value);
    d->title->setText(d->view->item(value)->text());
    return true;
}

bool HConfigWidget::setWidgetIcon(int index, const QIcon &icon)
{
    Q_D(HConfigWidget);
    if (!HAbstractMultiWidget::setWidgetIcon(index, icon))
        return false;
    d->view->item(index)->setIcon(icon);
    return true;
}

bool HConfigWidget::setWidgetTitle(int index, const QString &title)
{
    Q_D(HConfigWidget);
    if (!HAbstractMultiWidget::setWidgetTitle(index, title))
        return false;
    d->view->item(index)->setText(title);
    if (index == currentIndex())
        d->title->setText(title);
    return true;
}

void HConfigWidget::setIconSize(const QSize &value)
{
    Q_D(HConfigWidget);
    d->view->setIconSize(value);
}

void HConfigWidget::save()
{
    Q_D(HConfigWidget);
    if (d->saving)
        return;
    d->saving = true;
    emit saving();
    d->saving = false;
}

void HConfigWidget::apply()
{
    Q_D(HConfigWidget);
    if (d->applying)
        return;
    d->applying = true;
    emit applying(currentIndex());
    QMetaObject::invokeMethod(currentWidget(), "apply");
    d->applying = false;
}

void HConfigWidget::discard()
{
    Q_D(HConfigWidget);
    if (d->discarding)
        return;
    d->discarding = true;
    emit discarding(currentIndex());
    QMetaObject::invokeMethod(currentWidget(), "discard");
    d->discarding = false;
}

bool HConfigWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::WindowTitleChange || event->type() == QEvent::WindowIconChange)
    {
        auto w = qobject_cast<QWidget *>(object);
        auto i = indexOf(w);
        if (event->type() == QEvent::WindowTitleChange)
            setWidgetTitle(i, w->windowTitle());
        if (event->type() == QEvent::WindowIconChange)
            setWidgetIcon(i, w->windowIcon());
    }
    return QWidget::eventFilter(object, event);
}

void HConfigWidget::init()
{
    Q_D(HConfigWidget);
    d->title = new QLabel;
    auto f = d->title->font();
    f.setBold(true);
    d->title->setFont(f);
    auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    d->stack = new QStackedWidget;
    d->view = new QListWidget;
    d->view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->view->setIconSize(QSize(48, 48));
    d->view->setMaximumWidth(150);
    d->view->setItemDelegate(new HConfigWidgetDelegate(this));
    auto policy = d->view->sizePolicy();
    policy.setHorizontalStretch(1);
    d->view->setSizePolicy(policy);
    policy = d->stack->sizePolicy();
    policy.setHorizontalStretch(5);
    d->stack->setSizePolicy(policy);
    policy = d->title->sizePolicy();
    policy.setHorizontalStretch(5);
    d->title->setSizePolicy(policy);
    policy = line->sizePolicy();
    policy.setHorizontalStretch(5);
    line->setSizePolicy(policy);
    auto l = new QGridLayout(this);
    l->addWidget(d->view, 0, 0, 3, 1);
    l->addWidget(d->title, 0, 1);
    l->addWidget(line, 1, 1);
    l->addWidget(d->stack, 2, 1);
    connect(d->view, &QListWidget::currentRowChanged, this, &HConfigWidget::setCurrentIndex);
}

HE_CONTROL_END_NAMESPACE

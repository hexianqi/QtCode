#include "HConfigPanel_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

HConfigPanelDelegate::HConfigPanelDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void HConfigPanelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    auto size = option.decorationSize;
    auto rect = QRect(option.rect.x() + 4, option.rect.top() + 4, option.rect.width() - 8, size.height());
    auto mode = option.state & QStyle::State_Enabled ? ((option.state & QStyle::State_Selected) && option.showDecorationSelected ? QIcon::Selected : QIcon::Normal) : QIcon::Disabled;
    auto icon = index.data(Qt::DecorationRole).value<QIcon>();
    icon.paint(painter, rect, Qt::AlignCenter, mode);

    auto text = index.data(Qt::DisplayRole).toString();
    auto rect2 = option.rect.adjusted(4, size.height() + 8, -4, -4);
    painter->setPen(option.palette.color(option.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text));
    painter->drawText(rect2, Qt::AlignCenter | Qt::TextWordWrap, option.fontMetrics.elidedText(text, option.textElideMode, rect2.width()));
}

QSize HConfigPanelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto size = option.decorationSize;
    auto width = option.fontMetrics.width(index.data(Qt::DisplayRole).toString());
    return QSize(qBound(size.width(), width, option.rect.width()), size.height() + option.fontMetrics.height() + 12);
}

HConfigPanel::HConfigPanel(QWidget *parent) :
    HAbstractMultiPanel(*new HConfigPanelPrivate, parent)
{
    init();
}

HConfigPanel::HConfigPanel(HConfigPanelPrivate &p, QWidget *parent) :
     HAbstractMultiPanel(p, parent)
{
    init();
}

HConfigPanel::~HConfigPanel()
{
}

int HConfigPanel::count() const
{
    Q_D(const HConfigPanel);
    return d->stack->count();
}

int HConfigPanel::indexOf(QWidget *p) const
{
    Q_D(const HConfigPanel);
    return d->stack->indexOf(p);
}

QWidget *HConfigPanel::widget(int index) const
{
    Q_D(const HConfigPanel);
    return d->stack->widget(index);
}

QWidget *HConfigPanel::currentWidget() const
{
    Q_D(const HConfigPanel);
    return d->stack->currentWidget();
}

QSize HConfigPanel::iconSize() const
{
    Q_D(const HConfigPanel);
    return d->view->iconSize();
}

void HConfigPanel::insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    Q_D(HConfigPanel);
    HAbstractMultiPanel::insertWidget(index, widget, icon, label);

    d->stack->insertWidget(index, widget);
    d->view->insertItem(index, new QListWidgetItem(widget->windowIcon(), widget->windowTitle()));
    if (count() == 1)
        setCurrentIndex(0);
}

bool HConfigPanel::removeWidget(int index)
{
    Q_D(HConfigPanel);
    if (!HAbstractMultiPanel::removeWidget(index))
        return false;

    auto w = widget(index);
    d->stack->removeWidget(w);

    delete w;
    delete d->view->takeItem(index);

    d->currentIndex = d->stack->currentIndex();
    if (d->currentIndex > -1)
        d->title->setText(d->view->item(d->currentIndex)->text());
    else
        d->title->setText("");
    return true;
}

bool HConfigPanel::setCurrentIndex(int value)
{
    Q_D(HConfigPanel);
    if (!HAbstractMultiPanel::setCurrentIndex(value))
        return false;
    d->stack->setCurrentIndex(value);
    d->view->setCurrentRow(value);
    d->title->setText(d->view->item(value)->text());
    return true;
}

bool HConfigPanel::setWidgetIcon(int index, const QIcon &icon)
{
    Q_D(HConfigPanel);
    if (!HAbstractMultiPanel::setWidgetIcon(index, icon))
        return false;
    d->view->item(index)->setIcon(icon);
    return true;
}

bool HConfigPanel::setWidgetTitle(int index, const QString &title)
{
    Q_D(HConfigPanel);
    if (!HAbstractMultiPanel::setWidgetTitle(index, title))
        return false;
    d->view->item(index)->setText(title);
    if (index == currentIndex())
        d->title->setText(title);
    return true;
}

void HConfigPanel::setIconSize(const QSize &value)
{
    Q_D(HConfigPanel);
    d->view->setIconSize(value);
}

void HConfigPanel::save()
{
    Q_D(HConfigPanel);
    if (d->saving)
        return;
    d->saving = true;
    emit saving();
    d->saving = false;
}

void HConfigPanel::apply()
{
    Q_D(HConfigPanel);
    if (d->applying)
        return;
    d->applying = true;
    emit applying(currentIndex());
    QMetaObject::invokeMethod(currentWidget(), "apply");
    d->applying = false;
}

void HConfigPanel::discard()
{
    Q_D(HConfigPanel);
    if (d->discarding)
        return;
    d->discarding = true;
    emit discarding(currentIndex());
    QMetaObject::invokeMethod(currentWidget(), "discard");
    d->discarding = false;
}

void HConfigPanel::init()
{
    Q_D(HConfigPanel);
    d->title = new QLabel;
    auto font = d->title->font();
    font.setBold(true);
    d->title->setFont(font);
    auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    d->stack = new QStackedWidget;
    d->view = new QListWidget;
    d->view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->view->setIconSize(QSize(48, 48));
    d->view->setMaximumWidth(150);
    d->view->setItemDelegate(new HConfigPanelDelegate(this));
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
    auto layout = new QGridLayout(this);
    layout->addWidget(d->view, 0, 0, 3, 1);
    layout->addWidget(d->title, 0, 1);
    layout->addWidget(line, 1, 1);
    layout->addWidget(d->stack, 2, 1);
    connect(d->view, &QListWidget::currentRowChanged, this, &HConfigPanel::setCurrentIndex);
}

HE_CONTROL_END_NAMESPACE

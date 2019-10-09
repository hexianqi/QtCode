#include "HNavTreeView_p.h"
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtGui/QPainter>
#include <QtGui/QStandardItemModel>

HE_CONTROL_BEGIN_NAMESPACE

HNavTreeDelegate::HNavTreeDelegate(QObject *parent)
{
    _view = qobject_cast<HNavTreeView *>(parent);
    _model = static_cast<QStandardItemModel *>(_view->model());
    auto fontId = QFontDatabase::addApplicationFont(":/image/fonts/pe-icon-set-weather.ttf");
    auto fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    _iconFont = QFont(fontName);
}

HNavTreeDelegate::~HNavTreeDelegate()
{

}

QSize HNavTreeDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(50, 30);
}

void HNavTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    drawBackground(painter, option);
    drawIcon(painter, option, index);
    drawText(painter, option, index);
    drawTip(painter, option, index);
    painter->restore();

}

void HNavTreeDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option) const
{
    QColor color;
    if (option.state & QStyle::State_Selected)
        color = _view->selectedBackground();
    else if (option.state & QStyle::State_MouseOver)
        color = _view->hoverBackground();
    else
        color = _view->normalBackground();
    painter->fillRect(option.rect, color);
}

void HNavTreeDelegate::drawIcon(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor color;
    auto font = _iconFont;
    auto rect = option.rect;
    if (option.state & QStyle::State_Selected)
        color = _view->selectedTextColor();
    else if (option.state & QStyle::State_MouseOver)
        color = _view->hoverTextColor();
    else
        color = _view->normalTextColor();

    rect.setLeft(10);
    painter->save();
    painter->setFont(font);
    painter->setPen(color);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, _view->isExpanded(index) ? QChar(0xf067) : QChar(0xf068));
    painter->restore();
}

void HNavTreeDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto text = index.data(Qt::DisplayRole).toString();
    if (text.isEmpty())
        return;

    QColor color;
    if (option.state & QStyle::State_Selected)
        color = _view->selectedTextColor();
    else if (option.state & QStyle::State_MouseOver)
        color = _view->hoverTextColor();
    else
        color = _view->normalTextColor();

    auto rect = option.rect.adjusted(25, 0, 0, 0);
    painter->setPen(color);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, text);
}

void HNavTreeDelegate::drawTip(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto tip = _view->info(index);
    if (tip.isEmpty())
        return;

    if (tip.toInt() > 0)
        tip = tip.toInt() > 999 ? "999+" : tip;
    else if (tip.length() > 2)
        tip = tip.left(2) + " .";

    auto color1 = option.state & QStyle::State_Selected ? _view->selectedBackground() : _view->selectedTextColor();
    auto color2 = option.state & QStyle::State_Selected ? _view->selectedTextColor() : _view->selectedBackground();

    auto radius = option.rect.height() / 4.0;
    auto rect = QRectF(option.rect.right() - 45, option.rect.top() + radius, 40, radius * 2);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color1);
    painter->drawRoundedRect(rect, radius, radius);
    painter->setPen(color2);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(rect, Qt::AlignCenter, tip);
}

HNavTreeView::HNavTreeView(QWidget *parent) :
    QTreeView(parent),
    d_ptr(new HNavTreeViewPrivate)
{
    init();
}

HNavTreeView::HNavTreeView(HNavTreeViewPrivate &p, QWidget *parent) :
    QTreeView(parent),
    d_ptr(&p)
{
    init();
}

HNavTreeView::~HNavTreeView()
{
}

QString HNavTreeView::info(const QModelIndex &index)
{
    auto text = d_ptr->model->itemFromIndex(index)->data(Qt::DisplayRole).toString();

    if (d_ptr->infos.contains(text))
        return d_ptr->infos.value(text);
    return QString();
}

QColor HNavTreeView::lineColor() const
{
    return d_ptr->lineColor;
}

QColor HNavTreeView::normalBackground() const
{
    return d_ptr->normalBackground;
}

QColor HNavTreeView::hoverBackground() const
{
    return d_ptr->hoverBackground;
}

QColor HNavTreeView::selectedBackground() const
{
    return d_ptr->selectedBackground;
}

QColor HNavTreeView::normalTextColor() const
{
    return d_ptr->normalTextColor;
}

QColor HNavTreeView::hoverTextColor() const
{
    return d_ptr->hoverTextColor;
}

QColor HNavTreeView::selectedTextColor() const
{
    return d_ptr->selectedTextColor;
}

void HNavTreeView::addItem(const QString &text, QStandardItem *parent)
{
    if (parent == nullptr)
        d_ptr->model->appendRow(new QStandardItem(text));
    else
        parent->appendRow(new QStandardItem(text));
}

void HNavTreeView::addItem(const QString &text, const QString &parentText)
{
    auto list = d_ptr->model->findItems(parentText, Qt::MatchRecursive);
    for (auto item : list)
        addItem(text, item);
}

void HNavTreeView::setItemInfo(const QString &itemText, const QString &info)
{
    d_ptr->infos.insert(itemText, info);
}

void HNavTreeView::setLineColor(const QColor &value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
}

void HNavTreeView::setNormalBackground(const QColor &value)
{
    if (d_ptr->normalBackground == value)
        return;
    d_ptr->normalBackground = value;
}

void HNavTreeView::setHoverBackground(const QColor &value)
{
    if (d_ptr->hoverBackground == value)
        return;
    d_ptr->hoverBackground = value;
}

void HNavTreeView::setSelectedBackground(const QColor &value)
{
    if (d_ptr->selectedBackground == value)
        return;
    d_ptr->selectedBackground = value;
}

void HNavTreeView::setNormalTextColor(const QColor &value)
{
    if (d_ptr->normalTextColor == value)
        return;
    d_ptr->normalTextColor = value;
}

void HNavTreeView::setHoverTextColor(const QColor &value)
{
    if (d_ptr->hoverTextColor == value)
        return;
    d_ptr->hoverTextColor = value;
}

void HNavTreeView::setSelectedTextColor(const QColor &value)
{
    if (d_ptr->selectedTextColor == value)
        return;
    d_ptr->selectedTextColor = value;
}

void HNavTreeView::init()
{
    d_ptr->model = new QStandardItemModel(this);
    setModel(d_ptr->model);
    setHeaderHidden(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setStyleSheet("QTreeView::branch {image:none;}");
    setItemDelegate(new HNavTreeDelegate(this));
}

HE_CONTROL_END_NAMESPACE

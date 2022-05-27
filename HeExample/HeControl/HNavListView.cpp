#include "HNavListView_p.h"
#include "HIconFontFactory.h"
#include <QtCore/QFile>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtXml/QDomDocument>

HE_BEGIN_NAMESPACE

HNavListModel::HNavListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

HNavListModel::~HNavListModel()
{
    for (auto it = _treeNodes.begin(); it != _treeNodes.end(); )
    {
        for (auto child = (*it)->childs.begin(); child != (*it)->childs.end();)
        {
            delete(*child);
            child = (*it)->childs.erase(child);
        }

        delete(*it);
        it = _treeNodes.erase(it);
    }
}

void HNavListModel::readData(const QString &fileName)
{
    QFile xml(fileName);
    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QDomDocument doc;
    if (!doc.setContent(&xml, false))
        return;

    _treeNodes.clear();
    auto childs = doc.documentElement().firstChildElement("layout").childNodes();
    for (int i = 0; i != childs.count(); i++)
    {
        auto node = new HTreeNode;
        auto element = childs.at(i).toElement();
        auto text = element.attribute("text");
        auto icon = element.attribute("icon");

        node->level = 1;
        node->expand = element.attribute("expand").toInt();
        node->text = text;
        node->tip = element.attribute("tip");
        if (!icon.isEmpty())
            node->icon = icon.at(0);

        auto childs2 = element.childNodes();
        for (int j = 0; j != childs2.count(); j++)
        {
            auto node2 = new HTreeNode;
            auto element2 = childs2.at(j).toElement();
            auto icon2 = element2.attribute("icon");
            node2->level = 2;
            node2->expand = true;
            node2->parentText = text;
            node2->text = element2.attribute("text");
            node2->tip = element2.attribute("tip");
            node2->last = (j == childs2.count() - 1 && i != childs.count() - 1);
            if (!icon2.isEmpty())
                node2->icon = icon2.at(0);
            node->childs.push_back(node2);
        }
        _treeNodes.push_back(node);
    }

    refreshList();
    beginResetModel();
    endResetModel();
}

// datas format: parentText | isCollapse | icon | text | tip
void HNavListModel::setItem(const QStringList &value)
{
    auto count = value.count();
    if (count == 0)
        return;

    _treeNodes.clear();
    for (int i = 0; i < count; ++i)
    {
        auto item = value.at(i);
        auto list = item.split("|");
        if (list.count() < 5 || !list.at(0).isEmpty())
            continue;

        auto node = new HTreeNode;
        auto icon = list.at(2);
        auto text = list.at(3);

        node->level = 1;
        node->expand = list.at(1).toInt();
        node->text = text;
        node->tip = list.at(4);
        if (!icon.isEmpty())
            node->icon = icon.at(0);

        for (int j = 0; j < count; j++)
        {
            auto item2 = value.at(j);
            auto list2 = item2.split("|");
            if (list2.count() < 5 || list2.at(0) != text)
                continue;

            auto node2 = new HTreeNode;
            auto icon2 = list2.at(2);
            node2->level = 2;
            node2->expand = true;
            node2->parentText = text;
            node2->text = list.at(3);
            node2->tip = list.at(4);
            node2->last = (j == count - 1);
            if (!icon2.isEmpty())
                node2->icon = icon2.at(0);
            node->childs.push_back(node2);
        }
        _treeNodes.push_back(node);
    }

    refreshList();
    beginResetModel();
    endResetModel();
}

void HNavListModel::expand(const QModelIndex &index)
{
    auto node = _listNodes[index.row()]->node;
    auto count = node->childs.size();
    if (count == 0)
        return;

    node->expand = !node->expand;
    if (node->expand)
    {
        beginInsertRows(QModelIndex(), index.row() + 1, index.row() + count);
        endInsertRows();
    }
    else
    {
        beginRemoveRows(QModelIndex(), index.row() + 1, index.row() + count);
        endRemoveRows();
    }
    refreshList();
}

int HNavListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _listNodes.size();
}

QVariant HNavListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto row = index.row();
    if (row >= _listNodes.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole)
        return _listNodes[row]->text;
    if (role == Qt::UserRole)
        return QVariant::fromValue(_listNodes.at(row)->node);
    return QVariant();
}

void HNavListModel::refreshList()
{
    _listNodes.clear();
    for (auto treeNode : _treeNodes)
    {
        auto listNode = new HListNode;
        listNode->text = treeNode->text;
        listNode->node = treeNode;
        _listNodes.push_back(listNode);
        if (!treeNode->expand)
            continue;

        for (auto child : treeNode->childs)
        {
            child->last = false;
            auto listNode2 = new HListNode;
            listNode2->text = child->text;
            listNode2->node = child;
            _listNodes.push_back(listNode2);
        }
        if (!_listNodes.empty())
            _listNodes.last()->node->last = true;
    }
}

HNavListDelegate::HNavListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    auto factory = new HIconFontFactory(this);
    _iconFont = factory->createFont("FontWeather");
    _view = qobject_cast<HNavListView *>(parent);
}

QSize HNavListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    auto node = index.data(Qt::UserRole).value<HNavListModel::HTreeNode *>();
    if (node->level == 1)
        return {50, 35};
    return {50, 28};
}

void HNavListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto node = index.data(Qt::UserRole).value<HNavListModel::HTreeNode *>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    // 绘制背景
    drawBackground(painter, option, node);
    // 绘制线条,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    drawLine(painter, option, node);
    // 绘制三角形,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    drawTriangle(painter, option, node);
    // 绘制行分隔符
    drawSeparate(painter, option, node);
    // 绘制文本
    drawText(painter, option, node);
    // 绘制提示信息
    drawTip(painter, option, node);
    // 绘制图标
    drawIcon(painter, option, node);
    painter->restore();
}

void HNavListDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    QColor color;
    auto parent = node->level == 1;
    if (option.state & QStyle::State_Selected)
        color = parent ? _view->parentSelectedColor() : _view->childSelectedColor();
    else if (option.state & QStyle::State_MouseOver)
        color = parent ? _view->parentHoverColor() : _view->childHoverColor();
    else
        color = parent ? _view->parentNormalColor() : _view->childNormalColor();
    painter->fillRect(option.rect, color);
}

void HNavListDelegate::drawLine(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    auto width = _view->lineWidth();
    if (node->level == 1 || !_view->isLineVisible() || width <= 0)
        return;
    if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver))
    {
        // 设置偏移量,不然上下部分会有点偏移
        auto offset = width / 2.0;
        auto rect = option.rect;
        auto top = QPointF(_view->isLineLeft() ? rect.left() : rect.right(), rect.top() + offset);
        auto bottom = QPointF(_view->isLineLeft() ? rect.left() : rect.right(), rect.bottom() - offset);
        painter->setPen(QPen(_view->lineColor(), width));
        painter->drawLine(top, bottom);
    }
}

void HNavListDelegate::drawTriangle(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    int width = _view->triangleWidth();
    if (node->level == 1 || !_view->isTriangleVisible() || width <= 0)
        return;
    if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver))
    {
        auto font = _iconFont;
        font.setPixelSize(_view->parentFontSize() + width);
        painter->setFont(font);
        painter->setPen(_view->triangleColor());
        if (_view->isTriangleLeft())
            painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
        else
            painter->drawText(option.rect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
    }
}

void HNavListDelegate::drawSeparate(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    if (!_view->isSeparateVisible())
        return;
    if (node->level == 1 || (node->level == 2 && node->last))
    {
        painter->setPen(QPen(_view->separateColor(), _view->separateHeight()));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }
}

void HNavListDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    auto text = node->text;
    if (text.isEmpty())
        return;

    QColor color;
    auto parent = node->level == 1;
    if (option.state & QStyle::State_Selected)
        color = parent ? _view->parentTextSelectedColor() : _view->childTextSelectedColor();
    else if (option.state & QStyle::State_MouseOver)
        color = parent ? _view->parentTextHoverColor() : _view->childTextHoverColor();
    else
        color = parent ? _view->parentTextNormalColor() : _view->childTextNormalColor();
    auto margin = parent ? _view->parentMargin() : _view->childMargin();
    auto fontSize = parent ? _view->parentFontSize() : _view->childFontSize();
    auto rect = option.rect.adjusted(margin, 0, 0, 0);
    auto font = painter->font();
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(color);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, text);
}

void HNavListDelegate::drawTip(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    auto tip = node->tip;
    if (!_view->isTipVisible() || tip.isEmpty())
        return;

    QColor color1, color2;
    if (tip.toInt() > 0)
        tip = tip.toInt() > 999 ? "999+" : tip;
    else if (tip.length() > 2)
        tip = tip.left(2) + " .";
    auto parent = node->level == 1;
    if (option.state & QStyle::State_Selected)
    {
        color1 = parent ? _view->parentTextSelectedColor() : _view->childTextSelectedColor();
        color2 = parent ? _view->parentSelectedColor() : _view->childSelectedColor();
    }
    else if (option.state & QStyle::State_MouseOver)
    {
        color1 = parent ? _view->parentTextSelectedColor() : _view->childTextSelectedColor();
        color2 = parent ? _view->parentSelectedColor() : _view->childSelectedColor();
    }
    else
    {
        color1 = parent ? _view->parentSelectedColor() : _view->childSelectedColor();
        color2 = parent ? _view->parentTextSelectedColor() : _view->childTextSelectedColor();
    }
    auto radius = option.rect.height() / 4.0;
    auto rect = QRectF(option.rect.right() - _view->tipWidth() - 5, option.rect.top() + radius, _view->tipWidth(), radius * 2);
    auto fontSize = parent ? _view->parentFontSize() : _view->childFontSize();
    auto font = painter->font();
    font.setPixelSize(fontSize - 2);
    painter->setFont(font);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color1);
    painter->drawRoundedRect(rect, radius, radius);
    painter->setPen(color2);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(rect, Qt::AlignCenter, tip);
}

void HNavListDelegate::drawIcon(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const
{
    QColor color;
    auto parent = node->level == 1;
    auto font = _iconFont;
    auto rect = option.rect;
    if (option.state & QStyle::State_Selected)
        color = parent ? _view->parentTextSelectedColor() : _view->childTextSelectedColor();
    else if (option.state & QStyle::State_MouseOver)
        color = parent ? _view->parentTextHoverColor() : _view->childTextHoverColor();
    else
        color = parent ? _view->parentTextNormalColor() : _view->childTextNormalColor();

    rect.setLeft(parent ? _view->parentIconMargin() : _view->childIconMargin());
    font.setPixelSize(parent ? _view->parentFontSize() : _view->childFontSize());
    painter->setFont(font);
    painter->setPen(color);

    // 绘制左侧图标
    if (!node->icon.isNull())
        painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, node->icon);
    else if (parent)
        painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, node->expand ? QChar(0xf067) : QChar(0xf068));

    // 绘制父节点右侧图标
    rect.setRight(option.rect.width() - 10);
    if (!(_view->isTipVisible() && !node->tip.isEmpty()) && _view->isRightIconVisible() && parent)
        painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, node->expand ? QChar(0xf054) : QChar(0xf078));
}

HNavListView::HNavListView(QWidget *parent) :
    QListView(parent),
    d_ptr(new HNavListViewPrivate)
{
    init();
}

HNavListView::HNavListView(HNavListViewPrivate &p, QWidget *parent) :
    QListView(parent),
    d_ptr(&p)
{
    init();
}

HNavListView::~HNavListView() = default;

QSize HNavListView::sizeHint() const
{
    return {200, 400};
}

QSize HNavListView::minimumSizeHint() const
{
    return {50, 50};
}

QString HNavListView::items() const
{
    return d_ptr->items;
}

bool HNavListView::isRightIconVisible() const
{
    return d_ptr->rightIconVisible;
}

bool HNavListView::isTipVisible() const
{
    return d_ptr->tipVisible;
}

int HNavListView::tipWidth() const
{
    return d_ptr->tipWidth;
}

bool HNavListView::isSeparateVisible() const
{
    return d_ptr->separateVisible;
}

int HNavListView::separateHeight() const
{
    return d_ptr->separateHeight;
}

QColor HNavListView::separateColor() const
{
    return d_ptr->separateColor;
}

bool HNavListView::isLineVisible() const
{
    return d_ptr->lineVisible;
}

bool HNavListView::isLineLeft() const
{
    return d_ptr->lineLeft;
}

int HNavListView::lineWidth() const
{
    return d_ptr->lineWidth;
}

QColor HNavListView::lineColor() const
{
    return d_ptr->lineColor;
}

bool HNavListView::isTriangleVisible() const
{
    return d_ptr->triangleVisible;
}

bool HNavListView::isTriangleLeft() const
{
    return d_ptr->triangleLeft;
}

int HNavListView::triangleWidth() const
{
    return d_ptr->triangleWidth;
}

QColor HNavListView::triangleColor() const
{
    return d_ptr->triangleColor;
}

int HNavListView::parentMargin() const
{
    return d_ptr->parentMargin;
}

int HNavListView::parentIconMargin() const
{
    return d_ptr->parentIconMargin;
}

int HNavListView::parentFontSize() const
{
    return d_ptr->parentFontSize;
}

int HNavListView::parentHeight() const
{
    return d_ptr->parentHeight;
}

QColor HNavListView::parentNormalColor() const
{
    return d_ptr->parentNormalColor;
}

QColor HNavListView::parentSelectedColor() const
{
    return d_ptr->parentSelectedColor;
}

QColor HNavListView::parentHoverColor() const
{
    return d_ptr->parentHoverColor;
}

QColor HNavListView::parentTextNormalColor() const
{
    return d_ptr->parentTextNormalColor;
}

QColor HNavListView::parentTextSelectedColor() const
{
    return d_ptr->parentTextSelectedColor;
}

QColor HNavListView::parentTextHoverColor() const
{
    return d_ptr->parentTextHoverColor;
}

int HNavListView::childMargin() const
{
    return d_ptr->childMargin;
}

int HNavListView::childIconMargin() const
{
    return d_ptr->childIconMargin;
}

int HNavListView::childFontSize() const
{
    return d_ptr->childFontSize;
}

int HNavListView::childHeight() const
{
    return d_ptr->childHeight;
}

QColor HNavListView::childNormalColor() const
{
    return d_ptr->childNormalColor;
}

QColor HNavListView::childSelectedColor() const
{
    return d_ptr->childSelectedColor;
}

QColor HNavListView::childHoverColor() const
{
    return d_ptr->childHoverColor;
}

QColor HNavListView::childTextNormalColor() const
{
    return d_ptr->childTextNormalColor;
}

QColor HNavListView::childTextSelectedColor() const
{
    return d_ptr->childTextSelectedColor;
}

QColor HNavListView::childTextHoverColor() const
{
    return d_ptr->childTextHoverColor;
}

HNavListView::ExpendMode HNavListView::expendMode() const
{
    return d_ptr->expendMode;
}

void HNavListView::readData(const QString &fileName)
{
    d_ptr->model->readData(fileName);
}

void HNavListView::setCurrentRow(int value)
{
    setCurrentIndex(d_ptr->model->index(value, 0));
}

void HNavListView::setItems(const QString &value)
{
    d_ptr->items = value;
    d_ptr->model->setItem(value.split(";"));
}

void HNavListView::setRightIconVisible(bool b)
{
    if (d_ptr->rightIconVisible == b)
        return;
    d_ptr->rightIconVisible = b;
}

void HNavListView::setTipVisible(bool b)
{
    if (d_ptr->tipVisible == b)
        return;
    d_ptr->tipVisible = b;
}

void HNavListView::setTipWidth(int value)
{
    if (d_ptr->tipWidth == value)
        return;
    d_ptr->tipWidth = value;
}

void HNavListView::setSeparateVisible(bool b)
{
    if (d_ptr->separateVisible == b)
        return;
    d_ptr->separateVisible = b;
}

void HNavListView::setSeparateHeight(int value)
{
    if (d_ptr->separateHeight == value)
        return;
    d_ptr->separateHeight = value;
}

void HNavListView::setSeparateColor(const QColor &value)
{
    if (d_ptr->separateColor == value)
        return;
    d_ptr->separateColor = value;
}

void HNavListView::setLineVisible(bool b)
{
    if (d_ptr->lineVisible == b)
        return;
    d_ptr->lineVisible = b;
}

void HNavListView::setLineLeft(bool b)
{
    if (d_ptr->lineLeft == b)
        return;
    d_ptr->lineLeft = b;
}

void HNavListView::setLineWidth(int value)
{
    if (d_ptr->lineWidth == value)
        return;
    d_ptr->lineWidth = value;
}

void HNavListView::setLineColor(const QColor &value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
}

void HNavListView::setTriangleLeft(bool b)
{
    if (d_ptr->triangleLeft == b)
        return;
    d_ptr->triangleLeft = b;
}

void HNavListView::setTriangleVisible(bool b)
{
    if (d_ptr->triangleVisible == b)
        return;
    d_ptr->triangleVisible = b;
}

void HNavListView::setTriangleWidth(int value)
{
    if (d_ptr->triangleWidth == value)
        return;
    d_ptr->triangleWidth = value;
}

void HNavListView::setTriangleColor(const QColor &value)
{
    if (d_ptr->triangleColor == value)
        return;
    d_ptr->triangleColor = value;
}

void HNavListView::setParentMargin(int value)
{
    if (d_ptr->parentMargin == value)
        return;
    d_ptr->parentMargin = value;
}

void HNavListView::setParentIconMargin(int value)
{
    if (d_ptr->parentIconMargin == value)
        return;
    d_ptr->parentIconMargin = value;
}

void HNavListView::setParentFontSize(int value)
{
    if (d_ptr->parentFontSize == value)
        return;
    d_ptr->parentFontSize = value;
}

void HNavListView::setParentHeight(int value)
{
    if (d_ptr->parentHeight == value)
        return;
    d_ptr->parentHeight = value;
}

void HNavListView::setParentNormalColor(const QColor &value)
{
    if (d_ptr->parentNormalColor == value)
        return;
    d_ptr->parentNormalColor = value;
}

void HNavListView::setParentSelectedColor(const QColor &value)
{
    if (d_ptr->parentSelectedColor == value)
        return;
    d_ptr->parentSelectedColor = value;
}

void HNavListView::setParentHoverColor(const QColor &value)
{
    if (d_ptr->parentHoverColor == value)
        return;
    d_ptr->parentHoverColor = value;
}

void HNavListView::setParentTextNormalColor(const QColor &value)
{
    if (d_ptr->parentTextNormalColor == value)
        return;
    d_ptr->parentTextNormalColor = value;
}

void HNavListView::setParentTextSelectedColor(const QColor &value)
{
    if (d_ptr->parentTextSelectedColor == value)
        return;
    d_ptr->parentTextSelectedColor = value;
}

void HNavListView::setParentTextHoverColor(const QColor &value)
{
    if (d_ptr->parentTextHoverColor == value)
        return;
    d_ptr->parentTextHoverColor = value;
}

void HNavListView::setChildMargin(int value)
{
    if (d_ptr->rightIconVisible == value)
        return;
    d_ptr->rightIconVisible = value;
}

void HNavListView::setChildIconMargin(int value)
{
    if (d_ptr->rightIconVisible == value)
        return;
    d_ptr->rightIconVisible = value;
}

void HNavListView::setChildFontSize(int value)
{
    if (d_ptr->rightIconVisible == value)
        return;
    d_ptr->rightIconVisible = value;
}

void HNavListView::setChildHeight(int value)
{
    if (d_ptr->rightIconVisible == value)
        return;
    d_ptr->rightIconVisible = value;
}

void HNavListView::setChildNormalColor(const QColor &value)
{
    if (d_ptr->childNormalColor == value)
        return;
    d_ptr->childNormalColor = value;
}

void HNavListView::setChildSelectedColor(const QColor &value)
{
    if (d_ptr->childSelectedColor == value)
        return;
    d_ptr->childSelectedColor = value;
}

void HNavListView::setChildHoverColor(const QColor &value)
{
    if (d_ptr->childHoverColor == value)
        return;
    d_ptr->childHoverColor = value;
}

void HNavListView::setChildTextNormalColor(const QColor &value)
{
    if (d_ptr->childTextNormalColor == value)
        return;
    d_ptr->childTextNormalColor = value;
}

void HNavListView::setChildTextSelectedColor(const QColor &value)
{
    if (d_ptr->childTextSelectedColor == value)
        return;
    d_ptr->childTextSelectedColor = value;
}

void HNavListView::setChildTextHoverColor(const QColor &value)
{
    if (d_ptr->childTextHoverColor == value)
        return;
    d_ptr->childTextHoverColor = value;
}

void HNavListView::setExpendMode(ExpendMode value)
{
    if (d_ptr->expendMode == value)
        return;
    if (d_ptr->expendMode == ExpendMode_SingleClick)
        disconnect(this, &HNavListView::clicked, this, &HNavListView::handleClicked);
    if (d_ptr->expendMode == ExpendMode_DoubleClick)
        disconnect(this, &HNavListView::doubleClicked, this, &HNavListView::handleClicked);
    d_ptr->expendMode = value;
    if (value == ExpendMode_SingleClick)
        connect(this, &HNavListView::clicked, this, &HNavListView::handleClicked);
    if (value == ExpendMode_DoubleClick)
        connect(this, &HNavListView::doubleClicked, this, &HNavListView::handleClicked);
}

void HNavListView::init()
{
    d_ptr->model = new HNavListModel(this);
    d_ptr->delegate = new HNavListDelegate(this);
    setModel(d_ptr->model);
    setItemDelegate(d_ptr->delegate);
    setMouseTracking(true);
    connect(this, &HNavListView::clicked, this, &HNavListView::handleClicked);
}

void HNavListView::handleClicked(const QModelIndex &index)
{;
    d_ptr->model->expand(index);
    auto node = index.data(Qt::UserRole).value<HNavListModel::HTreeNode *>();
    emit pressed(node->text, node->parentText);
}

HE_END_NAMESPACE

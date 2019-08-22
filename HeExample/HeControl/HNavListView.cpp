#include "HNavListView_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HNavDelegate::HNavDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

HNavListView::HNavListView(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HNavListViewPrivate)
{
}

HNavListView::HNavListView(HNavListViewPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HNavListView::~HNavListView()
{
}

//void NavDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    painter->setRenderHint(QPainter::Antialiasing);
//    NavModel::TreeNode *node = (NavModel::TreeNode *)index.data(Qt::UserRole).toULongLong();

//    //定义变量存储区域
//    QRect optionRect = option.rect;
//    int x = optionRect.x();
//    int y = optionRect.y();
//    int width = optionRect.width();
//    int height = optionRect.height();

//    int fontSize = nav->getParentFontSize();

//    //父节点和子节点颜色分开设置
//    bool parent = (node->level == 1);

//    //根据不同的状态设置不同的颜色 bgColor-主背景色 textColor-主文字颜色 tipBgColor-提示信息背景颜色 tipTextColor-提示信息文字颜色
//    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
//    if (option.state & QStyle::State_Selected) {
//        bgColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
//        textColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
//        tipBgColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
//        tipTextColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
//        iconColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
//    } else if (option.state & QStyle::State_MouseOver) {
//        bgColor = parent ? nav->getParentBgHoverColor() : nav->getChildBgHoverColor();
//        textColor = parent ? nav->getParentTextHoverColor() : nav->getChildTextHoverColor();
//        tipBgColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
//        tipTextColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
//        iconColor = parent ? nav->getParentTextHoverColor() : nav->getChildTextHoverColor();
//    } else {
//        bgColor = parent ? nav->getParentBgNormalColor() : nav->getChildBgNormalColor();
//        textColor = parent ? nav->getParentTextNormalColor() : nav->getChildTextNormalColor();
//        tipBgColor = parent ? nav->getParentBgSelectedColor() : nav->getChildBgSelectedColor();
//        tipTextColor = parent ? nav->getParentTextSelectedColor() : nav->getChildTextSelectedColor();
//        iconColor = parent ? nav->getParentTextNormalColor() : nav->getChildTextNormalColor();
//    }

//    //绘制背景
//    painter->fillRect(optionRect, bgColor);

//    //绘制线条,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
//    int lineWidth = nav->getLineWidth();
//    if (!parent && nav->getLineVisible() && lineWidth > 0) {
//        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver)) {
//            //设置偏移量,不然上下部分会有点偏移
//            float offset = (float)lineWidth / 2;

//            //计算上下两个坐标点
//            QPointF pointTop(x, y + offset);
//            QPointF pointBottom(x, height + y - offset);
//            if (!nav->getLineLeft()) {
//                pointTop.setX(width);
//                pointBottom.setX(width);
//            }

//            //设置线条颜色和宽度
//            painter->setPen(QPen(nav->getLineColor(), lineWidth));
//            painter->drawLine(pointTop, pointBottom);
//        }
//    }

//    //绘制三角形,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
//    int triangleWidth = nav->getTriangleWidth();
//    if (!parent && nav->getTriangleVisible() && triangleWidth > 0) {
//        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver)) {
//            QFont font = iconFont;
//            font.setPixelSize(fontSize + triangleWidth);
//            painter->setFont(font);
//            painter->setPen(nav->getTriangleColor());

//            //采用图形字体中的三角形绘制
//            if (nav->getTriangleLeft()) {
//                painter->drawText(optionRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
//            } else {
//                painter->drawText(optionRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
//            }
//        }
//    }

//    //绘制行分隔符
//    if (nav->getSeparateVisible()) {
//        if (node->level == 1 || (node->level == 2 && node->last)) {
//            painter->setPen(QPen(nav->getSeparateColor(), nav->getSeparateHeight()));
//            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
//        }
//    }

//    //绘制文字,如果文字为空则不绘制
//    QString text = node->text;
//    if (!text.isEmpty()) {
//        //文字离左边的距离+字体大小
//        int margin = nav->getParentMargin();
//        if (node->level == 2) {
//            margin = nav->getChildMargin();
//            fontSize = nav->getChildFontSize();
//        }

//        //计算文字区域
//        QRect textRect = optionRect;
//        textRect.setWidth(width - margin);
//        textRect.setX(x + margin);

//        QFont font;
//        font.setPixelSize(fontSize);
//        painter->setFont(font);
//        painter->setPen(textColor);
//        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
//    }

//    //绘制提示信息,如果不需要显示提示信息或者提示信息为空则不绘制
//    QString tip = node->tip;
//    if (nav->getTipVisible() && !tip.isEmpty()) {
//        //如果是数字则将超过999的数字显示成 999+
//        //如果显示的提示信息长度过长则将多余显示成省略号 .
//        if (tip.toInt() > 0) {
//            tip = tip.toInt() > 999 ? "999+" : tip;
//        } else if (tip.length() > 2) {
//            tip = tip.left(2) + " .";
//        }

//        //计算绘制区域,半径取高度的四分之一
//        int radius = height / 4;
//        QRect tipRect = optionRect;
//        tipRect.setHeight(radius * 2);
//        tipRect.moveCenter(optionRect.center());
//        tipRect.setLeft(optionRect.right() - nav->getTipWidth() - 5);
//        tipRect.setRight(optionRect.right() - 5);

//        //设置字体大小
//        QFont font;
//        font.setPixelSize(fontSize - 2);
//        painter->setFont(font);

//        //绘制提示文字的背景
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(tipBgColor);
//        painter->drawRoundedRect(tipRect, radius, radius);

//        //绘制提示文字
//        painter->setPen(tipTextColor);
//        painter->setBrush(Qt::NoBrush);
//        painter->drawText(tipRect, Qt::AlignCenter, tip);
//    }

//    //计算绘制图标区域
//    QRect iconRect = optionRect;
//    iconRect.setLeft(parent ? nav->getParentIconMargin() : nav->getChildIconMargin());

//    //设置图形字体和画笔颜色
//    QFont font = iconFont;
//    font.setPixelSize(fontSize);
//    painter->setFont(font);
//    painter->setPen(textColor);

//    //绘制左侧图标,有图标则绘制图标,没有的话父窗体取 + -
//    if (!node->icon.isNull()) {
//        painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, node->icon);
//    } else if (parent) {
//        if (node->expand) {
//            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf067));
//        } else {
//            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf068));
//        }
//    }

//    //绘制父节点右侧图标
//    iconRect.setRight(optionRect.width() - 10);
//    if (!(nav->getTipVisible() && !node->tip.isEmpty()) && nav->getRightIconVisible() && parent) {
//        if (node->expand) {
//            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf054));
//        } else {
//            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf078));
//        }
//    }
//}

HE_CONTROL_END_NAMESPACE

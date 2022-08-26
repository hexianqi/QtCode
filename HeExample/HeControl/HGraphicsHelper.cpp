#include "HGraphicsHelper.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

QVariant HGraphicsHelper::fixByScene(QGraphicsItem *item, const QVariant &value)
{
    auto scene = item->scene();
    if (scene == nullptr)
        return {};

    auto pos = value.toPointF();
    auto sceneRect = scene->sceneRect();
    auto boundingRect = item->boundingRect();
    auto moveRect = QRectF(pos.x(), pos.y(), boundingRect.width(), boundingRect.height());

    // 左上角
    if (!sceneRect.contains(moveRect.topLeft()))
    {
        pos.setX(qBound(0.0, moveRect.left(), sceneRect.width()));
        pos.setY(qBound(0.0, moveRect.top(), sceneRect.height()));
        return pos;
    }
    // 右上角
    if (!sceneRect.contains(moveRect.topRight()))
    {
        pos.setX(sceneRect.width() - moveRect.width());
        item->setPos(pos);
        return pos;
    }
    // 左下角
    if (!sceneRect.contains(moveRect.bottomLeft()))
    {
        pos.setY(sceneRect.height() - moveRect.height());
        item->setPos(pos);
        return pos;
    }
    return {};
}

QVariant HGraphicsHelper::fixByOverlap(QGraphicsItem *item, const QVariant &value)
{
    auto scene = item->scene();
    auto collidItems = item->collidingItems();
    if (scene == nullptr || collidItems.isEmpty())
        return {};

    auto pos = value.toPointF();
    auto itemBoundingRect = item->boundingRect();
    auto moveRect = QRectF(pos.x(), pos.y(), itemBoundingRect.width(), itemBoundingRect.height());
    auto otherItem = collidItems.first();
    auto otherItemBoundingRect = otherItem->boundingRect();
    auto otherItemRect = QRectF(otherItem->x(), otherItem->y(), otherItemBoundingRect.width(), otherItemBoundingRect.height());

    // 左上角
    if (otherItemRect.contains(moveRect.topLeft()))
    {
        auto temp = otherItemRect.bottomRight() - moveRect.topLeft();
        if (fabs(temp.x()) > fabs(temp.y()))
            pos.setY(otherItem->y() + otherItemRect.height() + 2);
        else
            pos.setX(otherItem->x() + otherItemRect.width() + 2);
        item->setPos(pos);
        return pos;
    }
    // 右上角
    if (otherItemRect.contains(moveRect.topRight()))
    {
        auto temp = otherItemRect.bottomLeft() - moveRect.topRight();
        if (fabs(temp.x()) > fabs(temp.y()))
            pos.setY(otherItem->y() + otherItemRect.height() + 2);
        else
            pos.setX(otherItem->x() - moveRect.width() - 2);
        item->setPos(pos);
        return pos;
    }
    // 左下角
    if (otherItemRect.contains(moveRect.bottomLeft()))
    {
        auto temp = otherItemRect.topRight() - moveRect.bottomLeft();
        if (fabs(temp.x()) > fabs(temp.y()))
            pos.setY(otherItem->y() - moveRect.height() - 2);
        else
            pos.setX(otherItem->x() + otherItemRect.width() + 2);
        item->setPos(pos);
        return pos;
    }
    // 右下角
    if (otherItemRect.contains(moveRect.bottomRight()))
    {
        auto temp = otherItemRect.topLeft() - moveRect.bottomRight();
        if (fabs(temp.x()) > fabs(temp.y()))
            pos.setY(otherItem->y() - moveRect.height() - 2);
        else
            pos.setX(otherItem->x() - otherItemRect.width() - 2);
        item->setPos(pos);
        return pos;
    }
    return {};
}

HE_END_NAMESPACE

//QVariant pixmapItem::itemChange(GraphicsItemChange change, const QVariant &value)
//{
//    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene()) // 控件发生移动
//    {
//        QPointF newPos = value.toPointF();
//        QRectF rect(0, 0, scene()->width(), scene()->height());

//        QList<QGraphicsItem *> list = collidingItems();//碰撞列表
//        if(list.size() > 0)
//        {
//            QGraphicsItem * otherItem = list.first();
//            QRectF otherItemRect = otherItem->boundingRect();
//            QRectF otherRect = QRectF(otherItem->x(),otherItem->y(),otherItemRect.width(),otherItemRect.height());

//            if(otherRect.contains(newPos))//左上角
//            {
//                QPointF tempPoint = otherRect.bottomRight() - newPos;
//                if(abs(tempPoint.x()) > abs(tempPoint.y()))
//                {
//                    newPos.setY(otherItem->y() + otherRect.height() + 2);
//                }
//                else
//                {
//                    newPos.setX(otherItem->x() + otherRect.width() + 2);
//                }
//                this->setPos(newPos);
//                return newPos;
//            }

//            QRectF thisRectF = boundingRect();
//            QPointF nowPos = QPointF(newPos.x() + thisRectF.width(),newPos.y());
//            if(otherRect.contains(nowPos))//右上角
//            {
//                QPointF tempPoint = otherRect.bottomLeft() - nowPos;
//                if(abs(tempPoint.x()) > abs(tempPoint.y()))
//                {
//                    newPos.setY(otherItem->y() + otherRect.height() + 2);
//                }
//                else
//                {
//                    newPos.setX(otherItem->x() - thisRectF.width() - 2);
//                }
//                this->setPos(newPos);
//                return newPos;
//            }

//            nowPos = QPointF(newPos.x(),newPos.y() + thisRectF.height());
//            if(otherRect.contains(nowPos))//左下角
//            {
//                QPointF tempPoint = otherRect.topRight() - nowPos;
//                if(abs(tempPoint.x()) > abs(tempPoint.y()))
//                {
//                    newPos.setY(otherItem->y() - thisRectF.height() - 2);
//                }
//                else
//                {
//                    newPos.setX(otherItem->x() + otherRect.width() + 2);
//                }
//                this->setPos(newPos);
//                return newPos;
//            }

//            nowPos = QPointF(newPos.x() + thisRectF.width(),newPos.y() + thisRectF.height());
//            if(otherRect.contains(nowPos))//右下角
//            {
//                QPointF tempPoint = otherRect.topLeft() - nowPos;
//                if(abs(tempPoint.x()) > abs(tempPoint.y()))
//                {
//                    newPos.setY(otherItem->y() - thisRectF.height() - 2);
//                }
//                else
//                {
//                    newPos.setX(otherItem->x() - otherRect.width() - 2);
//                }
//                this->setPos(newPos);
//                return newPos;
//            }
//        }
//    }

//    return QGraphicsObject::itemChange(change, value);
//}

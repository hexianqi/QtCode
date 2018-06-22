/***************************************************************************************************
**      2018-06-19  HAbstractMouseStrategy 抽象鼠标策略。
***************************************************************************************************/

#ifndef HABSTRACTMOUSESTRATEGY_H
#define HABSTRACTMOUSESTRATEGY_H

#include <QObject>

class QPaintEvent;
class QMouseEvent;
class HAbstractMouseStrategyPrivate;

class HAbstractMouseStrategy : public QObject
{
    Q_OBJECT

public:
    explicit HAbstractMouseStrategy(QWidget *parent = nullptr);
    ~HAbstractMouseStrategy();

public:
    virtual void setValidRegion(QRectF value);
    virtual void setEnable(bool b);

public:
    bool isEnable();

public:
    virtual void paintEvent(QPaintEvent *) = 0;
    virtual bool mousePressEvent(QMouseEvent *) = 0;
    virtual bool mouseMoveEvent(QMouseEvent *) = 0;
    virtual bool mouseReleaseEvent(QMouseEvent *) = 0;

protected:
    HAbstractMouseStrategy(HAbstractMouseStrategyPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractMouseStrategyPrivate> d_ptr;
};

#endif // HABSTRACTMOUSESTRATEGY_H

/***************************************************************************************************
**      2018-06-19  HAbstractMouseStrategy 抽象鼠标策略。
***************************************************************************************************/

#ifndef HABSTRACTMOUSESTRATEGY_H
#define HABSTRACTMOUSESTRATEGY_H

#include "IMouseStrategy.h"
#include <QObject>

class HAbstractMouseStrategyPrivate;

class HAbstractMouseStrategy : public QObject, public IMouseStrategy
{
    Q_OBJECT

public:
    explicit HAbstractMouseStrategy(QWidget *parent = nullptr);
    ~HAbstractMouseStrategy() override;

public:
    bool setValidRegion(QRectF value) override;
    bool setEnable(bool b) override;
    bool isEnable() override;

protected:
    HAbstractMouseStrategy(HAbstractMouseStrategyPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractMouseStrategyPrivate> d_ptr;
};

#endif // HABSTRACTMOUSESTRATEGY_H

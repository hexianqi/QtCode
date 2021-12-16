/***************************************************************************************************
**      2019-06-19  ICircular 等待策略。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

class QPainter;

HE_BEGIN_NAMESPACE

class ICircular : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void dataChanged();

public:
    // 绘制
    virtual void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE

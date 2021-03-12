/***************************************************************************************************
**      2019-07-15  HAbstractColorPanel 抽象颜色面板
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractColorPanelPrivate;

class HAbstractColorPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit HAbstractColorPanel(QWidget *parent = nullptr);
    ~HAbstractColorPanel() override;

signals:
    void colorPicked(const QColor &value);

public:
    QColor color() const;

public slots:
    virtual void setColor(const QColor &value);

protected:
    HAbstractColorPanel(HAbstractColorPanelPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractColorPanelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

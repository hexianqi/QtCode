/***************************************************************************************************
**      2020-09-02  HTimeTooltip
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HTimeTooltipPrivate;

class HTimeTooltip : public QWidget
{
    Q_OBJECT

public:
    explicit HTimeTooltip(QWidget *parent = nullptr);
    ~HTimeTooltip() override;

public:
    void setTip(const QPoint &pos, const QString &time, const QString &text);
    void show();

protected:
    HTimeTooltip(HTimeTooltipPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void adjustPosition();
    void buildPath();

protected:
    QScopedPointer<HTimeTooltipPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE


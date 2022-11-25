/***************************************************************************************************
**      2022-11-18  HTimelineWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HTimelineWidgetPrivate;

class HTimelineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTimelineWidget(QWidget *parent = nullptr);
    ~HTimelineWidget() override;

public:
    void addInfo(QDate, QString);

protected:
    HTimelineWidget(HTimelineWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *)override;
    void drawBigCircle(QPainter *, int x, int y);
    void drawSmallCircle(QPainter *, int x, int y);

protected:
    QScopedPointer<HTimelineWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE


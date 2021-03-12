/***************************************************************************************************
**      2019-04-04  HCalloutChartExtend 图表扩展 - 带标注。
***************************************************************************************************/

#pragma once

#include "HAbstractChartExtend.h"
#include <QtCore/QPointF>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

class HCalloutChartExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HCalloutChartExtend : public HAbstractChartExtend
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCalloutChartExtend)

public:
    explicit HCalloutChartExtend(QObject *parent = nullptr);
    explicit HCalloutChartExtend(QChart *chart, QObject *parent = nullptr);

public:
    bool connectExtend() override;
    bool disconnectExtend() override;
    void connectSeries(QAbstractSeries *);
    void disconnectSeries(QAbstractSeries *);
    void updateGeometry();
    void clear();

protected:
    HCalloutChartExtend(HCalloutChartExtendPrivate &p, QObject *parent = nullptr);

protected slots:
    void handleSeriesClicked(QPointF point);
    void handleSeriesHovered(QPointF point, bool state);
};

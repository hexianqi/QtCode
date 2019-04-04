/***************************************************************************************************
**      2018-07-05  HMarkerChartExtend 图表扩展 - 图例标记可选。
***************************************************************************************************/

#ifndef HMARKERCHARTEXTEND_H
#define HMARKERCHARTEXTEND_H

#include "HAbstractChartExtend.h"

class HMarkerChartExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HMarkerChartExtend : public HAbstractChartExtend
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMarkerChartExtend)

public:
    explicit HMarkerChartExtend(QObject *parent = nullptr);
    explicit HMarkerChartExtend(QChart *chart, QObject *parent = nullptr);
    ~HMarkerChartExtend();

public:
    bool connectExtend() override;
    bool disconnectExtend() override;

protected:
    void handleMarkerClicked();

protected:
    HMarkerChartExtend(HMarkerChartExtendPrivate &p, QObject *parent = nullptr);
};

#endif // HMARKERCHARTEXTEND_H

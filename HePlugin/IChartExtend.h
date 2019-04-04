/***************************************************************************************************
**      2019-04-04  IChartExtend 图表扩展接口。
***************************************************************************************************/

#ifndef ICHARTEXTEND_H
#define ICHARTEXTEND_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class QDESIGNER_WIDGET_EXPORT IChartExtend
{
public:
    // 设置图表
    virtual void setChart(QChart *) = 0;
    // 连接扩展
    virtual bool connectExtend() = 0;
    // 断开扩展
    virtual bool disconnectExtend() = 0;
};

#endif // ICHARTEXTEND_H

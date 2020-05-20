/***************************************************************************************************
**      2018-07-05  HAbstractChartExtend 抽象图表扩展。
***************************************************************************************************/

#ifndef HABSTRACTCHARTEXTEND_H
#define HABSTRACTCHARTEXTEND_H

#include "IChartExtend.h"
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QObject>
#include <functional>

QT_CHARTS_BEGIN_NAMESPACE
class QLegendMarker;
class QAbstractSeries;
QT_CHARTS_END_NAMESPACE

class HAbstractChartExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HAbstractChartExtend : public QObject, public IChartExtend
{
    Q_OBJECT

public:
    explicit HAbstractChartExtend(QObject *parent = nullptr);
    explicit HAbstractChartExtend(QChart *chart, QObject *parent = nullptr);
    ~HAbstractChartExtend() override;

public:
    void setChart(QChart *) override;
    QChart *chart() override;
    bool connectExtend() override;
    bool disconnectExtend() override;

protected:
    HAbstractChartExtend(HAbstractChartExtendPrivate &p, QObject *parent = nullptr);

protected:
    void forEachMarker(const std::function<void(QLegendMarker *)> &func);
    void forEachSeries(const std::function<void(QAbstractSeries *)> &func);

protected:
    QScopedPointer<HAbstractChartExtendPrivate> d_ptr;
};

#endif // HABSTRACTCHARTEXTEND_H

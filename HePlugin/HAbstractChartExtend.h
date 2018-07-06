/***************************************************************************************************
**      2018-07-05  HAbstractChartExtend 抽象图表扩展。
***************************************************************************************************/

#ifndef HABSTRACTCHARTEXTEND_H
#define HABSTRACTCHARTEXTEND_H

#include <QObject>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class HAbstractChartExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HAbstractChartExtend : public QObject
{
    Q_OBJECT

public:
    explicit HAbstractChartExtend(QChart *chart, QObject *parent = nullptr);
    ~HAbstractChartExtend();

protected:
    HAbstractChartExtend(HAbstractChartExtendPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractChartExtendPrivate> d_ptr;
};

#endif // HABSTRACTCHARTEXTEND_H

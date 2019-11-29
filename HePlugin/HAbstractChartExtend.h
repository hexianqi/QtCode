/***************************************************************************************************
**      2018-07-05  HAbstractChartExtend 抽象图表扩展。
***************************************************************************************************/

#ifndef HABSTRACTCHARTEXTEND_H
#define HABSTRACTCHARTEXTEND_H

#include "IChartExtend.h"
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QObject>

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
    QScopedPointer<HAbstractChartExtendPrivate> d_ptr;
};

#endif // HABSTRACTCHARTEXTEND_H

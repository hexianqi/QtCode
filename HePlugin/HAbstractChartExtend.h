/***************************************************************************************************
**      2018-07-05  HAbstractChartExtend 抽象图表扩展。
***************************************************************************************************/

#ifndef HABSTRACTCHARTEXTEND_H
#define HABSTRACTCHARTEXTEND_H

#include "IChartExtend.h"
#include <QtCore/QObject>

class HAbstractChartExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HAbstractChartExtend : public QObject, public IChartExtend
{
    Q_OBJECT

public:
    explicit HAbstractChartExtend(QObject *parent = nullptr);
    explicit HAbstractChartExtend(QChart *chart, QObject *parent = nullptr);
    ~HAbstractChartExtend();

public:
    void setChart(QChart *) override;
    bool connectExtend() override;
    bool disconnectExtend() override;

public:
    QChart *chart();

protected:
    HAbstractChartExtend(HAbstractChartExtendPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractChartExtendPrivate> d_ptr;
};

#endif // HABSTRACTCHARTEXTEND_H

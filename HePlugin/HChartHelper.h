#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class QDESIGNER_WIDGET_EXPORT HChartHelper
{
public:
    static QChart *switchChartType(QChart *);
};


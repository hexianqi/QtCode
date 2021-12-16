#include "HTm30RxhjWidget_p.h"
#include "HTm30BarChart.h"
#include "HTm30RcshjChartView.h"
#include "HTm30RhshjChartView.h"
#include "HTm30RfhjChartView.h"
#include <QtWidgets/QVBoxLayout>

HTm30RxhjWidget::HTm30RxhjWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTm30RxhjWidgetPrivate)
{
    init();
}

HTm30RxhjWidget::~HTm30RxhjWidget()
{
}

void HTm30RxhjWidget::setRcshj(QList<double> value)
{
    d_ptr->rcshj->chart()->setBarValue(value);
}

void HTm30RxhjWidget::setRhshj(QList<double> value)
{
    d_ptr->rhshj->chart()->setBarValue(value);
}

void HTm30RxhjWidget::setRfhj(QList<double> value)
{
    d_ptr->rfhj->chart()->setBarValue(value);
}

void HTm30RxhjWidget::init()
{
    auto layout = new QVBoxLayout(this);
    d_ptr->rcshj = new HTm30RcshjChartView;
    d_ptr->rhshj = new HTm30RhshjChartView;
    d_ptr->rfhj = new HTm30RfhjChartView;
    d_ptr->rcshj->chart()->axisX()->setTitleVisible(false);
    d_ptr->rcshj->chart()->axisX()->setLabelsVisible(false);
    d_ptr->rhshj->chart()->axisX()->setTitleVisible(false);
    d_ptr->rhshj->chart()->axisX()->setLabelsVisible(false);
    layout->addWidget(d_ptr->rcshj);
    layout->addWidget(d_ptr->rhshj);
    layout->addWidget(d_ptr->rfhj);
    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setStyleSheet("background-color: rgb(255, 255, 255);");
    setWindowTitle("Rx,hj");
}



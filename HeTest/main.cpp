#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "HeAlgorithm/HRegister.h"
#include "HeAlgorithm/HSpectrumFacade.h"
#include "HePlugin/HCIE1931View.h"
#include "HePlugin/HCIE1931Widget.h"
#include <functional>
#include <QTreeWidgetItem>
#include <QtMath>
#include <QRandomGenerator>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
//#include <gsl/gsl_sf_bessel.h>
#include <iostream>

QT_CHARTS_USE_NAMESPACE
HE_ALGORITHM_USE_NAMESPACE

void TestRegister()
{
    HRegister reg;
    if (reg.checkRegisterCode())
        return;

    auto id = reg.getRegisterId();
    auto code = reg.encrypt(id);
    qDebug() << id;
    qDebug() << code;
    reg.setRegisterCode(code);
}

//void TestGsl()
//{
//    auto x = 10.0;
//    auto y = gsl_sf_bessel_j0(x);
//    qDebug() << QString("Jo(%1) = %2").arg(x).arg(y);
//}

QWidget *TestChart()
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++)
    {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    auto *chartView = new HCIE1931View;
    chartView->setChart(chart);
    chart->setZValue(20);
    return chartView;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HCIE1931Widget w;
//    QPolygonF poly = QPolygonF() << QPointF(0.1, 0.1) << QPointF(0.2,0.3) << QPointF(0.4,0.5) << QPointF(0.7,0.1) << QPointF(0.6,0.4);
//    w.addPolygon(1, poly, Qt::red);
    w.show();


//    QMainWindow window;
//    window.setCentralWidget(TestChart());
//    window.resize(400, 300);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}




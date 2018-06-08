#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "HeAlgorithm/HRegister.h"
#include "HeAlgorithm/HSpectrumFacade.h"
#include "HePlugin/HCIE1931View.h"
#include <functional>
#include <QTreeWidgetItem>
#include <QtMath>
#include <QRandomGenerator>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <gsl/gsl_sf_bessel.h>
#include <iostream>

QT_CHARTS_USE_NAMESPACE
HE_ALGORITHM_USE_NAMESPACE

// 测试注册机
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

void TestGsl()
{
    auto x = 10.0;
    auto y = gsl_sf_bessel_j0(x);
    qDebug() << QString("Jo(%1) = %2").arg(x).arg(y);
}

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
    //   chartView->setChart(chart);
    return chartView;
}

void TestTran()
{
    QRectF target(30, 30, 300, 300);
    QRectF source(10, 10, 200, 200);
    QPointF p1(50, 50);

    QTransform tran;
    tran.translate(-source.left(), -source.top());
    tran.scale(target.width() / source.width(), target.height() / source.height());
  //  tran.translate(target.left(), target.top());
    tran.translate(20, 20);


    auto p2 = tran.map(p1);
    qDebug() << p2;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    TestTran();


//    QMainWindow window;
//    window.setCentralWidget(TestChart());
//    window.resize(400, 300);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}




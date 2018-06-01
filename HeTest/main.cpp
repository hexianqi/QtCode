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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    std::function<int(int,int)> fun;
//    TestRegister();

//    HSpectrumFacade sf;
//    sf.getChromaticity();

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

//    QPixmap pixmap(":/image/CIE1931.png");
//    QBrush br(pixmap);
//    chart->setPlotAreaBackgroundVisible(true);
//    chart->setPlotAreaBackgroundBrush(br);



    auto *chartView = new HCIE1931View;
 //   chartView->setRenderHint(QPainter::Antialiasing);
 //   chartView->setChart(chart);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.grabGesture(Qt::PanGesture);
    window.grabGesture(Qt::PinchGesture);
    window.show();

    return a.exec();
}




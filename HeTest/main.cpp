#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include <QApplication>
#include <QDebug>
#include <functional>
#include <QChartView>
#include <QPolygonF>
#include <QFile>
#include <QTextStream>

QPolygonF readFile()
{
    int i,n;
    QString str;


    QFile file(":/dat/CIE_DAY.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QPolygonF poly;
    double x,y,t1,t2;

    in >> str >> n;
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
    {
        in >> x >> y >> t1 >> t2;
        poly << QPointF(x,y);
    }
    file.close();
    return poly;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HTestGsl gsl;

//    QPolygonF p1,p2;
//    for (int i = 0; i < 10; i++)
//        p1 << QPointF(i + 0.5 * std::sin(i), i + std::cos(i * i));
//    p2 = gsl.interpolation(p1);
//    auto chart = HTestChart::diffChart(p1, p2);

    auto p1 = readFile();
    auto p2 = gsl.interpolation(p1);
    auto chart = HTestChart::diffChart(p1, p2);


    QMainWindow window;
    window.setCentralWidget(chart);
    window.resize(400, 300);
    window.grabGesture(Qt::PanGesture);
    window.grabGesture(Qt::PinchGesture);
    window.show();

    return a.exec();
}




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

void TestVector(QVector<double> *c)
{
    qDebug() << (*c)[0];

    *c << 2.0 << 3.0;
    qDebug() << *c;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<double> t;
    t.fill(1.0, 3);
    TestVector(&t);

    qDebug() << t;

//    HTestGsl gsl;
//    QMainWindow window;
//    window.setCentralWidget(gsl.linearFitting());
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}




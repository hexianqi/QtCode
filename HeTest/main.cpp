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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HTestPlugin::testCIE1931View()->show();

//    HTestGsl gsl;
//    QMainWindow window;
//    window.setCentralWidget(gsl.interpEval());
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}

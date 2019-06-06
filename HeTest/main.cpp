#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include "HeExample/HeControl/HControlTester.h"
#include <QtCore/QDebug>
#include <QtGui/QPolygonF>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtCharts/QChartView>
#include <functional>

HE_CONTROL_USE_NAMESPACE

void testGslChart()
{
    HTestGsl gsl;
    auto p = gsl.interpEval();
    HTestChart::diffChart(p[0], p[1])->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    HControlTester tester;
    tester.createWidget("HGifWidget")->show();

//    HTestPlugin::testCIE1931View()->show();

//    QMainWindow window;
//    window.setCentralWidget(gsl.interpEval());
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}

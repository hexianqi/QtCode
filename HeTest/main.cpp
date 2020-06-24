#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include "HTestMedia.h"
#include "HeCore/HCore.h"
#include "HeAlgorithm/HChromaticity.h"
#include "HeExample/HeControl/HDemoWidget.h"
#include "HeExample/HeControl/HControlFactoryWidget.h"
#include "HeExample/HeControl/HControlDemoWidget.h"
#include <QtCore/QDebug>
#include <QtGui/QPolygonF>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtCharts/QChartView>
#include <functional>


HE_CORE_USE_NAMESPACE
HE_ALGORITHM_USE_NAMESPACE
HE_CONTROL_USE_NAMESPACE

void testGslChart()
{
    auto p = HTestGsl::interpEval();
    HTestChart::diffChart(p[0], p[1])->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

void exportCieUcs()
{
    auto chromaticity = new HChromaticity();

    chromaticity->exportCieUcs("test1", QPointF( 2300,  5000),  2.0);
    chromaticity->exportCieUcs("test2", QPointF( 5000, 10000),  5.0);
    chromaticity->exportCieUcs("test3", QPointF(10000, 15000), 10.0);
    chromaticity->exportCieUcs("test4", QPointF(15000, 20000), 20.0);
    chromaticity->exportCieUcs("test5", QPointF(20000, 25000), 50.0);
}

int main(int argc, char *argv[])
{
    qDebug() << HCore::toCommand(HLogType::ForePurple);
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    HTestMedia::audioEncoder("", "");
    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
//    HControlDemoWidget dw;
//    dw.show();

//    MainWindow window;
//    window.setCentralWidget(new HControlWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
    return a.exec();
}

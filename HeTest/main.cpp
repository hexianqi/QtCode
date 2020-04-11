#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include "HeCore/HCore.h"
#include "HeExample/HeControl/HDemoWidget.h"
#include "HeExample/HeControl/HControlFactoryWidget.h"
#include "HeExample/HeControl/HControlDemoWidget.h"
#include <QtCore/QDebug>
#include <QtGui/QPolygonF>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtCharts/QChartView>
#include <functional>
#include <QImageReader>

HE_CORE_USE_NAMESPACE
HE_CONTROL_USE_NAMESPACE

void testGslChart()
{
    auto p = HTestGsl::interpEval();
    HTestChart::diffChart(p[0], p[1])->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

int main(int argc, char *argv[])
{
    qDebug() << HCore::toCommand(HLogType::ForePurple);
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    a.setStyle(QStyleFactory::create("Plastique"));

    HControlFactoryWidget cw;
    cw.show();
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

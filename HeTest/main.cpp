#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestData.h"
#include "HTestGsl.h"
#include "HTestMedia.h"
#include "HTestOpenGL.h"
#include "HTestPlugin.h"
#include "HeCore/HCore.h"
#include "HeControl/HDemoWidget.h"
#include "HeControl/HControlFactoryWidget.h"
#include "HeControl/HControlDemoWidget.h"
#include "HeControl/HOpenGLDemoWidget.h"
#include "HeControl/HBreakoutWidget.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtCharts/QChartView>

#include "HePlugin/HTm30BarChart.h"
#include "HePlugin/HTm30RfiChartView.h"
#include "HePlugin/HTm30RfhjChartView.h"
#include "HePlugin/HTm30RcshjChartView.h"
#include "HePlugin/HTm30RhshjChartView.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_USE_NAMESPACE


void testGslChart()
{
    auto p = HTestGsl::interpEval();
    HTestChart::lineChart(p)->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

int main(int argc, char *argv[])
{
    qDebug() << HCore::toCommand(HLogType::ForePurple);
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    auto data = HTestAlgorithm::testIesTm30();

//    HTm30RfiChartView rfi;
//    rfi.chart()->setBarValue(data.Rfi.toList());
//    rfi.show();

//    HTm30RfhjChartView rfhj;
//    rfhj.chart()->setBarValue(data.hj.Rf.toList());
//    rfhj.show();

//    QList<double> data1;
//    for (auto v : data.hj.Rcs)
//        data1 << v * 100;
//    HTm30RcshjChartView rcshj;
//    rcshj.chart()->setBarValue(data1);
//    rcshj.show();

    HTm30RhshjChartView rhshj;
    rhshj.chart()->setBarValue(data.hj.Rhs.toList());
    rhshj.show();


//    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
//    HControlDemoWidget dw;
//    dw.show();

//    HBreakoutWidget ow;
//    ow.move(50, 300);
//    ow.resize(800, 600);
//    ow.show();

//    MainWindow window;
//    window.setCentralWidget(&videoWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
    return a.exec();
}

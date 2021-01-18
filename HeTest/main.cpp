﻿#include "MainWindow.h"
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

//    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
//    HControlDemoWidget dw;
//    dw.show();

    HBreakoutWidget ow;
    ow.move(50, 300);
    ow.resize(800, 600);
    ow.show();

//    MainWindow window;
//    window.setCentralWidget(&videoWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
    return a.exec();
}

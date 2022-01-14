#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestCore.h"
#include "HTestData.h"
#include "HTestEigen.h"
#include "HTestGsl.h"
#include "HTestMedia.h"
#include "HTestOpenGL.h"
#include "HTestPlugin.h"
#include "HeCore/HCore.h"
#include "HeCore/HDumpTree.h"
#include "HeControl/HDemoWidget.h"
#include "HeControl/HControlFactoryWidget.h"
#include "HeControl/HControlDemoWidget.h"
#include "HeControl/HOpenGLDemoWidget.h"
#include "HeControl/HBreakoutWidget.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QRegularExpression>

void testGslChart()
{
    auto p = HTestGsl::interpEval();
    HTestPlugin::lineChart(p)->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

int main(int argc, char *argv[])
{
    qDebug() << HCore::toCommand(HLogType::ForePurple);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QApplication::setStyle(QStyleFactory::create("Plastique"));

//    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
    HControlDemoWidget dw;
    dw.show();

//    HBreakoutWidget ow;
//    ow.move(50, 300);
//    ow.resize(800, 600);
//    ow.show();

//    HTestAlgorithm::testIesTm30();


//    MainWindow window;
////    window.setCentralWidget(&videoWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
//    HDumpTree::dumpProperty(&window);

    return a.exec();
}

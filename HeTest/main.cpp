#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestCore.h"
#include "HTestData.h"
#include "HTestDir.h"
#include "HTestEigen.h"
#include "HTestFile.h"
#include "HTestGsl.h"
#include "HTestMedia.h"
#include "HTestOpenGL.h"
#include "HTestPlugin.h"
#include "HTestSql.h"
#include "HeCore/HCore.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeControl/HControlFactoryWidget.h"
#include "HeControl/HControlDemoWidget.h"
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

#include <string>
#include <sstream>

void testGslChart()
{
    auto p = HTestGsl::interpEval();
    HTestPlugin::lineChart(p)->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();
}

int main(int argc, char *argv[])
{
    HCoreGlobalInstance::instance()->initialize();
    qDebug() << HCore::toCommand(HLogType::ForePurple);

    // 设置启用高分屏缩放支持
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 设置启用高分屏图片支持
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 设置OpenGL模式
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication::addLibraryPath("./plugins");
    QApplication::setStyle(QStyleFactory::create("Plastique"));
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    HTestFile::toString("CIE1964.dat", "HData_CIE1964.cpp");
    HTestFile::toString("CIE224_2017_R99_1nm.dat", "HData_CIE_IES.cpp");

 //    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
    return 0;


    HControlDemoWidget dw;
    dw.show();

//   HMainWindow window;
////    window.setCentralWidget(&videoWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
////    HDumpTree::dumpProperty(&window);

    return a.exec();
}

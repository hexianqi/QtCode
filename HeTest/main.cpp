#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestCore.h"
#include "HTestData.h"
#include "HTestDir.h"
#include "HTestEigen.h"
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

    QList<int> lunarData;
    lunarData << 461653 << 1386 << 2413;                                                               // 1968--1970
    lunarData << 330077 << 1197 << 2637 << 268877 << 3365 << 531109 << 2900 << 2922 << 398042 << 2395; // 1971--1980
    lunarData << 1179 << 267415 << 2635 << 661067 << 1701 << 1748 << 398772 << 2742 << 2391 << 330031; // 1981--1990
    lunarData << 1175 << 1611 << 200010 << 3749 << 527717 << 1452 << 2742 << 332397 << 2350 << 3222;   // 1991--2000
    lunarData << 268949 << 3402 << 3493 << 133973 << 1386 << 464219 << 605 << 2349 << 334123 << 2709;  // 2001--2010
    lunarData << 2890 << 267946 << 2773 << 592565 << 1210 << 2651 << 395863 << 1323 << 2707 << 265877; // 2011--2020
    lunarData << 1706 << 2773 << 133557 << 1206 << 398510 << 2638 << 3366 << 335142 << 3411 << 1450;   // 2021--2030
    lunarData << 200042 << 2413 << 723293 << 1197 << 2637 << 399947 << 3365 << 3410 << 334676 << 2906; // 2031--2040

    for (auto i : lunarData)
        qDebug() << "<< 0x" << QString("%1").arg(i, 6, 16, QChar('0')).toUpper();
    return 0;

//    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
//    HControlDemoWidget dw;
//    dw.show();

//   HMainWindow window;
////    window.setCentralWidget(&videoWidget);
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();
////    HDumpTree::dumpProperty(&window);

    return a.exec();
}

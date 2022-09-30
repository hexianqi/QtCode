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

    double d = 1.2345678901E-10;
    auto str = QString::number(d, 'e', 12);
    QVector<uchar> ch;
    for (auto c : str)
        ch.append(c.toLatin1());

    QString str2;
    for (auto c : ch)
        str2.append(c);
    auto d2 = str2.toDouble();

//    qDebug() << d;
//    qDebug() << str;
//    qDebug() << ch;
//    qDebug() << str2;
//    qDebug() << d2;

    std::ostringstream stream;
    stream << d;
    auto strB =  stream.str();

    qDebug() << d;
    qDebug() << QString::fromStdString(strB);


    std::string strA = "1.234567890E+10";
    auto v = std::stod(strA);
    qDebug() << &strA;
    qDebug() << v;

    return 0;



//    HTestMedia::videoPlayer_vlc("media\\Titanic.ts");
//    return 0;

//    HControlFactoryWidget cw;
//    cw.show();
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

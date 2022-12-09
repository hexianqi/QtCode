#include "HMainWindow1000A.h"
#include "HMainWindow1000RGB.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeSql/HSqlGlobalInstance.h"
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    HCoreGlobalInstance::instance()->initialize();
    HSqlGlobalInstance::instance()->initialize();

#ifdef SL1000A
    QApplication::setApplicationName("SL1000A");
    HMainWindow1000A w;
#endif

#ifdef SL1000RGB
    QApplication::setApplicationName("SL1000RGB");
    HMainWindow1000RGB w;
#endif

    w.showMaximized();
    return a.exec();
}

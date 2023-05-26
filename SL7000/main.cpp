#include "HMainWindow7000.h"
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

#ifdef SL7000
    QApplication::setApplicationName("SL7000");
    H_TCD(HMainWindow7000) w;
#endif

    w.showMaximized();
    return a.exec();
}

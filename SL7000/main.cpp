#include "HMainWindow7000.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeSql/HSqlGlobalInstance.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);

    HCoreGlobalInstance::instance()->init();
    HSqlGlobalInstance::instance()->init();

#ifdef SL7000
    QApplication::setApplicationName("SL7000");
    HMainWindow7000 w;
    w.show();
#endif

    return a.exec();
}

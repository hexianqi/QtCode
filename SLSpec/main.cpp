#include "HMainWindowSpec.h"
#include "HeCore/HCoreGlobalInstance.h"
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    HCoreGlobalInstance::instance()->initialize();

    HMainWindowSpec w;
    w.show();
    return a.exec();
}

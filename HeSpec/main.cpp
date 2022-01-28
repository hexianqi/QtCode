#include "HMainWindowSpec.h"
#include "HeCore/HCoreGlobalInstance.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");

    HCoreGlobalInstance::instance()->initialize();

    HMainWindowSpec w;
    w.show();
    return a.exec();
}

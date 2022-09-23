#include "HMainWindowDemo.h"
#include "HeCore/HCoreGlobalInstance.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HCoreGlobalInstance::instance()->initialize();

    HMainWindowDemo w;
    w.show();

    return a.exec();
}

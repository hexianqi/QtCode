#include "HMainWindowSpec.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    HMainWindowSpec w;
    w.show();
    return a.exec();
}

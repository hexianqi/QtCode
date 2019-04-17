#include "HMainWindow2000.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    HMainWindow2000 w;
    w.show();
    return a.exec();
}

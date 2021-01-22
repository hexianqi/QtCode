#include "HMainWindow2000.h"
#include "HMainWindow2000DC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

#ifdef SL2000
    QApplication::setApplicationName("SL2000");
    HMainWindow2000 w;
    w.show();
#elif SL2000DC
    QApplication::setApplicationName("SL2000DC");
    HMainWindow2000DC w;
    w.show();
#endif
    return QApplication::exec();
}

#include "HMainWindow2000.h"
#include "HMainWindow2000AC.h"
#include "HMainWindow2000DC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

#ifdef SL2000
    QApplication::setApplicationName("SL2000");
    HMainWindow2000 w;
#elif SL2000AC
    QApplication::setApplicationName("SL2000AC");
    HMainWindow2000AC w;
#elif SL2000DC
    QApplication::setApplicationName("SL2000DC");
    HMainWindow2000DC w;
#endif
    w.show();
    return QApplication::exec();
}

#include "HMainWindow2100DC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

#ifdef SL2100DC
    QApplication::setApplicationName("SL2100DC");
    HMainWindow2100DC w;
    w.show();
//#elif SL2000AC
//    QApplication::setApplicationName("SL2100AC");
//    HMainWindow2000AC w;
//    w.show();
#endif

    return a.exec();
}

#include "HMainWindow2000.h"
#include "HMainWindow2000AC.h"
#include "HMainWindow2000DC.h"
#include "HMainWindow2000F.h"
#include <QtCore/QTranslator>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

    QTranslator t1, t2, t3;
    if (t1.load("HeCore_en"))
        a.installTranslator(&t1);
    if (t2.load("HeGui_en"))
        a.installTranslator(&t2);
    if (t3.load("SL2000_en"))
        a.installTranslator(&t3);

#ifdef SL2000
    QApplication::setApplicationName("SL2000");
    HMainWindow2000 w;
#elif SL2000AC
    QApplication::setApplicationName("SL2000AC");
    HMainWindow2000AC w;
#elif SL2000DC
    QApplication::setApplicationName("SL2000DC");
    HMainWindow2000DC w;
#elif SL2000F
    QApplication::setApplicationName("SL2000F");
    HMainWindow2000F w;
#endif
    w.show();
    return QApplication::exec();
}

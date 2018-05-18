#include "HMainWindow2000.h"
#include "HBuilder2000.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ;
//    QScopedPointer<HMainWindow> w(build.createMainWindow());
//    w->show();

    HBuilder2000 build;
    build.createMainWindow()->show();

//    HMainWindow2000 w;
//    w.init();
//    w.show();

    return a.exec();
}

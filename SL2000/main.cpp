#include "HBuilder2000.h"
#include "HMainWindow2000.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    HBuilder2000 build;
//    auto w = build.createWidget();
//    w->show();


    HMainWindow2000 w;
    HBuilder2000 build(&w);
    build.createWidget();
    w.show();
    return a.exec();
}

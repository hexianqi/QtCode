#include "HMainWindow2000.h"
#include "HBuilder2000.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HBuilder2000 build;
    build.createMainWindow()->show();
    return a.exec();
}

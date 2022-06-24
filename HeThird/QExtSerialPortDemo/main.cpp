#include "HMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HMainWindow w;
    w.show();
    return a.exec();
}

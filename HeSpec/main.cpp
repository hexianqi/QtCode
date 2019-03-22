#include "HMainWindowSpec.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HMainWindowSpec w;
    w.show();
    return a.exec();
}

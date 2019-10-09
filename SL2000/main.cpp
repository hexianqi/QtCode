/***************************************************************************************************
**      2019-05-27  SL2000 光谱测试仪。
***************************************************************************************************/

#include "HMainWindow2000.h"
#include <QtWidgets/QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");

#ifdef SL2000
    a.setApplicationName("SL2000");
    HMainWindow2000 w;
    w.show();
#endif
    return a.exec();
}

/***************************************************************************************************
**      2019-05-27  SL2000 光谱测试仪。
***************************************************************************************************/

#include "HMainWindow2000.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
//    a.setApplicationName("SL2000");
//    a.setOrganizationName("杭州");
    HMainWindow2000 w;
    w.show();
    return a.exec();
}

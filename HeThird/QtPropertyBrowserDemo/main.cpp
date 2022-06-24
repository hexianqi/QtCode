#include "HDemoWidget.h"
#include "HVariantWidget.h"
#include "HPropertyBrowser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    HPropertyBrowser widget;
//    widget.setObject(new HDemoWidget);
//    widget.show();

    HDemoWidget w;
    w.show();

//    HMainWindow w;
//    w.show();


    return a.exec();
}

#include "HMainWindow3000.h"
#include "HHelper.h"
#include "HDBLoginDialog.h"
#include "HeCore/HCoreGlobalInstance.h"
#include <QtCore/QTextCodec>
#include <QtCore/QThread>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>

HE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(HeGui);

    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    HCoreGlobalInstance::instance()->initialize();
    HCoreGlobalInstance::instance()->startLogService();

    if (!HHelper::initialize())
        return 0;

//    HDBLoginDialog dlg;
//    if (dlg.exec() != QDialog::Accepted)
//        return 0;

    QPixmap pixmap(":/image/welcome.jpg");
    QSplashScreen splash(pixmap);
    splash.setWindowOpacity(0.8);
    splash.show();
    splash.showMessage("程序正在启动......", Qt::AlignBottom | Qt::AlignHCenter, Qt::red);
//    QThread::sleep(3);

    HMainWindow3000 w;
    w.show();
    splash.finish(&w);

    return a.exec();
}

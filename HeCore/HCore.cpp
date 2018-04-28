#include "HCore.h"
#include <QEventLoop>
#include <QTimer>

HE_CORE_USE_NAMESPACE

void HeCore::msleep(int msecs)
{
    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);
    timer.setInterval(msecs);
    QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timer.start();
    eventLoop.exec();
}

/***************************************************************************************************
**      延时方法2
***************************************************************************************************/
//void msleep(int msecs)
//{
//    QTime dieTime = QTime::currentTime().addMSecs(msecs);
//    while (QTime::currentTime() < dieTime )
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
//}

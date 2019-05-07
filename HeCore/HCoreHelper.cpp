#include "HCoreHelper.h"
#include <QtCore/QTimer>
#include <QtCore/QEventLoop>

HE_CORE_BEGIN_NAMESPACE

void HCoreHelper::msleep(ulong msecs)
{
    QEventLoop event;
    QTimer::singleShot(msecs, &event, SLOT(quit()));
    event.exec();
}

/***************************************************************************************************
**      延时方法2
***************************************************************************************************/
//    void msleep(ulong msecs)
//    {
//        auto time = QTime::currentTime().addMSecs(msecs);
//        while (QTime::currentTime() < time )
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
//    }

QStringList HCoreHelper::unselected(QStringList optional, QStringList selected)
{
    for (auto s : selected)
        optional.removeAll(s);
    return optional;
}

HE_CORE_END_NAMESPACE

#include "HCoreHelper.h"
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

HE_CORE_BEGIN_NAMESPACE

QStringList HCoreHelper::unselected(QStringList optional, QStringList selected)
{
    for (auto s : selected)
        optional.removeAll(s);
    return optional;
}

void HCoreHelper::msleep(int msecs)
{
    QEventLoop event;
    QTimer::singleShot(msecs, &event, SLOT(quit()));
    event.exec();
}

void HCoreHelper::msleep2(int msecs)
{
    auto time = QTime::currentTime().addMSecs(msecs);
    while (QTime::currentTime() < time )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

HE_CORE_END_NAMESPACE

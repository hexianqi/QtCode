#include "HCoreHelper.h"
#include <QtCore/QSettings>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

QStringList HCoreHelper::unselected(QStringList optional, QStringList selected)
{
    for (const auto &s : selected)
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

void HCoreHelper::dumpStructure(const QObject *obj, int spaceCount)
{
    qDebug() << QString("%1%2 : %3")
                    .arg("", spaceCount)
                    .arg(obj->metaObject()->className(), obj->objectName());
    for (auto child : obj->children())
        dumpStructure(child, spaceCount + 4);
}

void HCoreHelper::readSettings(QString fileName, QString prefix, QVariantMap &params)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup(prefix);
    for (const auto &k : settings.allKeys())
        params.insert(k, settings.value(k));
    settings.endGroup();
}

void HCoreHelper::writeSettings(QString fileName, QString prefix, QVariantMap params)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup(prefix);
    for (auto i = params.begin(); i != params.end(); i++)
        settings.setValue(i.key(), i.value());
    settings.endGroup();
}

HE_END_NAMESPACE

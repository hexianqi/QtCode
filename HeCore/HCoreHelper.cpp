#include "HCoreHelper.h"
#include <QtCore/QSettings>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QColor>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

QStringList HCoreHelper::unselected(QStringList optional, QStringList selected)
{
    for (const auto &s : selected)
        optional.removeAll(s);
    return optional;
}

QVariantMap HCoreHelper::unite(const QVariantMap &m1, const QVariantMap &m2)
{
    auto m = m1;
    for (auto i = m2.begin(); i != m2.end(); i++)
        m.insert(i.key(), i.value());
    return m;
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
    while (QTime::currentTime() < time)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QColor HCoreHelper::calcForeColor(QColor backColor)
{
    auto gray = (0.299 * backColor.red() + 0.587 * backColor.green() + 0.114 * backColor.blue()) / 255;
    return gray > 0.5 ? Qt::black : Qt::white;
}

void HCoreHelper::readSettings(const QString &fileName, const QString &prefix, QVariantMap &params)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup(prefix);
    for (const auto &k : settings.allKeys())
        params.insert(k, settings.value(k));
    settings.endGroup();
}

void HCoreHelper::writeSettings(const QString &fileName, const QString &prefix, const QVariantMap &params)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup(prefix);
    for (auto i = params.begin(); i != params.end(); i++)
        settings.setValue(i.key(), i.value());
    settings.endGroup();
}

HE_END_NAMESPACE

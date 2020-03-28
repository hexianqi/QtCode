#include "HCore.h"
#include <QtCore/QDebug>

HE_CORE_BEGIN_NAMESPACE

QString HCore::typeAddition(QString type, QString addition)
{
    return  QString("%1_%2]").arg(type.left(type.size() - 1)).arg(addition);
}

void HCore::dumpStructure(const QObject *obj, int spaceCount)
{
    qDebug() << QString("%1%2 : %3")
                .arg("", spaceCount)
                .arg(obj->metaObject()->className())
                .arg(obj->objectName());
    for (auto child : obj->children())
        dumpStructure(child, spaceCount + 4);
}

HE_CORE_END_NAMESPACE

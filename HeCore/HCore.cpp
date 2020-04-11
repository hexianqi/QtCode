#include "HCore.h"
#include <QtCore/QDebug>

HE_CORE_BEGIN_NAMESPACE

QString HCore::typeAddition(const QString &type, const QString &addition)
{
    return  QString("%1_%2]").arg(type.left(type.size() - 1), addition);
}

void HCore::dumpStructure(const QObject *obj, int spaceCount)
{
    qDebug() << QString("%1%2 : %3")
                .arg("", spaceCount)
                .arg(obj->metaObject()->className(), obj->objectName());
    for (auto child : obj->children())
        dumpStructure(child, spaceCount + 4);
}

HE_CORE_END_NAMESPACE

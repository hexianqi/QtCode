#include "HCore.h"
#include <QtCore/QString>

HE_CORE_BEGIN_NAMESPACE

QString HCore::typeAddition(QString type, QString addition)
{
    return  QString("%1_%2]").arg(type.left(type.size() - 1)).arg(addition);
}

HE_CORE_END_NAMESPACE

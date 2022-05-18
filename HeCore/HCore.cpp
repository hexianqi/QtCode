#include "HCore.h"

HE_BEGIN_NAMESPACE

QString HCore::typeAddition(const QString &type, const QString &addition)
{
    return  QString("%1_%2]").arg(type.left(type.size() - 1), addition);
}

HE_END_NAMESPACE

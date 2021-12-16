#include "HStyleHelper.h"
#include <QtCore/QFile>

HE_BEGIN_NAMESPACE

QString HStyleHelper::loadStyle(const QString &fileName)
{
    QString qss;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        qss = QLatin1String(file.readAll());
        file.close();
    }
    return qss;
}

HE_END_NAMESPACE

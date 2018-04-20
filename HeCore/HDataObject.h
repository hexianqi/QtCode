#ifndef HDATAOBJECT_H
#define HDATAOBJECT_H

#include "HeCore_global.h"
#include <QString>

namespace He {
namespace Core {

// 提供静态函数tr，数据类型。
class HECORE_EXPORT HDataObject
{
public:
    HDataObject();

public:
    static QString tr(const char *sourceText, const char *comment = 0, int n = -1);

public:
    virtual void initialize(QString type);
    virtual void setType(QString value);

public:
    QString type(bool bracket = true) const;

protected:
    QString removeBracket(QString text) const;

protected:
    QString _type;
};

} // Core
} // He


#endif // HDATAOBJECT_H

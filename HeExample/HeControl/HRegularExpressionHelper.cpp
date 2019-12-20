#include "HRegularExpressionHelper.h"
#include <QtCore/QRegularExpression>

HE_CONTROL_BEGIN_NAMESPACE

bool HRegularExpressionHelper::isMatch(const QString &text, const QString &pattern)
{
    QRegularExpression re(pattern);
    auto rem = re.match(text);
    return rem.hasMatch();
}

bool HRegularExpressionHelper::isIP(const QString &text)
{
    return isMatch(text, R"(^((2[0-4]\d|25[0-5]|[01]?\d\d?)\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)$)");
}

HE_CONTROL_END_NAMESPACE

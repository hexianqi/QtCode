#include "HRegularExpressionHelper.h"
#include <QtCore/QRegularExpression>
#include <QtGui/QRegularExpressionValidator>

HE_BEGIN_NAMESPACE

bool HRegularExpressionHelper::isMatch(const QString &text, const QString &pattern)
{
    QRegularExpression re(pattern);
    return re.match(text).hasMatch();
}

bool HRegularExpressionHelper::isIP(const QString &text)
{
    return isMatch(text, R"(^((2[0-4]\d|25[0-5]|[01]?\d\d?)\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)$)");
}

QRegularExpressionValidator *HRegularExpressionHelper::email(QObject *parent)
{
    QRegularExpression re(R"(^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$)");
    return new QRegularExpressionValidator(re, parent);
}

HE_END_NAMESPACE

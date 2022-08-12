#include "HQssStyle_p.h"
#include "HStyleHelper.h"
#include <QtGui/QPalette>

HE_BEGIN_NAMESPACE

HQssStyle::HQssStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HQssStylePrivate)
{
    init();
}

HQssStyle::HQssStyle(HQssStylePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HQssStyle::~HQssStyle() = default;

void HQssStyle::initialize(QVariantMap /*param*/)
{
}

QString HQssStyle::typeName()
{
    return "HQssStyle";
}

QString HQssStyle::toStyleSheet()
{
    return d_ptr->styleSheet.value(d_ptr->current);
}

QPalette HQssStyle::toPalette()
{
    return d_ptr->palette.value(d_ptr->current);
}

QColor HQssStyle::color(const QString &flag)
{
    auto style = toStyleSheet();
    auto index = style.indexOf(flag);
    if (index >= 0)
        return style.mid(index + flag.length(), 7);
    return Qt::black;
}

QStringList HQssStyle::styles()
{
    return d_ptr->styleSheet.keys();
}

bool HQssStyle::selectStyle(const QString &vlaue)
{
    if (d_ptr->current == vlaue || !d_ptr->styleSheet.contains(vlaue))
        return false;
    d_ptr->current = vlaue;
    return true;
}

void HQssStyle::addStyle(const QString &key, const QString &fileName)
{
    auto qss = HStyleHelper::loadStyle(fileName);
    if (qss.isEmpty())
        return;
    auto color = qss.mid(20, 7);
    d_ptr->styleSheet.insert(key, qss);
    d_ptr->palette.insert(key, QPalette(QColor(color)));
}

void HQssStyle::init()
{
    addStyle(tr("黑色风格"),        ":/Resources/qss/psblack.css");
    addStyle(tr("灰色扁平风格"),    ":/Resources/qss/flatgray.css");
    addStyle(tr("淡蓝色风格"),      ":/Resources/qss/lightblue.css");
    selectStyle(tr("淡蓝色风格"));
}

HE_END_NAMESPACE

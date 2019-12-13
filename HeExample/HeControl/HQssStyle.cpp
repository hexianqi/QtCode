#include "HQssStyle_p.h"
#include <QtCore/QFile>
#include <QtGui/QPalette>

HE_CONTROL_BEGIN_NAMESPACE

HQssStyle::HQssStyle(QObject *parent) :
    IQssStyle(parent),
    d_ptr(new HQssStylePrivate)
{
    init();
}

HQssStyle::HQssStyle(HQssStylePrivate &p, QObject *parent) :
    IQssStyle(parent),
    d_ptr(&p)
{
    init();
}

HQssStyle::~HQssStyle()
{
}

void HQssStyle::initialize(QVariantMap /*param*/)
{

}

QString HQssStyle::typeName()
{
    return "HQssStyle";
}

QPalette HQssStyle::toPalette()
{
    return d_ptr->palette.value(d_ptr->current);
}

QString HQssStyle::toStyleSheet()
{
    return d_ptr->styleSheet.value(d_ptr->current);
}

QStringList HQssStyle::styles()
{
    return d_ptr->styleSheet.keys();
}

bool HQssStyle::selectStyle(QString value)
{
    if (d_ptr->current == value || !d_ptr->styleSheet.contains(value))
        return false;
    d_ptr->current = value;
    return true;
}

void HQssStyle::addStyle(QString key, QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return;
    QString qss = QLatin1String(file.readAll());
    QString color = qss.mid(20, 7);
    d_ptr->styleSheet.insert(key, qss);
    d_ptr->palette.insert(key, QPalette(QColor(color)));
}

void HQssStyle::init()
{
    addStyle(tr("黑色风格"),        ":/qss/psblack.css");
    addStyle(tr("白色扁平化风格"),  ":/qss/flatwhite.css");
    addStyle(tr("淡绿色风格"),      ":/qss/lightblue.css");
    selectStyle(tr("淡绿色风格"));
}

HE_CONTROL_END_NAMESPACE

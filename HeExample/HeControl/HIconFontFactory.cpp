#include "HIconFontFactory_p.h"
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

HIconFontFactory::HIconFontFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HIconFontFactoryPrivate)
{
    registerClass();
}

HIconFontFactory::~HIconFontFactory() = default;

void HIconFontFactory::initialize(QVariantMap /*param*/)
{

}

QString HIconFontFactory::typeName()
{
    return "HIconFontFactory";
}

QStringList HIconFontFactory::families()
{
    return d_ptr->fontResource.keys();
}

QFont HIconFontFactory::createFont(const QString &family)
{
    auto db = QFontDatabase();
    if (db.families().contains(family))
        return QFont(family);
    if (!d_ptr->fontResource.contains(family))
    {
        qDebug() << tr("load %1 error.").arg(family);
        return QFont();
    }
    auto id = QFontDatabase::addApplicationFont(d_ptr->fontResource.value(family));     // 加入字体，并获取字体ID
    auto name = QFontDatabase::applicationFontFamilies(id).at(0);                       // 获取字体名称
    return QFont(name);
}

void HIconFontFactory::registerClass()
{
    d_ptr->fontResource.insert("FontAwesome",   ":/fonts/fontawesome-webfont.ttf");
    d_ptr->fontResource.insert("FontIcon",      ":/fonts/iconfont.ttf");
    d_ptr->fontResource.insert("FontWeather",   ":/fonts/pe-icon-set-weather.ttf");
}

HE_END_NAMESPACE

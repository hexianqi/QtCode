#include "HIconFontFactory_p.h"
#include <QtCore/QPoint>
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

QPoint HIconFontFactory::fontRange(const QString &family)
{
    return d_ptr->fontRange.value(family);
}

void HIconFontFactory::registerClass()
{
    d_ptr->fontResource.insert("FontWeather",       ":/Resources/fonts/pe-icon-set-weather.ttf");
    d_ptr->fontResource.insert("FontAwesome",       ":/Resources/fonts/fontawesome-webfont.ttf");
    d_ptr->fontResource.insert("FontAwesome6Pro",   ":/Resources/fonts/fa-regular-400.ttf");
    d_ptr->fontResource.insert("FontIcon",          ":/Resources/fonts/iconfont.ttf");
    d_ptr->fontRange.insert("FontWeather",          QPoint(0xe900, 0xe9cf));
    d_ptr->fontRange.insert("FontAwesome",          QPoint(0xf000, 0xf2e0));
    d_ptr->fontRange.insert("FontAwesome6Pro",      QPoint(0xe000, 0xf8ff));
    d_ptr->fontRange.insert("FontIcon",             QPoint(0xe500, 0xea5d));

}

HE_END_NAMESPACE

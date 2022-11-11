#include "HGradientThemeStyle_p.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

HGradientThemeStyle::HGradientThemeStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HGradientThemeStylePrivate)
{
}

HGradientThemeStyle::HGradientThemeStyle(HGradientThemeStylePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HGradientThemeStyle::~HGradientThemeStyle()
{
}

void HGradientThemeStyle::initialize(QVariantMap /*param*/)
{

}

QString HGradientThemeStyle::typeName()
{
    return "HGradientThemeStyle";
}

QString HGradientThemeStyle::toStyleSheet(QVariantMap param)
{
    auto topRadius = param.value("topRadius", 5).toInt();
    auto borderColor = param.value("borderColor", "#000000").toString();
    auto backgroundStartColor = param.value("backgroundStartColor", "#1ABC9C").toString();
    auto backgroundEndColor = param.value("backgroundEndColor", "#FFFFFF").toString();

    return QString("QWidget { "
                   "border-top-left-radius:%1px;"
                   "border-top-right-radius:%1px;"
                   "border-width:2px;"
                   "border-style:solid;"
                   "border-color:%2;"
                   "background-color:qlineargradient(x1:0, y1:0 , x2:0 ,y2:1 stop:0 %3 ,stop:1 %4);}")
        .arg(topRadius)
        .arg(borderColor)
        .arg(backgroundStartColor)
        .arg(backgroundEndColor);
}

void HGradientThemeStyle::setStyle(QWidget *obj, int topRadius, const QString &borderColor, const QString &backgroundStartColor, const QString &backgroundEndColor)
{
    QVariantMap param;
    param["topRadius"] = topRadius;
    param["borderColor"] = borderColor;
    param["backgroundStartColor"] = backgroundStartColor;
    param["backgroundEndColor"] = backgroundEndColor;
    obj->setStyleSheet(toStyleSheet(param));
}

HE_END_NAMESPACE

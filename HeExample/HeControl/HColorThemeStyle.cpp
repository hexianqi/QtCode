#include "HColorThemeStyle_p.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

HColorThemeStyle::HColorThemeStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HColorThemeStylePrivate)
{
}

HColorThemeStyle::HColorThemeStyle(HColorThemeStylePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HColorThemeStyle::~HColorThemeStyle()
{
}

void HColorThemeStyle::initialize(QVariantMap /*param*/)
{

}

QString HColorThemeStyle::typeName()
{
    return "HColorThemeStyle";
}

QString HColorThemeStyle::toStyleSheet(QVariantMap param)
{
    auto topRadius = param.value("topRadius", 5).toInt();
    auto bottomRadius = param.value("bottomRadius", 5).toInt();
    auto topBorderWidth = param.value("topBorderWidth", 1).toInt();
    auto rightBorderWidth = param.value("rightBorderWidth", 1).toInt();
    auto bottomBorderWidth = param.value("bottomBorderWidth", 1).toInt();
    auto leftBorderWidth = param.value("leftBorderWidth", 1).toInt();
    auto borderColor = param.value("borderColor", "#000000").toString();
    auto backgroundColor = param.value("backgroundColor", "#1ABC9C").toString();

    return QString("QWidget { "
                   "border-top-left-radius:%1px;"
                   "border-top-right-radius:%1px;"
                   "border-bottom-left-radius:%2px;"
                   "border-bottom-right-radius:%2px;"
                   "border-width: %3px %4px %5px %6px;"
                   "border-style: solid;"
                   "border-color:%7;"
                   "background-color:%8;}")
        .arg(topRadius)
        .arg(bottomRadius)
        .arg(topBorderWidth)
        .arg(rightBorderWidth)
        .arg(bottomBorderWidth)
        .arg(leftBorderWidth)
        .arg(borderColor)
        .arg(backgroundColor);
}

void HColorThemeStyle::setStyle(QWidget *obj, int topRadius, int bottomRadius, int topBorderWidth, int rightBorderWidth, int bottomBorderWidth, int leftBorderWidth, const QString &borderColor, const QString &backgroundColor)
{
    QVariantMap param;
    param["topRadius"] = topRadius;
    param["bottomRadius"] = bottomRadius;
    param["topBorderWidth"] = topBorderWidth;
    param["rightBorderWidth"] = rightBorderWidth;
    param["bottomBorderWidth"] = bottomBorderWidth;
    param["leftBorderWidth"] = leftBorderWidth;
    param["borderColor"] = borderColor;
    param["backgroundColor"] = backgroundColor;
    obj->setStyleSheet(toStyleSheet(param));
}


HE_END_NAMESPACE

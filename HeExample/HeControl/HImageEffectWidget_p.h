#ifndef HIMAGEEFFECTWIDGET_P_H
#define HIMAGEEFFECTWIDGET_P_H

#include "HImageEffectWidget.h"
#include <QtCore/QMap>

class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class IEffectFactory;

class HImageEffectWidgetPrivate
{
public:
    double factor;
    QString imageName1;
    QString imageName2;
    QPixmap pixmap1;
    QPixmap pixmap2;

public:
    QPropertyAnimation *animation = nullptr;
    IShaderEffect *effect = nullptr;
    IEffectFactory *factory = nullptr;
    QMap<QString, IShaderEffect *> effectCache;
};

HE_CONTROL_END_NAMESPACE

#endif // HIMAGEEFFECTWIDGET_P_H

/***************************************************************************************************
**      2019-07-25  HSplitEffect
***************************************************************************************************/

#ifndef HSPLITEFFECT_H
#define HSPLITEFFECT_H

#include "HAbstractShaderEffect.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSplitEffectPrivate;

class HSplitEffect : public HAbstractShaderEffect
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSplitEffect)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(SplitStyle splitStyle READ splitStyle WRITE setSplitStyle)

public:
    enum SplitStyle
    {
        SplitStyle_OutsideToInside,
        SplitStyle_InsideToOutside
    };
    Q_ENUM(SplitStyle)

public:
    explicit HSplitEffect(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, const QRect &rect, const QPixmap &pixmap) override;

public:
    Qt::Orientation orientation() const;
    SplitStyle splitStyle() const;

public slots:
    void setOrientation(Qt::Orientation value);
    void setSplitStyle(SplitStyle value);

protected:
    HSplitEffect(HSplitEffectPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HSPLITEFFECT_H

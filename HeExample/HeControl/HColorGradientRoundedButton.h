/***************************************************************************************************
**      2022-11-22  HColorGradientRoundedButton
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QAbstractButton>

HE_BEGIN_NAMESPACE

class HColorGradientRoundedButtonPrivate;

struct HDoubleColor
{
    HDoubleColor(QColor frist = Qt::red, QColor second = Qt::blue);

public:
    bool operator!=(const HDoubleColor &);
    bool operator==(const HDoubleColor &);

public:
    QColor frist;
    QColor second;
};

class HColorGradientRoundedButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(HDoubleColor currentColor READ currentColor WRITE setCurrentColor)

public:
    explicit HColorGradientRoundedButton(QWidget *parent = nullptr);
    ~HColorGradientRoundedButton() override;

public:
    HDoubleColor currentColor() const;
    void setCurrentColor(const HDoubleColor &);

protected:
    void paintEvent(QPaintEvent *)override;
    void enterEvent(QEvent *)override;
    void leaveEvent(QEvent *)override;

protected:
    HColorGradientRoundedButton(HColorGradientRoundedButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void init();

protected:
    QScopedPointer<HColorGradientRoundedButtonPrivate> d_ptr;
};

HE_END_NAMESPACE

#ifdef HE_NAMESPACE
    Q_DECLARE_METATYPE(HE_NAMESPACE::HDoubleColor);
#else
    Q_DECLARE_METATYPE(HDoubleColor);
#endif

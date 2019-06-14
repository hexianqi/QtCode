/***************************************************************************************************
**      2019-06-12  HAbstractStyle  抽象样式。
***************************************************************************************************/

#ifndef HABSTRACTSTYLE_H
#define HABSTRACTSTYLE_H

#include "IStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractStylePrivate;

class HAbstractStyle : public IStyle
{
    Q_OBJECT

public:
    explicit HAbstractStyle(QObject *parent = nullptr);
    ~HAbstractStyle() override;

public:
    void initialize(QVariantMap param) override;

protected:
    HAbstractStyle(HAbstractStylePrivate &p, QObject *parent = nullptr);

protected:
    virtual QVariant data(QString type, QVariantMap param, QVariant defaultValue = QVariant());

protected:
    QScopedPointer<HAbstractStylePrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTSTYLE_H

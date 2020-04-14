/***************************************************************************************************
**      2019-06-12  HAbstractCustomStyle 抽象样式。
***************************************************************************************************/

#ifndef HABSTRACTCUSTOMSTYLE_H
#define HABSTRACTCUSTOMSTYLE_H

#include "ICustomStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractCustomStylePrivate;

class HAbstractCustomStyle : public ICustomStyle
{
    Q_OBJECT

public:
    explicit HAbstractCustomStyle(QObject *parent = nullptr);
    ~HAbstractCustomStyle() override;

public:
    void initialize(QVariantMap param) override;
    QString toStyleSheet() override;

protected:
    HAbstractCustomStyle(HAbstractCustomStylePrivate &p, QObject *parent = nullptr);

protected:
    virtual QVariant data(const QString &type, const QVariantMap &param, const QVariant &defaultValue = QVariant());

protected:
    QScopedPointer<HAbstractCustomStylePrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTCUSTOMSTYLE_H

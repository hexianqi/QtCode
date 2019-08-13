/***************************************************************************************************
**      2019-07-19  HQssStyle Qss样式
***************************************************************************************************/

#ifndef HQSSSTYLE_H
#define HQSSSTYLE_H

#include "IQssStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class HQssStylePrivate;

class HQssStyle : public IQssStyle
{
    Q_OBJECT

public:
    explicit HQssStyle(QObject *parent = nullptr);
    ~HQssStyle() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QPalette toPalette();
    QString toStyleSheet() override;
    QStringList keys() override;
    bool selectStyle(QString value) override;

protected:
    HQssStyle(HQssStylePrivate &p, QObject *parent = nullptr);

protected:
    void addStyle(QString key, QString fileName);

protected:
    QScopedPointer<HQssStylePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HQSSSTYLE_H

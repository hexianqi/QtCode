#include "HAbstractCustomStyle_p.h"

HE_BEGIN_NAMESPACE

HAbstractCustomStyle::HAbstractCustomStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractCustomStylePrivate)
{
}

HAbstractCustomStyle::HAbstractCustomStyle(HAbstractCustomStylePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractCustomStyle::~HAbstractCustomStyle() = default;

void HAbstractCustomStyle::initialize(QVariantMap param)
{
    d_ptr->param = param;
}

QString HAbstractCustomStyle::toStyleSheet(QVariantMap param)
{
    auto list = QStringList() << pushButton(param)
                              << lineEdit(param)
                              << progressBar(param)
                              << slider(param)
                              << radioButton(param)
                              << checkBox(param)
                              << scrollBar(param);
    return list.join("\n");
}

QVariant HAbstractCustomStyle::data(const QString &type, const QVariantMap &param, const QVariant &defaultValue)
{
    if (param.contains(type))
        return param.value(type);
    return d_ptr->param.value(type, defaultValue);
}

HE_END_NAMESPACE

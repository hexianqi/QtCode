#include "HAbstractCustomStyle_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractCustomStyle::HAbstractCustomStyle(QObject *parent) :
    ICustomStyle(parent),
    d_ptr(new HAbstractCustomStylePrivate)
{
}

HAbstractCustomStyle::HAbstractCustomStyle(HAbstractCustomStylePrivate &p, QObject *parent) :
    ICustomStyle(parent),
    d_ptr(&p)
{
}

HAbstractCustomStyle::~HAbstractCustomStyle() = default;

void HAbstractCustomStyle::initialize(QVariantMap param)
{
    d_ptr->globalParam = param;
}

QString HAbstractCustomStyle::toStyleSheet()
{
    QStringList list;
    list << pushButton()
         << lineEdit()
         << progressBar()
         << slider()
         << radioButton()
         << checkBox()
         << scrollBar();
    return list.join("\n");
}

QVariant HAbstractCustomStyle::data(const QString &type, const QVariantMap &param, const QVariant &defaultValue)
{
    if (param.contains(type))
        return param.value(type);
    return d_ptr->globalParam.value(type, defaultValue);
}

HE_CONTROL_END_NAMESPACE

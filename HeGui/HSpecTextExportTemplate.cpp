#include "HSpecTextExportTemplate_p.h"
#include "HeCore/HCore.h"
#include "HeData/HDataHelper.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

HSpecTextExportTemplate::HSpecTextExportTemplate(QObject *parent) :
    HAbstractTextExportTemplate(*new HSpecTextExportTemplatePrivate, parent)
{
}

HSpecTextExportTemplate::HSpecTextExportTemplate(HSpecTextExportTemplatePrivate &p, QObject *parent) :
    HAbstractTextExportTemplate(p, parent)
{
}

HSpecTextExportTemplate::~HSpecTextExportTemplate() = default;

QString HSpecTextExportTemplate::typeName()
{
    return "HSpecTextExportTemplate";
}

QString HSpecTextExportTemplate::content(bool title)
{
    Q_D(HSpecTextExportTemplate);
    if (d->data.type() == QVariant::List)
        return parse(d->data.toList(), title);
    if (d->data.type() == QVariant::Map)
        return parse(d->data.toMap(), title);
    return QString();
}

QString HSpecTextExportTemplate::parse(QVariantMap data, bool title)
{
    Q_D(HSpecTextExportTemplate);
    QString text;
    QStringList list;
    auto types = d->types;
    types.removeAll("[光谱能量曲线]");

    if (title)
        text += HCore::toCaptionUnit(types).join("\t") + "\n";
    for (auto t : types)
        list << HCore::toString(t, HDataHelper::derive(t, data));
    text += list.join("\t") + "\n";
    if (d->types.contains("[光谱能量曲线]"))
        text += parse(data.value("[光谱能量曲线]").value<QPolygonF>()) + "\n";
    return text;
}

QString HSpecTextExportTemplate::parse(QVariantList data, bool title)
{
    Q_D(HSpecTextExportTemplate);
    QString text;
    QStringList list1, list2;
    auto types = d->types;
    types.removeAll("[光谱能量曲线]");

    if (title)
        text += "Index\t" + HCore::toCaptionUnit(types).join("\t") + "\n";
    for (int i = 0; i < data.count(); i++)
    {
        auto value = data.at(i).toMap();
        list2.clear();
        for (auto t : types)
            list2 << HCore::toString(t, HDataHelper::derive(t, value));
        list1 << QString("%1\t").arg(i + 1) + list2.join("\t");
    }
    text += list1.join("\n") + "\n";
    return text;
}

QString HSpecTextExportTemplate::parse(QPolygonF value)
{
    QString text;
    QStringList list;
    text += HCore::toCaptionUnit("[光谱波长]") + "\t" + HCore::toCaptionUnit("[光谱能量百分比]") + "\n";
    for (int i = 0; i < value.size(); i += 10)
        list << HCore::toString("[光谱波长]", value.at(i).x()) + "\t" +  HCore::toString("[光谱能量百分比]", value.at(i).y());
    text += list.join("\n");
    return text;
}

HE_END_NAMESPACE

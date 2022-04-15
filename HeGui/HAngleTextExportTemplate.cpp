#include "HAngleTextExportTemplate_p.h"
#include "HeCore/HCore.h"
#include "HeData/HDataHelper.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

HAngleTextExportTemplate::HAngleTextExportTemplate(QObject *parent) :
    HAbstractTextExportTemplate(*new HAngleTextExportTemplatePrivate, parent)
{
}

HAngleTextExportTemplate::HAngleTextExportTemplate(HAngleTextExportTemplatePrivate &p, QObject *parent) :
    HAbstractTextExportTemplate(p, parent)
{
}

HAngleTextExportTemplate::~HAngleTextExportTemplate() = default;

QString HAngleTextExportTemplate::typeName()
{
    return "HAngleTextExportTemplate";
}

QString HAngleTextExportTemplate::content(bool title)
{
    Q_D(HAngleTextExportTemplate);
    QString text;
    QStringList list;
    auto data = d->data.toMap();
    auto poly = data.value("[光强角度分布]").value<QPolygonF>();
    auto types = d->types;
    types.removeAll("[光强角度分布]");

    if (title)
        text += HCore::toCaptionUnit(types).join("\t") + "\n";
    for (auto t : types)
        list << HCore::toString(t, HDataHelper::derive(t, data));
    text += list.join("\t") + "\n";

    if (d->types.contains("[光强角度分布]"))
    {
        list.clear();
        text += HCore::toCaptionUnit("[角度]") + "\t" + HCore::toCaptionUnit("[光强度]") + "\n";
        for (auto p : poly)
            list << HCore::toString("[角度]", p.x()) + "\t" +  HCore::toString("[光强度]", p.y());
        text += list.join("\n");
    }
    return text;
}

HE_END_NAMESPACE

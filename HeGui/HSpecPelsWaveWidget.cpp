#include "HSpecPelsWaveWidget_p.h"
#include "HeCore/HCore.h"
#include "HeData/HSpecPelsWave.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

HSpecPelsWaveWidgetPrivate::HSpecPelsWaveWidgetPrivate(HSpecPelsWave *d)
{
    data = d;
}

HSpecPelsWaveWidget::HSpecPelsWaveWidget(HSpecPelsWave *data, QWidget *parent)
    : HEntireTableWidget(*new HSpecPelsWaveWidgetPrivate(data), parent)
{
    init();
    showData();
}

HSpecPelsWaveWidget::~HSpecPelsWaveWidget()
{
}

void HSpecPelsWaveWidget::saveData()
{
    Q_D(HSpecPelsWaveWidget);
    QPolygonF poly;

    for (int i = 0; i < rowCount(); i++)
        poly.append(QPointF(item(i, 0)->text().toDouble(), item(i, 1)->text().toDouble()));
    d->data->setPelsWave(poly);
    showData();
}

void HSpecPelsWaveWidget::showData()
{
    Q_D(HSpecPelsWaveWidget);
    auto poly = d->data->pelsWave();
    auto size = poly.size();

    clearContents();
    setRowCount(size);
    for (int i = 0; i < size; i++)
        setRow(i, QStringList() << toString("[光谱像元]", poly[i].x()) << toString("[光谱波长]", poly[i].y()));
}

void HSpecPelsWaveWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(QStringList() << "[光谱像元]" << "[光谱波长]");
    setItemDelegate(delegate);
    setHorizontalHeaderLabels(QStringList() << tr("像元") << tr("波长"));
}

HE_GUI_END_NAMESPACE

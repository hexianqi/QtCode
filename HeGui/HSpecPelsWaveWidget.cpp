#include "HSpecPelsWaveWidget_p.h"
#include "HeCore/HCore.h"
#include "HeData/HSpecPelsWave.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecPelsWaveWidget::HSpecPelsWaveWidget(QWidget *parent) :
    HEntireTableWidget(*new HSpecPelsWaveWidgetPrivate, parent)
{
    init();
}

HSpecPelsWaveWidget::~HSpecPelsWaveWidget()
{
    qDebug() << __func__;
}

void HSpecPelsWaveWidget::setData(HSpecPelsWave *p)
{
    Q_D(HSpecPelsWaveWidget);
    d->data = p;
    showData();
}

void HSpecPelsWaveWidget::saveData()
{
    Q_D(HSpecPelsWaveWidget);
    QPolygonF poly;

    for (int i = 0; i < rowCount(); i++)
        poly << QPointF(item(i, 0)->text().toDouble(), item(i, 1)->text().toDouble());
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
        setRow(i, QStringList() << HCore::toString("[光谱像元]", poly[i].x()) << HCore::toString("[光谱波长]", poly[i].y()));
}

void HSpecPelsWaveWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(QStringList() << "[光谱像元]" << "[光谱波长]");
    setItemDelegate(delegate);
    setHorizontalHeaderLabels(QStringList() << tr("像元") << tr("波长"));
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setWindowTitle(tr("光谱像元波长"));
}

HE_GUI_END_NAMESPACE

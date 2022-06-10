#include "HSpecPelsWaveWidget_p.h"
#include "HeCore/HCore.h"
#include "HeData/HSpecPelsWave.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HEntireTableWidget.h"
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HSpecPelsWaveWidget::HSpecPelsWaveWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSpecPelsWaveWidgetPrivate)
{
    init();
}

HSpecPelsWaveWidget::~HSpecPelsWaveWidget() = default;

void HSpecPelsWaveWidget::setData(HSpecPelsWave *p)
{
    d_ptr->data = p;
    showData();
}

void HSpecPelsWaveWidget::saveData()
{
    QPolygonF poly;
    for (int i = 0; i < d_ptr->tableWidget->rowCount(); i++)
        poly << QPointF(d_ptr->tableWidget->item(i, 0)->text().toDouble(), d_ptr->tableWidget->item(i, 1)->text().toDouble());
    d_ptr->data->setPelsWave(poly);
    showData();
}

void HSpecPelsWaveWidget::showData()
{
    auto poly = d_ptr->data->pelsWave();
    auto size = poly.size();
    d_ptr->spinBox->setValue(size);
    for (int i = 0; i < size; i++)
        d_ptr->tableWidget->setRow(i, QStringList() << HCore::toString("[光谱像元]", poly[i].x()) << HCore::toString("[光谱波长]", poly[i].y()));
}

void HSpecPelsWaveWidget::setRowCount(int value)
{
    auto previous = d_ptr->tableWidget->rowCount();
    d_ptr->tableWidget->setRowCount(value);
    for (int i = previous; i < value; i++)
        d_ptr->tableWidget->setRow(i, QStringList() << "0" << "500.0");
}

void HSpecPelsWaveWidget::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(QStringList() << "[光谱像元]" << "[光谱波长]");
    d_ptr->tableWidget = new HEntireTableWidget;
    d_ptr->tableWidget->setItemDelegate(delegate);
    d_ptr->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("像元") << tr("波长"));
    d_ptr->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    d_ptr->spinBox = new QSpinBox();
    d_ptr->spinBox->setAlignment(Qt::AlignCenter);
    d_ptr->spinBox->setRange(2, 10);
    auto label = new QLabel();
    label->setText(tr("项数："));
    label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    auto layout = new QGridLayout(this);
    layout->addWidget(label, 1, 0, 1, 1);
    layout->addWidget(d_ptr->spinBox, 1, 1, 1, 1);
    layout->addWidget(d_ptr->tableWidget, 0, 0, 1, 2);
    connect(d_ptr->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &HSpecPelsWaveWidget::setRowCount);
    setWindowTitle(tr("光谱像元波长"));
}

HE_END_NAMESPACE

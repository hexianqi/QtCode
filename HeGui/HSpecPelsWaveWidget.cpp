#include "HSpecPelsWaveWidget_p.h"
#include "HeCore/HCore.h"
#include "HeData/HSpecPelsWave.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HePlugin/HEntireTableWidget.h"
#include <QtWidgets/QCheckBox>
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
    d_ptr->data->setData("[线性策略]", d_ptr->checkBox->isChecked() ? "HPolynomStrategy" : "HPlineStrategy");
    d_ptr->data->setData("[线性多项式项数]", d_ptr->spinBox2->value());
    d_ptr->data->setPoints(poly);
    showData();
}

void HSpecPelsWaveWidget::showData()
{
    auto poly = d_ptr->data->points();
    auto size = poly.size();
    d_ptr->checkBox->setChecked(d_ptr->data->data("[线性策略]").toString() == "HPolynomStrategy");
    d_ptr->spinBox->setValue(size);
    d_ptr->spinBox2->setValue(d_ptr->data->data("[线性多项式项数]").toInt());
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
    d_ptr->checkBox = new QCheckBox();
    d_ptr->checkBox->setText(tr("多项式项数："));
    d_ptr->spinBox = new QSpinBox();
    d_ptr->spinBox->setAlignment(Qt::AlignCenter);
    d_ptr->spinBox->setRange(2, 20);
    d_ptr->spinBox2 = new QSpinBox();
    d_ptr->spinBox2->setAlignment(Qt::AlignCenter);
    d_ptr->spinBox2->setRange(2, 10);
    auto label = new QLabel();
    label->setText(tr("行数："));
    label->setAlignment(Qt::AlignRight| Qt::AlignTrailing | Qt::AlignVCenter);
    auto layout = new QGridLayout(this);
    layout->addWidget(label, 1, 0, 1, 1);
    layout->addWidget(d_ptr->checkBox, 1, 2, 1, 1);
    layout->addWidget(d_ptr->spinBox, 1, 1, 1, 1);
    layout->addWidget(d_ptr->spinBox2, 1, 3, 1, 1);
    layout->addWidget(d_ptr->tableWidget, 0, 0, 1, 4);
    connect(d_ptr->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &HSpecPelsWaveWidget::setRowCount);
    setWindowTitle(tr("光谱像元波长"));
}

HE_END_NAMESPACE

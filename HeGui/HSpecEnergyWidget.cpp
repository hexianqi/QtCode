#include "HSpecEnergyWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include "HePlugin/HProgressBar.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include <QtGui/QIcon>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecEnergyWidgetPrivate::HSpecEnergyWidgetPrivate()
{
    toolTipTypes = QStringList() << "[峰值波长]" << "[主波长]" << "[色温]" << "[色坐标]" << "[显色指数]";
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecEnergyWidget::HSpecEnergyWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new HSpecEnergyWidgetPrivate)
{
    init();
}

HSpecEnergyWidget::HSpecEnergyWidget(HSpecEnergyWidgetPrivate &p, QWidget *parent)
    : QWidget(parent)
    , d_ptr(&p)
{
    init();
}

HSpecEnergyWidget::~HSpecEnergyWidget()
{
    qDebug() << __func__;
}

void HSpecEnergyWidget::initCoordinate()
{
    d_ptr->specWidget->setWaveRange(d_ptr->testSpec->data("[光谱波长范围]").toPointF());
}

void HSpecEnergyWidget::refreshWidget()
{
    QString tip;
    int state = d_ptr->testSpec->data("[采样溢出状态]").toInt();
    d_ptr->progressBar->setValue(d_ptr->testSpec->data("[采样比率]").toInt());

    if (state == 0)
    {
        d_ptr->specWidget->addPolygon(0, d_ptr->testSpec->energy());
        tip = d_ptr->testSpec->toHtmlTable(d_ptr->toolTipTypes, Qt::white);
    }
    else if (state < 0)
        d_ptr->specWidget->setCenter(tr("光谱采样数值太小!"), Qt::green, Qt::black);
    else
        d_ptr->specWidget->setCenter(tr("光谱采样数值太大!"), Qt::red, Qt::white);
    d_ptr->specWidget->setToolTip(tip);
}

void HSpecEnergyWidget::init()
{
    d_ptr->specWidget = new HSpecDiagramWidget;
    d_ptr->progressBar = new HProgressBar;
    d_ptr->progressBar->setOrientation(Qt::Vertical);
    d_ptr->progressBar->setRange(0, 100);
    d_ptr->progressBar->setValue(0);
    d_ptr->progressBar->setToolTip(tr("采样比率"));
    auto margins = d_ptr->specWidget->margins();
    d_ptr->progressLayout = new QHBoxLayout;
    d_ptr->progressLayout->setSpacing(2);
    d_ptr->progressLayout->setContentsMargins(5, margins.top(), 5, margins.bottom());
    d_ptr->progressLayout->addWidget(d_ptr->progressBar);
    auto layout = new QGridLayout(this);
    layout->setSpacing(9);
    layout->addLayout(d_ptr->progressLayout, 0, 0);
    layout->addWidget(d_ptr->specWidget, 0, 1);
    connect(d_ptr->specWidget, &HSpecDiagramWidget::marginChanged, this, [=](QMargins m){ d_ptr->progressLayout->setContentsMargins(5, m.top(), 5, m.bottom()); });
    initCoordinate();
    setAutoFillBackground(true);
    setWindowIcon(QIcon(":/image/Spectrum.png"));
    setWindowTitle(tr("相对光谱能量分布"));
}

HE_GUI_END_NAMESPACE

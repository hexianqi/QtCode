#include "HSpecEnergyWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HProgressBar.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include <QtCore/QSettings>
#include <QtGui/QIcon>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HSpecEnergyWidgetPrivate::HSpecEnergyWidgetPrivate()
{
    toolTipTypes = QStringList() << "[峰值波长]" << "[主波长]" << "[色温]" << "[色坐标]" << "[显色指数Ra]";
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HSpecEnergyWidget::HSpecEnergyWidget(QWidget *parent):
    QWidget(parent),
    d_ptr(new HSpecEnergyWidgetPrivate)
{
    init();
}

HSpecEnergyWidget::HSpecEnergyWidget(HSpecEnergyWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HSpecEnergyWidget::~HSpecEnergyWidget()
{
    writeSettings();
}

void HSpecEnergyWidget::initCoordinate()
{
    d_ptr->specWidget->setWaveRange(d_ptr->testData->data("[光谱波长范围]").toPointF());
}

void HSpecEnergyWidget::refreshWidget()
{
    QString tip;

    for (auto bar : d_ptr->progressBars)
        bar->setValue(d_ptr->testData->data(bar->property("showType").toString()).toDouble());

    int state = d_ptr->testData->data("[光谱采样溢出状态]").toInt();
    if (state == 0)
    {
        d_ptr->specWidget->addPolygon(0, d_ptr->testData->data("[光谱能量曲线]").value<QPolygonF>());
        tip = d_ptr->testData->toHtmlTable(d_ptr->toolTipTypes, Qt::white);
    }
    else if (state < 0)
        d_ptr->specWidget->setCenter(tr("光谱采样数值太小!"), Qt::green, Qt::black);
    else
        d_ptr->specWidget->setCenter(tr("光谱采样数值太大!"), Qt::red, Qt::white);
    d_ptr->specWidget->setToolTip(tip);
}

void HSpecEnergyWidget::addProgressBar(const QString &type)
{
    if (d_ptr->progressBars.contains(type))
        return;
    auto bar = new HProgressBar(this);
    bar->setOrientation(Qt::Vertical);
    bar->setRange(0, 100);
    bar->setValue(0);
    bar->setToolTip(HCore::toCaption(type));
    bar->setProperty("showType", type);
    d_ptr->progressBars.insert(type, bar);
    d_ptr->progressLayout->addWidget(bar);
}

void HSpecEnergyWidget::setProgressBarVisible(const QString &type, bool b)
{
    if (!d_ptr->progressBars.contains(type))
        return;
    d_ptr->progressBars.value(type)->setVisible(b);
}

void HSpecEnergyWidget::init()
{
    readSettings();
    d_ptr->specWidget = new HSpecDiagramWidget;
    d_ptr->specWidget->setDrawRibbon(d_ptr->ribbon);
    auto margins = d_ptr->specWidget->margins();
    d_ptr->progressLayout = new QHBoxLayout;
    d_ptr->progressLayout->setSpacing(2);
    d_ptr->progressLayout->setContentsMargins(5, margins.top(), 5, margins.bottom());
    addProgressBar("[光谱采样比率]");
    auto layout = new QGridLayout(this);
    layout->setSpacing(9);
    layout->addLayout(d_ptr->progressLayout, 0, 0);
    layout->addWidget(d_ptr->specWidget, 0, 1);
    connect(d_ptr->specWidget, &HSpecDiagramWidget::marginChanged, this, [=](QMargins m){ d_ptr->progressLayout->setContentsMargins(5, m.top(), 5, m.bottom()); });
    initCoordinate();
    setWindowIcon(QIcon(":/image/Spectrum.png"));
    setWindowTitle(tr("相对光谱功率分布"));
}

void HSpecEnergyWidget::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("SpecEnergyWidget");
    d_ptr->ribbon = settings->value("Ribbon", true).toBool();
    settings->endGroup();
}

void HSpecEnergyWidget::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("SpecEnergyWidget");
    settings->setValue("Ribbon", d_ptr->ribbon);
    settings->endGroup();
}

HE_END_NAMESPACE

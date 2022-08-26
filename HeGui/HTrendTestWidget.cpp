#include "HTrendTestWidget_p.h"
#include "HTrendTestSetWidget.h"
#include "HSpecEnergyWidget.h"
#include "HResultTableWidget.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IDataFactory.h"
#include "HeData/ITextStream.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDynamicChartView.h"
#include <QtCore/QSettings>
#include <QtCore/QDateTime>
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>

HE_BEGIN_NAMESPACE

HTrendTestWidgetPrivate::HTrendTestWidgetPrivate()
{
    stream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createTextStream("HTextStream");
    stream->setFileFilter("Excel files (*.xls)");
    optional = HAppContext::getContextValue<QStringList>("TrendOptional");
    displays = QStringList() << "[测量日期]" << "[测量时间]" << optional;
    baseY.insert("[色纯度]", -1);
    baseY.insert("[色坐标x]", -1);
    baseY.insert("[色坐标y]", -1);
}

HTrendTestWidget::HTrendTestWidget(QWidget *parent) :
    HTestWidget(*new HTrendTestWidgetPrivate, parent)
{
    init();
    setWindowTitle(tr("老化测试"));
}

HTrendTestWidget::~HTrendTestWidget() = default;

QString HTrendTestWidget::typeName()
{
    return "HTrendTestWidget";
}

void HTrendTestWidget::createAction()
{
    Q_D(HTrendTestWidget);
    HTestWidget::createAction();
    d->displayGroup = new QActionGroup(this);
    for (auto s : d->optional)
    {
        auto action = new QAction;
        action->setCheckable(true);
        action->setText(HCore::toCaption(s));
        action->setData(s);
        d->displayGroup->addAction(action);
    }
    connect(d->displayGroup, &QActionGroup::triggered, this, &HTrendTestWidget::changeDisplay);
}

void HTrendTestWidget::createWidget()
{
    Q_D(HTrendTestWidget);
    d->testSetWidget = new HTrendTestSetWidget;
    d->energyWidget = new HSpecEnergyWidget;
    d->energyWidget->addProgressBar("[光采样比率]");
    d->tableWidget = new HResultTableWidget;
    d->chartView = new HDynamicChartView;
}

void HTrendTestWidget::createMenu()
{

}

void HTrendTestWidget::createToolBar()
{
    Q_D(HTrendTestWidget);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->setIconSize(QSize(40, 40));
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBars << toolBar1 << toolBar2;
}

void HTrendTestWidget::initWidget()
{
    Q_D(HTrendTestWidget);
    auto layout = new QGridLayout(this);
    auto tabWidget = new QTabWidget;
    auto splitter = new QSplitter(Qt::Vertical);
    d->tableWidget->setDisplay(d->displays);
    d->tableWidget->setSelected(d->selected);
    d->tableWidget->addAction(d->actionClear);
    HPluginHelper::addSeparator(d->chartView);
    d->chartView->addActions(d->displayGroup->actions());
    tabWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    tabWidget->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget->addTab(d->chartView, tr("趋势曲线"));
    splitter->addWidget(tabWidget);
    splitter->addWidget(d->tableWidget);
    splitter->setHandleWidth(15);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
    layout->addWidget(splitter);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTrendTestWidget::handleStateChanged);
    connect(d->testSetWidget, &ITestSetWidget::resultChanged, this, &HTrendTestWidget::handleResultChanged);
    changeDisplay(d->displayGroup->actions().first());
}

void HTrendTestWidget::clearResult()
{
    Q_D(HTrendTestWidget);
    d->interval = 0.0;
    d->result.clear();
    d->tableWidget->clearResult();
    d->chartView->clear();
}

void HTrendTestWidget::exportExcel()
{
    Q_D(HTrendTestWidget);
    if (d->result.isEmpty())
        return;

    QString text;
    text += "Index\t" + HCore::toCaptionUnit(d->displays).join("\t") + "\n";
    for (int i = 0; i < d->result.count(); i++)
    {
        QStringList list;
        for (auto t : d->displays)
            list << HCore::toString(t, d->result.at(i).value(t));
        text += QString("%1\t").arg(i + 1) + list.join("\t") +  + "\n";
    }
    d->stream->setContent(text);
    d->stream->saveAsFile();
}

void HTrendTestWidget::readSettings()
{
    Q_D(HTrendTestWidget);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TrendTestWidget");
    d->selected = settings->value("TableSelected", d->displays).toStringList();
    settings->endGroup();
}

void HTrendTestWidget::writeSettings()
{
    Q_D(HTrendTestWidget);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("TrendTestWidget");
    settings->setValue("TableSelected", d->tableWidget->selected());
    settings->endGroup();
}

void HTrendTestWidget::changeDisplay(QAction *action)
{
    Q_D(HTrendTestWidget);
    if (action == nullptr)
        return;
    action->setChecked(true);
    auto type = action->data().toString();
    if (type == d->current)
        return;
    d->current = type;
    QPolygonF poly;
    for (int i = 0; i < d->result.size(); i++)
        poly.append(QPointF(d->interval * (i + 1), d->result.at(i).value(type).toDouble()));
    d->chartView->replace(poly, true, 1, d->baseY.value(type, 1));
    d->chartView->chart()->setTitle(tr("%1 随时间变化趋势").arg(HCore::toCaption(type)));
}

void HTrendTestWidget::handleStateChanged(bool b)
{
    Q_D(HTrendTestWidget);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
}

void HTrendTestWidget::handleResultChanged(HActionType, bool first)
{
    Q_D(HTrendTestWidget);
    if (first)
    {
        clearResult();
        d->interval = d->testSetWidget->data("[测量间隔]").toDouble();
    }
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
    d->result.append(d->testData->select(d->displays));
    d->energyWidget->refreshWidget();
    d->tableWidget->refreshResult(true);
    d->chartView->addPoint(d->interval * d->result.size(), d->testData->data(d->current).toDouble());
}

HE_END_NAMESPACE

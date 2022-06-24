#include "HSpecChromatismChartView_p.h"
#include "IGuiFactory.h"
#include "HAction.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestData.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/IChromatism.h"
#include "HeData/IChromatismItem.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QMenu>

HE_BEGIN_NAMESPACE

HSpecChromatismChartViewPrivate::HSpecChromatismChartViewPrivate()
{
    factory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HSpecChromatismChartView::HSpecChromatismChartView(QWidget *parent) :
    HChromatismChartView(*new HSpecChromatismChartViewPrivate, parent)
{
    init();
}

HSpecChromatismChartView::~HSpecChromatismChartView() = default;

void HSpecChromatismChartView::initMenuShow()
{
    Q_D(HSpecChromatismChartView);
    d->menuShow->clear();
    auto datas = d->configManage->chromatismCollection();
    if (datas == nullptr || datas->isEmpty())
        return;
    auto data = datas->value(datas->useIndex());
    if (data == nullptr)
        return;
    auto group = new QActionGroup(this);
    for (auto v : data->values())
         group->addAction(v->data("[标题]").toString())->setData(v->data());
    connect(group, &QActionGroup::triggered, this, &HSpecChromatismChartView::showChromatism);
    d->menuShow->addActions(group->actions());
    if (!group->actions().isEmpty())
        showChromatism(group->actions().at(0));
}

void HSpecChromatismChartView::refreshWidget()
{
    Q_D(HSpecChromatismChartView);
    setData(d->testData->data("[色容差详情]").toMap());
}

void HSpecChromatismChartView::init()
{
    Q_D(HSpecChromatismChartView);
    HChromatismChartView::init();
    d->menuShow = new QMenu(tr("显示"), this);
    HPluginHelper::addSeparator(this);
    addAction(d->factory->createAction(tr("配置(&E)..."), "HChromatismEditHandler"));
    addAction(d->factory->createAction(tr("选择(&S)..."), "HChromatismSelectHandler"));
    addAction(d->menuShow->menuAction());
    initMenuShow();
    setWindowTitle(tr("色容差"));
}

void HSpecChromatismChartView::showChromatism(QAction *p)
{
    if (p == nullptr)
        return;
    setData(p->data().toMap());
}

HE_END_NAMESPACE

#include "HSpecChromatismWidget_p.h"
#include "IGuiFactory.h"
#include "HAction.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IChromatismCollection.h"
#include "HeData/IChromatism.h"
#include "HeData/IChromatismItem.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HChromatismWidget.h"
#include <QtWidgets/QMenu>
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecChromatismWidgetPrivate::HSpecChromatismWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HSpecChromatismWidget::HSpecChromatismWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSpecChromatismWidgetPrivate)
{
    init();
}

HSpecChromatismWidget::~HSpecChromatismWidget()
{
    qDebug() << __func__;
}

void HSpecChromatismWidget::initMenuShow()
{
    d_ptr->menuShow->clear();
    auto datas = d_ptr->configManage->chromatismCollection();
    if (datas == nullptr || datas->isEmpty())
        return;
    auto data = datas->value(datas->useIndex());
    if (data == nullptr)
        return;
    auto group = new QActionGroup(this);
    for (auto v : data->values())
         group->addAction(v->data("[标题]").toString())->setData(v->data());
    connect(group, &QActionGroup::triggered, this, &HSpecChromatismWidget::showChromatism);
    d_ptr->menuShow->addActions(group->actions());
    if (!group->actions().isEmpty())
        showChromatism(group->actions().at(0));
}

void HSpecChromatismWidget::refreshWidget()
{
    d_ptr->chromatismWidget->setData(d_ptr->testData->data("[色容差标准]").toMap());
}

void HSpecChromatismWidget::showChromatism(QAction *p)
{
    if (p == nullptr)
        return;
    d_ptr->chromatismWidget->setData(p->data().toMap());
}

void HSpecChromatismWidget::init()
{
    d_ptr->menuShow = new QMenu(tr("显示"), this);
    d_ptr->chromatismWidget = new HChromatismWidget;
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(d_ptr->chromatismWidget);
    HPluginHelper::addSeparator(d_ptr->chromatismWidget);
    d_ptr->chromatismWidget->addAction(d_ptr->factory->createAction(tr("配置(&E)..."), "HChromatismEditHandler"));
    d_ptr->chromatismWidget->addAction(d_ptr->factory->createAction(tr("选择(&S)..."), "HChromatismSelectHandler"));
    d_ptr->chromatismWidget->addAction(d_ptr->menuShow->menuAction());
    initMenuShow();
    setWindowTitle(tr("色容差"));
}

HE_GUI_END_NAMESPACE

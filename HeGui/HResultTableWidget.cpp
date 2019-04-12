#include "HResultTableWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeController/ITestData.h"
#include "HePlugin/HTypeOptionalDialog.h"
#include <QAction>
#include <QHeaderView>
#include <QDebug>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

HResultTableWidgetPrivate::HResultTableWidgetPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HResultTableWidget::HResultTableWidget(QWidget *parent) :
    HEntireTableWidget(*new HResultTableWidgetPrivate, parent)
{
    init();
}

HResultTableWidget::HResultTableWidget(HResultTableWidgetPrivate &p, QWidget *parent) :
    HEntireTableWidget(p, parent)
{
    init();
}

HResultTableWidget::~HResultTableWidget()
{
    qDebug() << __func__;
}

void HResultTableWidget::setOptionals(QStringList value)
{
    Q_D(HResultTableWidget);
    if (d->optionals == value)
        return;
    d->optionals = value;
    clear();
    setHorizontalHeaderLabels(toCaptionUnit(value));
}

void HResultTableWidget::setSelecteds(QStringList value)
{
    Q_D(HResultTableWidget);
    if (d->selecteds == value)
        return;
    d->selecteds = value;
    for (int i = 0; i < d->optionals.size(); i++)
        setColumnHidden(i, value.contains(d->optionals[i]));
}

void HResultTableWidget::clearResult()
{
    clearContents();
    setRowCount(0);
}

void HResultTableWidget::refreshResult(int row, bool append)
{
    Q_D(HResultTableWidget);
    auto value = d->testData->toString(d->optionals);
    if (append || row >= rowCount())
        insertRow(row, value);
    else
        setRow(row, value);
}

void HResultTableWidget::openOptionalDialog()
{
    Q_D(HResultTableWidget);
    HTypeOptionalDialog dlg(d->selecteds, d->optionals, this);
    if (dlg.exec())
        setSelecteds(dlg.selected());
}

void HResultTableWidget::init()
{
    Q_D(HResultTableWidget);
    d->actionClear = new QAction(QIcon(":/image/Clear.png"), tr("清除结果(&R)"));
    d->actionOptional = new QAction(QIcon(":/image/Options.png"), tr("显示选项(&O)..."));
    addAction(d->actionClear);
    addAction(d->actionOptional);
    connect(d->actionClear, &QAction::triggered, this, &HResultTableWidget::clearResult);
    connect(d->actionOptional, &QAction::triggered, this, &HResultTableWidget::openOptionalDialog);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setVisible(false);
}

HE_GUI_END_NAMESPACE


#include "HResultTableWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HePlugin/HOptionalTableExtend.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>

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

void HResultTableWidget::setDisplay(QStringList value)
{
    Q_D(HResultTableWidget);
    if (d->displays == value)
        return;
    d->displays = value;
    d->optional->setDisplay(value);
    d->optional->setOptional(value);
    setHorizontalHeaderLabels(toCaptionUnit(value));
}

void HResultTableWidget::setSelected(QStringList value)
{
    Q_D(HResultTableWidget);
    d->optional->setSelected(value);
}

void HResultTableWidget::clearResult()
{
    clearContents();
    setRowCount(0);
}

void HResultTableWidget::refreshResult(int row, bool append)
{
    Q_D(HResultTableWidget);
    auto value = d->testData->toString(d->displays);
    if (append || row >= rowCount())
        insertRow(row, value);
    else
        setRow(row, value);

    auto map = d->testData->data("[品质不符合颜色]").toMap();
    for (auto i = map.begin(); i != map.end(); i++)
    {
        auto column = d->displays.indexOf(i.key());
        if (column != -1)
            item(row, column)->setBackgroundColor(i.value().value<QColor>());
    }
}

QStringList HResultTableWidget::selected()
{
    Q_D(HResultTableWidget);
    return d->optional->selected();
}

void HResultTableWidget::init()
{
    Q_D(HResultTableWidget);
    d->optional = new HOptionalTableExtend(this);
    d->optional->setTableView(this);
    d->actionClear = new QAction(QIcon(":/image/Clear.png"), tr("清除结果(&R)"));
    addAction(d->actionClear);
    connect(d->actionClear, &QAction::triggered, this, &HResultTableWidget::clearResult);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setVisible(false);
}

HE_GUI_END_NAMESPACE


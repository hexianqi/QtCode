#include "HResultTableWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/ITestData.h"
#include "HePlugin/HOptionalTableExtend.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QHeaderView>

HE_BEGIN_NAMESPACE

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

HResultTableWidget::~HResultTableWidget() = default;

void HResultTableWidget::setDisplay(const QStringList &value)
{
    Q_D(HResultTableWidget);
    if (d->displays == value)
        return;
    d->displays = value;
    d->optional->setDisplay(value);
    d->optional->setOptional(value);
    setHorizontalHeaderLabels(HCore::toCaptionUnit(value));
}

void HResultTableWidget::setSelected(const QStringList &value)
{
    Q_D(HResultTableWidget);
    d->optional->setSelected(value);
}

void HResultTableWidget::clearResult()
{
    clearContents();
    setRowCount(0);
}

void HResultTableWidget::refreshResult(bool append)
{
    Q_D(HResultTableWidget);
    auto value = d->testData->toString(d->displays);
    int row = rowCount() - 1;
    if (append || row < 0)
    {
        row++;
        insertRow(row, value);
        scrollToBottom();
    }
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
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setDefaultSectionSize(100);
}

HE_END_NAMESPACE

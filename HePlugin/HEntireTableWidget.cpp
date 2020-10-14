#include "HEntireTableWidget_p.h"

HEntireTableWidget::HEntireTableWidget(QWidget *parent) :
    HTableWidget(*new HEntireTableWidgetPrivate, parent)
{
    init();
}

HEntireTableWidget::HEntireTableWidget(HEntireTableWidgetPrivate &p, QWidget *parent) :
    HTableWidget(p, parent)
{
    init();
}

HEntireTableWidget::~HEntireTableWidget() = default;

void HEntireTableWidget::setHorizontalHeaderLabels(const QStringList &value)
{
    setColumnCount(value.size());
    HTableWidget::setHorizontalHeaderLabels(value);
}

void HEntireTableWidget::setVerticalHeaderLabels(const QStringList &value)
{
    setRowCount(value.size());
    HTableWidget::setVerticalHeaderLabels(value);
}

void HEntireTableWidget::setRow(int row, const QStringList &value)
{
    setRow(row, 0, value);
}

void HEntireTableWidget::setRow(int row, int column, const QStringList &value)
{
    if (row < 0 || row >= rowCount() || column < 0 || column >= colorCount())
        return;

    for (int i = 0; i < value.size(); i++)
        item(row, column + i)->setText(value[i]);
}

void HEntireTableWidget::setColumn(int column, const QStringList &value)
{
    setColumn(0, column, value);
}

void HEntireTableWidget::setColumn(int row, int column, const QStringList &value)
{
    if (row < 0 || row >= rowCount() || column < 0 || column >= columnCount())
        return;

    for (int i = 0; i < value.size(); i++)
        item(row + i, column)->setText(value[i]);
}

void HEntireTableWidget::insertRow(int row, const QStringList &value)
{
    QTableWidget::insertRow(row);
    if (!value.isEmpty())
        setRow(row, value);
}

void HEntireTableWidget::init()
{
    setSelectionMode(QAbstractItemView::ContiguousSelection);
}

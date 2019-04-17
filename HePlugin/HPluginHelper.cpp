#include "HPluginHelper.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtGui/QClipboard>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QTableWidget>

HE_CORE_USE_NAMESPACE

QAction *HPluginHelper::addSeparator(QWidget *widget)
{
    auto action = new QAction(widget);
    action->setSeparator(true);
    widget->addAction(action);
    return action;
}

QString HPluginHelper::copy(QTableWidget *widget, bool withHeader)
{
    int row,column;
    QString text,header;

    auto ranges = widget->selectedRanges();
    if (ranges.isEmpty())
        return QString();

    auto range = ranges.first();
    for (row = range.topRow(); row <= range.bottomRow(); ++row)
    {
        if (widget->isRowHidden(row))
            continue;
        for (column = range.leftColumn(); column <= range.rightColumn(); column++)
        {
            if (widget->isColumnHidden(column))
                continue;
            text += widget->item(row, column)->text() + "\t";
        }
        text += "\n";
    }

    if (withHeader)
    {
        for (column = range.leftColumn(); column <= range.rightColumn(); column++)
        {
            if (widget->isColumnHidden(column))
                continue;
            header += widget->model()->headerData(column, Qt::Horizontal).toString() + "\t";
        }
        text = header + "\n" + text;
    }

    text.replace("\t\n", "\n");
    QApplication::clipboard()->setText(text);
    return text;
}

QString HPluginHelper::copy(QTableView *widget, bool withHeader)
{
    int row,column;
    QString text,header;

    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return text;

    auto range = selection.first();
    for (row = range.top(); row <= range.bottom(); row++)
    {
        if (widget->isRowHidden(row))
            continue;
        for (column = range.left(); column <= range.right(); column++)
        {
            if (widget->isColumnHidden(column))
                continue;
            text += widget->model()->index(row, column).data().toString() + "\t";
        }
        text += "\n";
    }

    if (withHeader)
    {
        for (column = range.left(); column <= range.right(); column++)
        {
            if (widget->isColumnHidden(column))
                continue;
            header += widget->model()->headerData(column, Qt::Horizontal).toString() + "\t";
        }
        text = header + "\n" + text;
    }

    text.replace("\t\n", "\n");
    QApplication::clipboard()->setText(text);
    return text;
}

QString HPluginHelper::paste(QTableWidget *widget)
{
    int i,j,m,n;
    int row,column,rowCount,columnCount;
    QStringList rowText,columnText;
    QTableWidgetItem *item;

    auto text = QApplication::clipboard()->text();
    auto ranges = widget->selectedRanges();
    if (ranges.isEmpty())
        return text;

    rowText = text.split('\n', QString::SkipEmptyParts);

    auto range = ranges.first();
    if (range.rowCount() * range.columnCount() == 1)
    {
        rowCount = widget->rowCount() - range.topRow();
        columnCount = widget->columnCount() - range.leftColumn();
    }
    else
    {
        rowCount = range.rowCount();
        columnCount = range.columnCount();
    }
    for (m = 0, i = 0; i < rowCount; i++)
    {
        row = range.topRow() + i;
        if (widget->isRowHidden(row))
            continue;
        if (m >= rowText.count())
            break;
        columnText = rowText[m].split('\t');
        for (n = 0, j = 0; j < columnCount; j++)
        {
            column = range.leftColumn() + j;
            if (widget->isColumnHidden(column))
                continue;
            if (n >= columnText.count())
                break;
            item = widget->item(row, column);
            if (item->flags() & Qt::ItemIsEditable)
                item->setText(columnText[n]);
            n++;
        }
        m++;
    }
    return text;
}

QString HPluginHelper::paste(QTableView *widget)
{
    int i,j,m,n;
    int row,column,rowCount,columnCount;
    QStringList rowText,columnText;
    QModelIndex index;

    auto text = QApplication::clipboard()->text();
    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return text;

    rowText = text.split('\n');
    rowText.removeLast();

    auto range = selection.first();
    if (range.width() * range.height() == 1)
    {
        rowCount = widget->model()->rowCount() - range.top();
        columnCount = widget->model()->columnCount() - range.left();
    }
    else
    {
        rowCount = range.height();
        columnCount = range.width();
    }

    for (m = 0, i = 0; i < rowCount; i++)
    {
        row = range.top() + i;
        if (widget->isRowHidden(row))
            continue;
        if (m >= rowText.count())
            break;
        columnText = rowText[m].split('\t');
        for (n = 0, j = 0; j < columnCount; j++)
        {
            column = range.left() + j;
            if (widget->isColumnHidden(column))
                continue;
            if (n >= columnText.count())
                break;
            index = widget->model()->index(row, column);
            if (index.flags() & Qt::ItemIsEditable)
                widget->model()->setData(index, columnText[n]);
            n++;
        }
        m++;
    }
    return text;
}

void HPluginHelper::initWidget(QString type, QSpinBox *widget)
{
    auto info = toFormatInfo(type);
    auto unit = info->unit(false);
    widget->setAlignment(Qt::AlignCenter);
    widget->setRange(static_cast<int>(info->min()), static_cast<int>(info->max()));
    widget->setSingleStep(static_cast<int>(info->singleStep()));
    if (!unit.isEmpty())
        widget->setSuffix(QString(" %1").arg(unit));
}

void HPluginHelper::initWidget(QString type, QDoubleSpinBox *widget)
{
    auto info = toFormatInfo(type);
    auto unit = info->unit(false);
    widget->setAlignment(Qt::AlignCenter);
    widget->setRange(info->min(), info->max());
    widget->setSingleStep(info->singleStep());
    widget->setDecimals(info->decimals());
    if (!unit.isEmpty())
        widget->setSuffix(QString(" %1").arg(unit));
}

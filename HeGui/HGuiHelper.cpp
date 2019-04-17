#include "HGuiHelper.h"
#include "HeCore/HCore.h"
#include <QtGui/QClipboard>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QAction>

HE_CORE_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

QString HGuiHelper::copy(QTableView *widget, bool withHeader)
{
    QString text,header;
    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return text;

    auto range = selection.first();
    for (int i = range.top(); i <= range.bottom(); i++)
    {
        if (widget->isRowHidden(i))
            continue;
        for (int j = range.left(); j <= range.right(); j++)
        {
            if (widget->isColumnHidden(j))
                continue;
            text += widget->model()->index(i, j).data().toString() + "\t";
        }
        text += "\n";
    }

    if (withHeader)
    {
        for (int i = range.left(); i <= range.right(); i++)
        {
            if (widget->isColumnHidden(i))
                continue;
            header += widget->model()->headerData(i, Qt::Horizontal).toString() + "\t";
        }
        text = header + "\n" + text;
    }

    text.replace("\t\n", "\n");
    QApplication::clipboard()->setText(text);
    return text;
}

QString HGuiHelper::copy(QTableWidget *widget, bool withHeader)
{
    QString text,header;
    QTableWidgetItem *item;

    auto ranges = widget->selectedRanges();
    if (ranges.isEmpty())
        return text;

    auto range = ranges.first();
    for (int i = range.topRow(); i <= range.bottomRow(); i++)
    {
        if (widget->isRowHidden(i))
            continue;
        for (int j = range.leftColumn(); j <= range.rightColumn(); j++)
        {
            if (widget->isColumnHidden(j))
                continue;
            item = widget->item(i, j);
            if (item)
                text += item->text() + "\t";
        }
        text += "\n";
    }

    if (withHeader)
    {
        for (int i = range.leftColumn(); i <= range.rightColumn(); i++)
        {
            if (widget->isColumnHidden(i))
                continue;
            header += widget->model()->headerData(i, Qt::Horizontal).toString() + "\t";
        }
        text = header + "\n" + text;
    }

    text.replace("\t\n", "\n");
    QApplication::clipboard()->setText(text);
    return text;
}

QString HGuiHelper::paste(QTableView *widget)
{
    int i,j,m,n;
    QStringList rows,columns;
    QModelIndex index;

    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return "";

    auto range = selection.first();
    auto bottom = range.width() * range.height() == 1 ? widget->model()->rowCount() - 1 : range.bottom();
    auto right = range.width() * range.height() == 1 ? widget->model()->columnCount() - 1 : range.right();
    auto text = QApplication::clipboard()->text();
    rows = text.split('\n');
    rows.removeLast();

    for (i = range.top(), m = 0; i <= bottom && m < rows.count(); i++)
    {
        if (widget->isRowHidden(i))
            continue;
        columns = rows[m].split('\t');
        for (j = range.left(), n = 0; j <= right && n < columns.count(); j++)
        {
            if (widget->isColumnHidden(j))
                continue;
            index = widget->model()->index(i, j);
            if (index.flags() & Qt::ItemIsEditable)
                widget->model()->setData(index, columns[n]);
            n++;
        }
        m++;
    }
    return text;
}

QString HGuiHelper::paste(QTableWidget *widget)
{
    int i,j,m,n;
    QStringList rows,columns;
    QTableWidgetItem *item;

    auto ranges = widget->selectedRanges();
    if (ranges.isEmpty())
        return "";

    auto range = ranges.first();
    auto bottom = range.rowCount() * range.columnCount() == 1 ? widget->rowCount() - 1 : range.bottomRow();
    auto right = range.rowCount() * range.columnCount() == 1 ? widget->columnCount() - 1 : range.rightColumn();
    auto text = QApplication::clipboard()->text();
    rows = text.split('\n');
    rows.removeLast();

    for (i = range.topRow(), m = 0; i <= bottom && m < rows.count(); i++)
    {
        if (widget->isRowHidden(i))
            continue;
        columns = rows[m].split('\t');
        for (j = range.leftColumn(), n = 0; j <= right && n < columns.count(); j++)
        {
            if (widget->isColumnHidden(j))
                continue;
            item = widget->item(i, j);
            if (item->flags() & Qt::ItemIsEditable)
                item->setText(columns[n]);
            n++;
        }
        m++;
    }
    return text;
}

QString HGuiHelper::selectedParameter(QWidget *parent, QStringList optional)
{
    if (optional.isEmpty())
        return QString();
    if (optional.size() == 1)
        return optional.first();

    bool ok;
    auto items = toCaption(optional);
    auto item = QInputDialog::getItem(parent, "", QObject::tr("请选择参数："), items, 0, false, &ok);
    if (!ok || item.isEmpty())
        return QString();
    return optional.value(items.indexOf(item));
}

QAction *HGuiHelper::addSeparator(QWidget *widget)
{
    QAction *action = new QAction(widget);
    action->setSeparator(true);
    widget->addAction(action);
    return action;
}

HE_GUI_END_NAMESPACE


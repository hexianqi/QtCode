#include "HPluginHelper.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtCore/QtMath>
#include <QtGui/QClipboard>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QInputDialog>
//#include <QtWidgets/QDesktopWidget>

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
    auto info = HCore::toFormatInfo(type);
    auto unit = info->unit(false);
    widget->setAlignment(Qt::AlignCenter);
    widget->setRange(static_cast<int>(info->min()), static_cast<int>(info->max()));
    widget->setSingleStep(static_cast<int>(info->singleStep()));
    if (!unit.isEmpty())
        widget->setSuffix(QString(" %1").arg(unit));
}

void HPluginHelper::initWidget(QString type, QDoubleSpinBox *widget)
{
    auto info = HCore::toFormatInfo(type);
    auto unit = info->unit(false);
    widget->setAlignment(Qt::AlignCenter);
    widget->setRange(info->min(), info->max());
    widget->setSingleStep(info->singleStep());
    widget->setDecimals(info->decimals());
    if (!unit.isEmpty())
        widget->setSuffix(QString(" %1").arg(unit));
}

void HPluginHelper::initWidget(QString type, QInputDialog *dlg)
{
    auto info = HCore::toFormatInfo(type);
    dlg->setInputMode(QInputDialog::DoubleInput);
    dlg->setDoubleRange(info->min(), info->max());
    dlg->setDoubleDecimals(info->decimals());
}

void HPluginHelper::centerWidget(QWidget *widget)
{
    auto size = QApplication::primaryScreen()->availableSize();
    widget->move((size.width() - widget->width()) / 2, (size.height() - widget->height()) / 2);
    widget->setFixedSize(widget->width(), widget->height());
}

bool HPluginHelper::selectedParameter(QWidget *parent, QStringList optional, QString &selected)
{
    if (optional.isEmpty())
        return false;

    if (optional.size() == 1)
    {
        selected = optional.first();
        return true;
    }

    auto list = HCore::toCaption(optional);
    QInputDialog dlg(parent);
    dlg.setLabelText(QObject::tr("请选择参数："));
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setComboBoxItems(list);
    if (!dlg.exec())
        return false;
    auto index = list.indexOf(dlg.textValue());
    if (index < 0)
        return false;
    selected = optional[index];
    return true;
}

bool HPluginHelper::getInputText(QWidget *parent, QString label, QString &text)
{
    QInputDialog dlg(parent);
    dlg.setLabelText(label);
    dlg.setInputMode(QInputDialog::TextInput);
    if (!dlg.exec() || dlg.textValue().isEmpty())
        return false;
    text = dlg.textValue();
    return true;
}

QImage HPluginHelper::createCrossImage(QSize size, QPen pen)
{
    QPainterPath path;
    path.moveTo(0, size.height() / 2);
    path.lineTo(size.width(), size.height() / 2);
    path.moveTo(size.width() / 2, 0);
    path.lineTo(size.width() / 2, size.height());

    QImage image(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    return image;
}

QPolygonF HPluginHelper::calcEllipse(QPointF center, double r, double theta, double a, double b)
{
    QPolygonF poly;
    auto theta1 = qDegreesToRadians(theta);
    for (int i = 0; i < 3600; i++)
    {
        auto theta2 = qDegreesToRadians(i * 0.1);
        auto x1 = r * a * qCos(theta2);
        auto y1 = r * b * qSin(theta2);
        auto x2 = x1 * qCos(theta1) - y1 * qSin(theta1) + center.x();
        auto y2 = x1 * qSin(theta1) + y1 * qCos(theta1) + center.y();
        poly << QPointF(x2, y2);
    }
    return poly;
}

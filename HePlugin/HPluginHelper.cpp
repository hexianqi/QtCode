#include "HPluginHelper.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include "QXlsx/xlsxdocument.h"
#include <QtCore/QtMath>
#include <QtGui/QClipboard>
#include <QtGui/QScreen>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFileDialog>

HE_CORE_USE_NAMESPACE

QAction *HPluginHelper::addSeparator(QWidget *widget)
{
    auto action = new QAction(widget);
    action->setSeparator(true);
    widget->addAction(action);
    return action;
}

QString HPluginHelper::copy(QTableView *widget, bool withHeader)
{
    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return "";

    int row, col;
    QString text, header;
    auto model = widget->model();
    auto range = selection.first();
    for (row = range.top(); row <= range.bottom(); row++)
    {
        if (widget->isRowHidden(row))
            continue;
        for (col = range.left(); col <= range.right(); col++)
        {
            if (widget->isColumnHidden(col))
                continue;
            text += model->index(row, col).data().toString() + "\t";
        }
        text += "\n";
    }

    if (withHeader)
    {
        for (col = range.left(); col <= range.right(); col++)
        {
            if (widget->isColumnHidden(col))
                continue;
            header += model->headerData(col, Qt::Horizontal).toString() + "\t";
        }
        text = header + "\n" + text;
    }

    text.replace("\t\n", "\n");
    QApplication::clipboard()->setText(text);
    return text;
}

QString HPluginHelper::paste(QTableView *widget)
{
    auto text = QApplication::clipboard()->text();
    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return text;

    int i, j, m, n;
    int row, col, rowCount, colCount;
    QStringList colText;
    QModelIndex index;
    auto model = widget->model();
    auto rowText = text.split('\n', QString::SkipEmptyParts);
    auto range = selection.first();
    if (range.width() * range.height() == 1)
    {
        rowCount = model->rowCount() - range.top();
        colCount = model->columnCount() - range.left();
    }
    else
    {
        rowCount = range.height();
        colCount = range.width();
    }

    for (m = 0, i = 0; i < rowCount; i++)
    {
        row = range.top() + i;
        if (widget->isRowHidden(row))
            continue;
        if (m >= rowText.count())
            break;
        colText = rowText[m].split('\t');
        for (n = 0, j = 0; j < colCount; j++)
        {
            col = range.left() + j;
            if (widget->isColumnHidden(col))
                continue;
            if (n >= colText.count())
                break;
            index = model->index(row, col);
            if (index.flags() & Qt::ItemIsEditable)
                model->setData(index, colText[n]);
            n++;
        }
        m++;
    }
    return text;
}

bool HPluginHelper::exportExcel(QTableView *widget)
{
    auto fileName = QFileDialog::getSaveFileName(nullptr, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return false;

    int i, j, row, col;
    QXlsx::Document doc(widget);
    auto model = widget->model();
    i = 2;
    for (row = 0; row < model->rowCount(); row++)
    {
        if (widget->isRowHidden(row))
            continue;
        doc.write(i++, 1, model->headerData(row, Qt::Vertical));
    }
    j = 2;
    for (col = 0; col < model->columnCount(); col++)
    {
        if (widget->isColumnHidden(col))
            continue;
        doc.write(1, j++, model->headerData(col, Qt::Horizontal));
    }
    i = 2;
    for (row = 0; row < model->rowCount(); row++)
    {
        if (widget->isRowHidden(row))
            continue;
        j = 2;
        for (col = 0; col < model->columnCount(); col++)
        {
            if (widget->isColumnHidden(col))
                continue;
            auto index = model->index(row, col);
            if (!index.isValid())
                continue;
            QXlsx::Format format;
            if (index.data(Qt::BackgroundColorRole).isValid())
                format.setPatternBackgroundColor(index.data(Qt::BackgroundColorRole).value<QColor>());
            doc.write(i, j++, index.data().toString(), format);
        }
        i++;
    }
    return doc.saveAs(fileName);
}

bool HPluginHelper::importExcel(QTableView *widget)
{
    auto fileName = QFileDialog::getOpenFileName(nullptr, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return false;
    QXlsx::Document doc(fileName, widget);
    if (!doc.isLoadPackage())
        return false;

    int i, j, row, col;
    auto model = widget->model();
    auto range = doc.dimension();
    auto t = range.firstRow() + 1;
    auto b = range.lastRow();
    auto l = range.firstColumn() + 1;
    auto r = range.lastColumn();
    if (range.rowCount() < 2 || range.columnCount() < 2)
        return false;

    i = t;
    for (row = 0; row < model->rowCount() && i <= b; row++)
    {
        if (widget->isRowHidden(row))
            continue;
        j = l;
        for (col = 0; col < model->columnCount() && j <= r; col++)
        {
            if (widget->isColumnHidden(col))
                continue;
            auto cell = doc.cellAt(i, j++);
            auto index = model->index(row, col);
            if (!index.isValid() || cell == nullptr)
                continue;
            if (cell->format().patternBackgroundColor().isValid())
                model->setData(index, cell->format().patternBackgroundColor(), Qt::BackgroundColorRole);
            model->setData(index, cell->value());
        }
        i++;
    }
    return true;
}

void HPluginHelper::initWidget(const QString &type, QSpinBox *widget)
{
    auto info = HCore::toFormatInfo(type);
    auto unit = info->unit(false);
    widget->setAlignment(Qt::AlignCenter);
    widget->setRange(static_cast<int>(info->min()), static_cast<int>(info->max()));
    widget->setSingleStep(static_cast<int>(info->singleStep()));
    if (!unit.isEmpty())
        widget->setSuffix(QString(" %1").arg(unit));
}

void HPluginHelper::initWidget(const QString &type, QDoubleSpinBox *widget)
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

void HPluginHelper::initWidget(const QString &type, QInputDialog *dlg)
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

bool HPluginHelper::getInputText(QWidget *parent, const QString &label, QString &text)
{
    QInputDialog dlg(parent);
    dlg.setLabelText(label);
    dlg.setInputMode(QInputDialog::TextInput);
    if (!dlg.exec() || dlg.textValue().isEmpty())
        return false;
    text = dlg.textValue();
    return true;
}

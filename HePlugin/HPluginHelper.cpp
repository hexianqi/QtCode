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

using namespace QXlsx;

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
    int row, column;
    QString text, header;

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

QString HPluginHelper::paste(QTableView *widget)
{
    int i, j, m, n;
    int row, column, rowCount, columnCount;
    QStringList columnText;
    QModelIndex index;

    auto text = QApplication::clipboard()->text();
    auto selection = widget->selectionModel()->selection();
    if (selection.isEmpty())
        return text;

    auto rowText = text.split('\n', QString::SkipEmptyParts);
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

bool HPluginHelper::exportExcel(QAbstractItemModel *model)
{
    auto fileName = QFileDialog::getSaveFileName(nullptr, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return false;

    int i, j;
    Document doc(model);
    for (i = 0; i < model->rowCount(); i++)
        doc.write(i + 2, 1, model->headerData(i, Qt::Vertical));
    for (j = 0; j < model->columnCount(); j++)
        doc.write(1, j + 2, model->headerData(j, Qt::Horizontal));
    for (i = 0; i < model->rowCount(); i++)
    {
        for (j = 0; j < model->columnCount(); j++)
        {
            auto index = model->index(i, j);
            if (!index.isValid())
                continue;
            Format format;
            if (index.data(Qt::BackgroundColorRole).isValid())
                format.setPatternBackgroundColor(index.data(Qt::BackgroundColorRole).value<QColor>());
            doc.write(i + 2, j + 2, index.data().toString(), format);
        }
    }
    return doc.saveAs(fileName);
}

bool HPluginHelper::importExcel(QAbstractItemModel *model)
{
    auto fileName = QFileDialog::getOpenFileName(nullptr, "", ".", "Excel files (*.xlsx)");
    if (fileName.isEmpty())
        return false;
    Document doc(fileName, model);
    if (!doc.isLoadPackage())
        return false;
    auto range = doc.dimension();
    auto rowCount = range.rowCount();
    auto colCount = range.columnCount();
    if (rowCount < 2 || colCount < 2)
        return false;

    for (int i = 2; i <= rowCount; i++)
    {
        for (int j = 2; j <= colCount; j++)
        {
            auto cell = doc.cellAt(i, j);
            auto index = model->index(i - 2, j - 2);
            if (!index.isValid() || cell == nullptr)
                continue;
            if (cell->format().patternBackgroundColor().isValid())
                model->setData(index, cell->format().patternBackgroundColor(), Qt::BackgroundColorRole);
            model->setData(index, cell->value());
        }
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

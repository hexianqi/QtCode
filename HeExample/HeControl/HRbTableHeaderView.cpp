#include "HRbTableHeaderView_p.h"
#include "HRbTableHeaderItem.h"
#include "HRbTableHeaderModel.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <qdrawutil.h>

HE_CONTROL_BEGIN_NAMESPACE

HRbTableHeaderViewPrivate::HRbTableHeaderViewPrivate(int rows, int columns)
{
    model = new HRbTableHeaderModel(rows, columns);
}

HRbTableHeaderView::HRbTableHeaderView(Qt::Orientation orientation, int rows, int columns, QWidget *parent) :
    QHeaderView(orientation, parent),
    d_ptr(new HRbTableHeaderViewPrivate(rows, columns))
{
    init();
}

HRbTableHeaderView::HRbTableHeaderView(HRbTableHeaderViewPrivate &p, Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent),
    d_ptr(&p)
{
    init();
}

HRbTableHeaderView::~HRbTableHeaderView()
{

}

void HRbTableHeaderView::setRowHeight(int row, int height)
{
    for (int column = 0; column < columnCount(); column++)
    {
        auto idx = index(row, column);
        auto size = idx.data(Qt::SizeHintRole).toSize();
        size.setHeight(height);
        d_ptr->model->setData(idx, size, Qt::SizeHintRole);
    }
    if (orientation() == Qt::Vertical)
        resizeSection(row, height);
}

void HRbTableHeaderView::setColumnWidth(int column, int width)
{
    for (int row = 0; row < rowCount(); row++)
    {
        auto idx = index(row, column);
        auto size = idx.data(Qt::SizeHintRole).toSize();
        size.setWidth(width);
        d_ptr->model->setData(idx, size, Qt::SizeHintRole);
    }
    if (orientation() == Qt::Horizontal)
        resizeSection(column, width);
}

void HRbTableHeaderView::setSpan(int row, int column, int rowSpanCount, int columnSpanCount)
{
    auto idx = index(row, column);
    if (rowSpanCount > 0)
        d_ptr->model->setData(idx, rowSpanCount, RowSpanRole);
    if (columnSpanCount)
        d_ptr->model->setData(idx, columnSpanCount, ColumnSpanRole);
}

void HRbTableHeaderView::setCellBackgroundColor(const QModelIndex &index, const QColor &color)
{
    d_ptr->model->setData(index, color, Qt::BackgroundRole);
}

void HRbTableHeaderView::setCellForegroundColor(const QModelIndex &index, const QColor &color)
{
    d_ptr->model->setData(index, color, Qt::ForegroundRole);
}

void HRbTableHeaderView::mousePressEvent(QMouseEvent *event)
{
    QHeaderView::mousePressEvent(event);

    auto pos = event->pos();
    auto idx = indexAt(pos);
    if (!idx.isValid())
        return;

    int beginSection = -1;
    int endSection   = -1;
    int numbers      = getSectionRange(idx, &beginSection, &endSection);
    if (numbers > 0)
    {
        emit sectionPressed(beginSection, endSection);
        return;
    }

    int count    = orientation() == Qt::Horizontal ? rowCount() : columnCount();
    int logical  = orientation() == Qt::Horizontal ? idx.column() : idx.row();
    int curLevel = orientation() == Qt::Horizontal ? idx.row() : idx.column();
    for (int i = 0; i < count; i++)
    {
        auto cell = orientation() == Qt::Horizontal ? index(i, logical) : index(logical, i);
        numbers = getSectionRange(cell, &beginSection, &endSection);
        if (numbers <= 0)
            continue;
        if (beginSection <= logical && logical <= endSection)
        {
            auto beginLevel = orientation() == Qt::Horizontal ? cell.row() : cell.column();
            auto levelCount = cell.data(orientation() == Qt::Horizontal ? RowSpanRole : ColumnSpanRole);
            if (!levelCount.isValid())
                continue;
            int endLevel = beginLevel + levelCount.toInt() - 1;
            if (beginLevel <= curLevel && curLevel <= endLevel)
            {
                emit sectionPressed(beginSection, endSection);
                break;
            }
        }
    }
}

void HRbTableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    int count = orientation() == Qt::Horizontal ? rowCount() : columnCount();
    for (int i = 0; i < count; i++)
    {
        auto cell = orientation() == Qt::Horizontal ? index(i, logicalIndex) : index(logicalIndex, i);
        auto size = cell.data(Qt::SizeHintRole).toSize();
        // set position of the cell
        QRect section(rect);
        if (orientation() == Qt::Horizontal)
            section.setTop(rowSpanSize(logicalIndex, 0, i)); // distance from 0 to i-1 rows
        else
            section.setLeft(columnSpanSize(logicalIndex, 0, i));
        section.setSize(size);

        // check up span column or row
        auto colSpan = columnSpanIndex(cell);
        auto rowSpan = rowSpanIndex(cell);
        if (colSpan.isValid())
        {
            int spanFrom  = colSpan.column();
            int spanCount = colSpan.data(ColumnSpanRole).toInt();
            if (orientation() == Qt::Horizontal)
                section.setLeft(sectionViewportPosition(spanFrom));
            else
            {
                section.setLeft(columnSpanSize(logicalIndex, 0, spanFrom));
                i = spanFrom + spanCount - 1;
            }
            section.setWidth(columnSpanSize(cell.row(), spanFrom, spanCount));
            // check up  if the column span index has row span
            auto subSpan = colSpan.data(RowSpanRole);
            if (subSpan.isValid())
            {
                int subSpanFrom  = colSpan.row();
                int subSpanCount = subSpan.toInt();
                if (orientation() == Qt::Vertical)
                    section.setTop(sectionViewportPosition(subSpanFrom));
                else
                {
                    section.setTop(rowSpanSize(spanFrom, 0, subSpanFrom));
                    i = subSpanFrom + subSpanCount - 1;
                }
                section.setHeight(rowSpanSize(spanFrom, subSpanFrom, subSpanCount));
            }
            cell = colSpan;
        }
        if (rowSpan.isValid())
        {
            int spanFrom  = rowSpan.row();
            int spanCount = rowSpan.data(RowSpanRole).toInt();
            if (orientation() == Qt::Vertical)
                section.setTop(sectionViewportPosition(spanFrom));
            else
            {
                section.setTop(rowSpanSize(logicalIndex, 0, spanFrom));
                i = spanFrom + spanCount - 1;
            }
            section.setHeight(rowSpanSize(cell.column(), spanFrom, spanCount));
            // check up if the row span index has column span
            auto subSpan = rowSpan.data(ColumnSpanRole);
            if (subSpan.isValid())
            {
                int subSpanFrom  = rowSpan.column();
                int subSpanCount = subSpan.toInt();
                if (orientation() == Qt::Horizontal)
                    section.setLeft(sectionViewportPosition(subSpanFrom));
                else
                {
                    section.setLeft(columnSpanSize(spanFrom, 0, subSpanFrom));
                    i = subSpanFrom + subSpanCount - 1;
                }
                section.setWidth(columnSpanSize(spanFrom, subSpanFrom, subSpanCount));
            }
            cell = rowSpan;
        }
        // draw section with style
        QStyleOptionHeader option;
        initStyleOption(&option);
        option.textAlignment = Qt::AlignCenter;
        option.iconAlignment = Qt::AlignVCenter;
        option.section = logicalIndex;
        option.text = cell.data(Qt::DisplayRole).toString();
        option.rect = section;
        // file background or foreground color of the cell
        QVariant background = cell.data(Qt::BackgroundRole);
        QVariant foreground = cell.data(Qt::ForegroundRole);
        if (background.canConvert(QMetaType::QBrush))
        {
            option.palette.setBrush(QPalette::Button, background.value<QBrush>());
            option.palette.setBrush(QPalette::Window, background.value<QBrush>());
        }
        if (foreground.canConvert(QMetaType::QBrush))
            option.palette.setBrush(QPalette::ButtonText, foreground.value<QBrush>());

        painter->save();
        qDrawShadePanel(painter, option.rect, option.palette, false, 1, &option.palette.brush(QPalette::Button));
        style()->drawControl(QStyle::CE_HeaderLabel, &option, painter);
        painter->restore();
    }
}

QSize HRbTableHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    auto size = QHeaderView::sectionSizeFromContents(logicalIndex);
    auto count = orientation() == Qt::Horizontal ? rowCount() : columnCount();
    for (int i = 0; i < count; i++)
    {
        auto cell = orientation() == Qt::Horizontal ? index(i, logicalIndex) : index(logicalIndex, i);
        auto colSpan = columnSpanIndex(cell);
        auto rowSpan = rowSpanIndex(cell);
        size = cell.data(Qt::SizeHintRole).toSize();
        if (colSpan.isValid())
        {
            int spanFrom  = colSpan.column();
            int spanCount = colSpan.data(ColumnSpanRole).toInt();
            size.setWidth(columnSpanSize(colSpan.row(), spanFrom, spanCount));
            if (orientation() == Qt::Vertical)
                i = spanFrom + spanCount -1;
        }
        if (rowSpan.isValid())
        {
            int spanFrom  = rowSpan.row();
            int spanCount = rowSpan.data(RowSpanRole).toInt();
            size.setHeight(rowSpanSize(rowSpan.column(), spanFrom, spanCount));
            if (orientation() == Qt::Horizontal)
                i = spanFrom + spanCount - 1;
        }
    }
    return size;
}

QModelIndex HRbTableHeaderView::indexAt(const QPoint &pos)
{
    int logical = logicalIndexAt(pos);
    if (orientation() == Qt::Horizontal)
    {
        int y = 0;
        for (int row = 0; row < rowCount(); row++)
        {
            auto cell = index(row, logical);
            y += cell.data(Qt::SizeHintRole).toSize().height();
            if (pos.y() <= y)
                return cell;
        }
    }
    else
    {
        int x = 0;
        for (int column = 0; column < columnCount(); column++)
        {
            auto cell = index(logical, column);
            x  += cell.data(Qt::SizeHintRole).toSize().width();
            if (pos.x() <= x)
                return cell;
        }
    }
    return QModelIndex();
}

QModelIndex HRbTableHeaderView::index(int row, int column) const
{
    return d_ptr->model->index(row, column);
}

QModelIndex HRbTableHeaderView::columnSpanIndex(const QModelIndex &currentIndex) const
{
    const int row = currentIndex.row();
    const int column = currentIndex.column();
    for (int i = column; i >= 0; i--)
    {
        auto cell = index(row, i);
        auto span  = cell.data(ColumnSpanRole);
        if (span.isValid() && cell.column() + span.toInt() - 1 >= column)
            return cell;
    }
    return QModelIndex();
}

QModelIndex HRbTableHeaderView::rowSpanIndex(const QModelIndex &currentIndex) const
{
    const int row = currentIndex.row();
    const int column = currentIndex.column();
    for (int i = row; i >= 0; i--)
    {
        auto cell = index(i, column);
        auto span = cell.data(RowSpanRole);
        if (span.isValid() && cell.row() + span.toInt() - 1 >= row)
            return cell;
    }
    return QModelIndex();
}

int HRbTableHeaderView::columnCount() const
{
    return d_ptr->model->columnCount();
}

int HRbTableHeaderView::rowCount() const
{
    return d_ptr->model->rowCount();
}

int HRbTableHeaderView::columnSpanSize(int row, int from, int count) const
{
    int span = 0;
    for (int i = from; i < from + count; i++)
        span += index(row, i).data(Qt::SizeHintRole).toSize().width();
    return span;
}

int HRbTableHeaderView::rowSpanSize(int column, int from, int count) const
{
    int span = 0;
    for (int i = from; i < from + count; i++)
        span += index(i, column).data(Qt::SizeHintRole).toSize().height();
    return span;
}

int HRbTableHeaderView::getSectionRange(QModelIndex &index, int *beginSection, int *endSection) const
{
    // check up section range from the index
    auto colSpan = columnSpanIndex(index);
    auto rowSpan = rowSpanIndex(index);
    int spanCount = 0;

    if (colSpan.isValid())
    {
        if (orientation() == Qt::Horizontal)
        {
            spanCount = colSpan.data(ColumnSpanRole).toInt();
            *beginSection = colSpan.column();
            *endSection   = *beginSection + spanCount - 1;
            index = colSpan;
            return spanCount;
        }
        // check up  if the column span index has row span
        auto subSpan = colSpan.data(RowSpanRole);
        if (subSpan.isValid())
        {
            spanCount  = subSpan.toInt();
            *beginSection = colSpan.row();
            *endSection   = *beginSection + spanCount - 1;
            index = colSpan;
            return spanCount;
        }
    }

    if (rowSpan.isValid())
    {
        if (orientation() == Qt::Vertical)
        {
            spanCount = rowSpan.data(RowSpanRole).toInt();
            *beginSection = rowSpan.row();
            *endSection   = *beginSection + spanCount - 1;;
            index = rowSpan;
            return spanCount;
        }
        // check up if the row span index has column span
        auto subSpan = rowSpan.data(ColumnSpanRole);
        if (subSpan.isValid())
        {
            spanCount = subSpan.toInt();
            *beginSection = rowSpan.column();
            *endSection   = *beginSection + spanCount - 1;;
            index = rowSpan;
            return spanCount;
        }
    }
    return 0;
}

void HRbTableHeaderView::init()
{
    QSize sectionSize;
    if (orientation() == Qt::Horizontal)
    {
        sectionSize.setWidth(defaultSectionSize());
        sectionSize.setHeight(20);
    }
    else
    {
        sectionSize.setWidth(50);
        sectionSize.setHeight(defaultSectionSize());
    }
    // set default size of item
    for (int row = 0; row < rowCount(); row++)
        for (int column = 0; column < columnCount(); column++)
            d_ptr->model->setData(index(row, column), sectionSize, Qt::SizeHintRole);
    setModel(d_ptr->model);
    connect(this, &HRbTableHeaderView::sectionResized, this, &HRbTableHeaderView::handleSectionResized);
}

void HRbTableHeaderView::handleSectionResized(int logicalIndex, int /*oldSize*/, int newSize)
{
    int count = orientation() == Qt::Horizontal ? rowCount() : columnCount();
    int pos = sectionViewportPosition(logicalIndex);
    int xx  = orientation() == Qt::Horizontal ? pos : 0;
    int yy  = orientation() == Qt::Horizontal ? 0 : pos;
    QRect section(xx, yy, 0, 0);
    for (int i = 0; i < count; i++)
    {
        auto cell = (orientation() == Qt::Horizontal) ? index(i, logicalIndex) : index(logicalIndex, i);
        auto size = cell.data(Qt::SizeHintRole).toSize();
        // set position of cell
        if (orientation() == Qt::Horizontal)
        {
            section.setTop(rowSpanSize(logicalIndex, 0, i));
            size.setWidth(newSize);
        }
        else
        {
            section.setLeft(columnSpanSize(logicalIndex, 0, i));
            size.setHeight(newSize);
        }
        d_ptr->model->setData(cell, size, Qt::SizeHintRole);

        auto colSpan = columnSpanIndex(cell);
        auto rowSpan = rowSpanIndex(cell);
        if (colSpan.isValid())
        {
            int column = colSpan.column();
            if (orientation() == Qt::Horizontal)
                section.setLeft(sectionViewportPosition(column));
            else
                section.setLeft(columnSpanSize(logicalIndex, 0, column));
        }
        if (rowSpan.isValid())
        {
            int row = rowSpan.row();
            if (orientation() == Qt::Vertical)
                section.setTop(sectionViewportPosition(row));
            else
                section.setTop(rowSpanSize(logicalIndex, 0, row));
        }
        QRect rect(section);
        rect.setWidth(viewport()->width() - section.left());
        rect.setHeight(viewport()->height() - section.top());
        viewport()->update(rect.normalized());
    }
}

HE_CONTROL_END_NAMESPACE

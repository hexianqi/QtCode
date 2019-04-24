/* Copyright 2016 Lee Cho Kang.
* email: pzesseto@gmail.com
* This file is part of the RbTableHeaderView.
*
* The RbTableHeaderView is free software: you can redistribute it
* and/or modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* The RbTableHeaderView is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with the RbTableHeaderView. If not, see http://www.gnu.org/licenses/.
*/
/*
 * RbTableHeaderView.h
 *  Created on: 2016. 6. 13.
 */

#include "RbTableHeaderView.h"
#include <QPainter>
#include <QStandardItem>
#include <QMouseEvent>
#include <qdrawutil.h>

RbTableHeaderItem::RbTableHeaderItem(RbTableHeaderItem* parent):
    row_prop(0),column_prop(0),parent_item(parent)
{
}

RbTableHeaderItem::RbTableHeaderItem(int arow, int acolumn, RbTableHeaderItem* parent):
    row_prop(arow),column_prop(acolumn),parent_item(parent)
{
}

RbTableHeaderItem::~RbTableHeaderItem()
{
}

RbTableHeaderItem* RbTableHeaderItem::insertChild(int row, int col)
{
    RbTableHeaderItem* newChild = new RbTableHeaderItem(row,col,this);
    child_items.insert(QPair<int,int>(row,col),newChild);
    return newChild;
}

const RbTableHeaderItem* RbTableHeaderItem::child(int row,int col) const
{
    QHash<QPair<int,int>,RbTableHeaderItem*>::const_iterator itr = child_items.find(QPair<int,int>(row,col));
    if (itr != child_items.end()) return itr.value();
    return 0;
}

RbTableHeaderItem* RbTableHeaderItem::child(int row,int col)
{
    QHash<QPair<int,int>,RbTableHeaderItem*>::iterator itr = child_items.find(QPair<int,int>(row,col));
    if (itr != child_items.end()) return itr.value();
    return 0;
}

void RbTableHeaderItem::setText(const QString& text)
{
    role_datas.insert(Qt::DisplayRole,text);
}

QVariant RbTableHeaderItem::data(int role) const
{
    QHash<int,QVariant>::const_iterator itr = role_datas.find(role);
    if (itr != role_datas.end()) return itr.value();
    return QVariant();
}

void RbTableHeaderItem::setData(const QVariant& data, int role)
{
    role_datas.insert(role,data);
}

void RbTableHeaderItem::clear()
{
    QList<RbTableHeaderItem*> items = child_items.values();
    foreach (RbTableHeaderItem* item, child_items)
    {
        if (item) delete item;
    }
    child_items.clear();
}

RbTableHeaderModel::RbTableHeaderModel(int rows, int cols, QObject* parent) :
    QAbstractTableModel(parent),row_count_prop(rows),column_count_prop(cols),root_item(new RbTableHeaderItem())
{
}

RbTableHeaderModel::~RbTableHeaderModel()
{
    root_item->clear();
    delete root_item;
}

QModelIndex RbTableHeaderModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row,column,parent)) return QModelIndex();

    RbTableHeaderItem* parentItem;
    if (!parent.isValid()) parentItem = root_item; // parent item is always the root_item on table model
    else parentItem = static_cast<RbTableHeaderItem*>(parent.internalPointer()); // no effect

    RbTableHeaderItem* childItem = parentItem->child(row,column);
    if (!childItem) childItem = parentItem->insertChild(row,column);
    return createIndex(row,column,childItem);

    return QModelIndex();
}

QVariant RbTableHeaderModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= row_count_prop || index.row() < 0 || index.column() >= column_count_prop || index.column() < 0)
        return QVariant();

    RbTableHeaderItem* item = static_cast<RbTableHeaderItem*>(index.internalPointer());

    return item->data(role);
}

bool RbTableHeaderModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid())
    {
        RbTableHeaderItem* item = static_cast<RbTableHeaderItem*>(index.internalPointer());
        if (role == COLUMN_SPAN_ROLE)
        {
            int col = index.column();
            int span = value.toInt();
            if (span > 0) // span size should be more than 1, else nothing to do
            {
                if (col+span-1 >= column_count_prop) // span size should be less than whole columns,
                    span = column_count_prop-col;
                item->setData(span,COLUMN_SPAN_ROLE);
            }
        }
        else if (role == ROW_SPAN_ROLE)
        {
            int row = index.row();
            int span = value.toInt();
            if (span > 0) // span size should be more than 1, else nothing to do
            {
                if (row+span-1 >= row_count_prop)
                    span = row_count_prop-row;
                item->setData(span,ROW_SPAN_ROLE);
            }
        }
        else
            item->setData(value,role);

        return true;
    }
    return false;
}

// Qt::ItemFlags RbTableHeaderModel::flags(const QModelIndex &index) const
// {
// 	if (!index.isValid())
// 		return Qt::ItemIsEnabled;
// 	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
// }


RbTableHeaderView::RbTableHeaderView(Qt::Orientation orientation, int rows, int columns, QWidget* parent):
    QHeaderView(orientation,parent)
{
    QSize baseSectionSize;
    if (orientation == Qt::Horizontal)
    {
        baseSectionSize.setWidth(defaultSectionSize());
        baseSectionSize.setHeight(20);
    }
    else
    {
        baseSectionSize.setWidth(50);
        baseSectionSize.setHeight(defaultSectionSize());
    }

    // create header model
    RbTableHeaderModel* headerModel = new RbTableHeaderModel(rows,columns);

    // set default size of item
    for (int row=0;row<rows;++row)
        for (int col=0;col<columns;++col)
            headerModel->setData(headerModel->index(row,col),baseSectionSize,Qt::SizeHintRole);

    setModel(headerModel);

    connect(this, SIGNAL(sectionResized(int, int, int)), this, SLOT(onSectionResized(int,int,int)));
}

RbTableHeaderView::~RbTableHeaderView()
{
}

void RbTableHeaderView::setRowHeight(int row, int rowHeight)
{
    RbTableHeaderModel* md = qobject_cast<RbTableHeaderModel*>(model());
    const int cols = md->columnCount();
    for (int col=0;col<cols;++col)
    {
        QSize sz = md->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setHeight(rowHeight);
        md->setData(md->index(row,col),sz,Qt::SizeHintRole);
    }
    if (orientation() == Qt::Vertical)
        resizeSection(row,rowHeight);
}

void RbTableHeaderView::setColumnWidth(int col, int colWidth)
{
    RbTableHeaderModel* md = qobject_cast<RbTableHeaderModel*>(model());
    const int rows = md->rowCount();
    for (int row=0;row<rows;++row)
    {
        QSize sz = md->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setWidth(colWidth);
        md->setData(md->index(row,col),sz,Qt::SizeHintRole);
    }
    if (orientation() == Qt::Horizontal)
        resizeSection(col,colWidth);
}


void RbTableHeaderView::setSpan(int row, int column, int rowSpanCount, int columnSpanCount)
{
    RbTableHeaderModel* md = qobject_cast<RbTableHeaderModel*>(model());
    QModelIndex idx = md->index(row,column);
    if (rowSpanCount > 0)
        md->setData(idx,rowSpanCount,ROW_SPAN_ROLE);
    if (columnSpanCount)
        md->setData(idx,columnSpanCount,COLUMN_SPAN_ROLE);
}

void RbTableHeaderView::setCellBackgroundColor(const QModelIndex& index, const QColor& color)
{
    RbTableHeaderModel* md = qobject_cast<RbTableHeaderModel*>(model());
    md->setData(index,color,Qt::BackgroundRole);
}

void RbTableHeaderView::setCellForegroundColor(const QModelIndex& index, const QColor& color)
{
    RbTableHeaderModel* md = qobject_cast<RbTableHeaderModel*>(model());
    md->setData(index,color,Qt::ForegroundRole);
}


void RbTableHeaderView::mousePressEvent(QMouseEvent* event)
{
    QHeaderView::mousePressEvent(event);
    QPoint pos = event->pos();
    QModelIndex index = indexAt(pos);
    const int OTN = orientation();
    if (index.isValid())
    {
        int beginSection = -1;
        int endSection   = -1;
        int numbers = 0;
        numbers = getSectionRange(index,&beginSection,&endSection);
        if (numbers > 0)
        {
            emit sectionPressed(beginSection,endSection);
            return;
        }
        else
        {
            const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(this->model());
            const int LEVEL_CNT = (OTN == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
            int logicalIdx = (OTN == Qt::Horizontal)?index.column():index.row();
            int curLevel   = (OTN == Qt::Horizontal)?index.row():index.column();
            for (int i=0;i<LEVEL_CNT;++i)
            {
                QModelIndex cellIndex = (OTN == Qt::Horizontal)?tblModel->index(i,logicalIdx):tblModel->index(logicalIdx,i);
                numbers = getSectionRange(cellIndex,&beginSection,&endSection);
                if (numbers > 0)
                {
                    if (beginSection <= logicalIdx && logicalIdx <= endSection)
                    {
                        int beginLevel = (OTN == Qt::Horizontal)?cellIndex.row():cellIndex.column();
                        QVariant levelSpanCnt = cellIndex.data((OTN == Qt::Horizontal)?ROW_SPAN_ROLE:COLUMN_SPAN_ROLE);
                        if (!levelSpanCnt.isValid())
                            continue;
                        int endLevel   = beginLevel + levelSpanCnt.toInt()-1;
                        if (beginLevel <= curLevel && curLevel <= endLevel)
                        {
                            emit sectionPressed(beginSection,endSection);
                            break;
                        }
                    }
                }
            }
        }
    }
}

QModelIndex RbTableHeaderView::indexAt(const QPoint& pos)
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(this->model());
    const int OTN = orientation();
    const int ROWS = tblModel->rowCount();
    const int COLS = tblModel->columnCount();
    int logicalIdx = logicalIndexAt(pos);

    if (OTN == Qt::Horizontal)
    {
        int dY=0;
        for (int row=0;row<ROWS;++row)
        {
            QModelIndex cellIndex = tblModel->index(row,logicalIdx);
            dY += cellIndex.data(Qt::SizeHintRole).toSize().height();
            if (pos.y() <= dY) return cellIndex;
        }
    }
    else
    {
        int dX=0;
        for (int col=0;col<COLS;++col)
        {
            QModelIndex cellIndex = tblModel->index(logicalIdx,col);
            dX += cellIndex.data(Qt::SizeHintRole).toSize().width();
            if (pos.x() <= dX) return cellIndex;
        }
    }

    return QModelIndex();
}

void RbTableHeaderView::paintSection(QPainter* painter, const QRect& rect, int logicalIdx) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(this->model());
    const int OTN = orientation();
    const int LEVEL_CNT = (OTN == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
    for (int i=0;i<LEVEL_CNT;++i)
    {
        QModelIndex cellIndex = (OTN == Qt::Horizontal)?tblModel->index(i,logicalIdx):tblModel->index(logicalIdx,i);
        QSize cellSize=cellIndex.data(Qt::SizeHintRole).toSize();
        QRect sectionRect(rect);

        // set position of the cell
        if (OTN == Qt::Horizontal)
            sectionRect.setTop(rowSpanSize(logicalIdx,0,i)); // distance from 0 to i-1 rows
        else
            sectionRect.setLeft(columnSpanSize(logicalIdx,0,i));

        sectionRect.setSize(cellSize);

        // check up span column or row
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt  = colSpanIdx.data(COLUMN_SPAN_ROLE).toInt();
            int colSpanTo   = colSpanFrom+colSpanCnt-1;
            int colSpan     = columnSpanSize(cellIndex.row(),colSpanFrom,colSpanCnt);
            if (OTN == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else
            {
                sectionRect.setLeft(columnSpanSize(logicalIdx,0,colSpanFrom));
                i = colSpanTo;
            }

            sectionRect.setWidth(colSpan);

            // check up  if the column span index has row span
            QVariant subRowSpanData = colSpanIdx.data(ROW_SPAN_ROLE);
            if (subRowSpanData.isValid())
            {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                int subRowSpan     = rowSpanSize(colSpanFrom,subRowSpanFrom,subRowSpanCnt);
                if (OTN == Qt::Vertical)
                    sectionRect.setTop(sectionViewportPosition(subRowSpanFrom));
                else
                {
                    sectionRect.setTop(rowSpanSize(colSpanFrom,0,subRowSpanFrom));
                    i = subRowSpanTo;
                }
                sectionRect.setHeight(subRowSpan);
            }
            cellIndex=colSpanIdx;
        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(ROW_SPAN_ROLE).toInt();
            int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
            int rowSpan     = rowSpanSize(cellIndex.column(),rowSpanFrom,rowSpanCnt);
            if (OTN == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else
            {
                sectionRect.setTop(rowSpanSize(logicalIdx,0,rowSpanFrom));
                i = rowSpanTo;
            }
            sectionRect.setHeight(rowSpan);

            // check up if the row span index has column span
            QVariant subColSpanData = rowSpanIdx.data(COLUMN_SPAN_ROLE);
            if (subColSpanData.isValid())
            {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                int subColSpan     = columnSpanSize(rowSpanFrom,subColSpanFrom,subColSpanCnt);
                if (OTN == Qt::Horizontal)
                    sectionRect.setLeft(sectionViewportPosition(subColSpanFrom));
                else
                {
                    sectionRect.setLeft(columnSpanSize(rowSpanFrom,0,subColSpanFrom));
                    i = subColSpanTo;
                }
                sectionRect.setWidth(subColSpan);
            }
            cellIndex=rowSpanIdx;
        }

        // draw section with style
        QStyleOptionHeader sectionStyle;
        initStyleOption(&sectionStyle);
        sectionStyle.textAlignment = Qt::AlignCenter;
        sectionStyle.iconAlignment = Qt::AlignVCenter;
        sectionStyle.section = logicalIdx;
        sectionStyle.text = cellIndex.data(Qt::DisplayRole).toString();
        sectionStyle.rect = sectionRect;

        // file background or foreground color of the cell
        QVariant bg = cellIndex.data(Qt::BackgroundRole);
        QVariant fg = cellIndex.data(Qt::ForegroundRole);
        if (bg.canConvert(QMetaType::QBrush))
        {
            sectionStyle.palette.setBrush(QPalette::Button, qvariant_cast<QBrush>(bg));
            sectionStyle.palette.setBrush(QPalette::Window, qvariant_cast<QBrush>(bg));
        }
        if (fg.canConvert(QMetaType::QBrush))
        {
            sectionStyle.palette.setBrush(QPalette::ButtonText, qvariant_cast<QBrush>(fg));
        }

        painter->save();
        qDrawShadePanel(painter,sectionStyle.rect,sectionStyle.palette,false,1,&sectionStyle.palette.brush(QPalette::Button));
        style()->drawControl(QStyle::CE_HeaderLabel, &sectionStyle, painter);
        painter->restore();
    }
}

QSize RbTableHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<const RbTableHeaderModel*>(this->model());
    const int OTN = orientation();
    const int LEVEL_CNT = (OTN == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();

    QSize siz = QHeaderView::sectionSizeFromContents(logicalIndex);
    for (int i=0;i<LEVEL_CNT;++i)
    {
        QModelIndex cellIndex = (OTN == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        siz=cellIndex.data(Qt::SizeHintRole).toSize();

        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt     = colSpanIdx.data(COLUMN_SPAN_ROLE).toInt();
            int colSpanTo   = colSpanFrom + colSpanCnt -1;
            siz.setWidth(columnSpanSize(colSpanIdx.row(),colSpanFrom,colSpanCnt));
            if (OTN == Qt::Vertical) i = colSpanTo;
        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(ROW_SPAN_ROLE).toInt();
            int rowSpanTo   = rowSpanFrom + rowSpanCnt-1;
            siz.setHeight(rowSpanSize(rowSpanIdx.column(),rowSpanFrom,rowSpanCnt));
            if (OTN == Qt::Horizontal) i = rowSpanTo;
        }
    }
    return siz;
}

QModelIndex RbTableHeaderView::columnSpanIndex(const QModelIndex& currentIdx) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(model());
    const int curRow = currentIdx.row();
    const int curCol = currentIdx.column();
    int i = curCol;
    while (i >= 0)
    {
        QModelIndex spanIndex = tblModel->index(curRow,i);
        QVariant span   = spanIndex.data(COLUMN_SPAN_ROLE);
        if (span.isValid() && spanIndex.column()+span.toInt()-1 >= curCol)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

QModelIndex RbTableHeaderView::rowSpanIndex(const QModelIndex& currentIdx) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(model());
    const int curRow = currentIdx.row();
    const int curCol = currentIdx.column();
    int i = curRow;
    while (i >= 0)
    {
        QModelIndex spanIndex = tblModel->index(i,curCol);
        QVariant span   = spanIndex.data(ROW_SPAN_ROLE);
        if (span.isValid() && spanIndex.row()+span.toInt()-1 >= curRow)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

int RbTableHeaderView::columnSpanSize(int row, int from, int spanCount) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i)
    {
        QSize cellSize = tblModel->index(row,i).data(Qt::SizeHintRole).toSize();
        span += cellSize.width();
    }
    return span;
}


int RbTableHeaderView::rowSpanSize(int column, int from, int spanCount) const
{
    const RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i)
    {
        QSize cellSize = tblModel->index(i,column).data(Qt::SizeHintRole).toSize();
        span += cellSize.height();
    }
    return span;
}

/**
 * @return section numbers
 */
int RbTableHeaderView::getSectionRange(QModelIndex& index, int* beginSection, int* endSection) const
{
    // check up section range from the index
    QModelIndex colSpanIdx = columnSpanIndex(index);
    QModelIndex rowSpanIdx = rowSpanIndex(index);

    if (colSpanIdx.isValid())
    {
        int colSpanFrom = colSpanIdx.column();
        int colSpanCnt  = colSpanIdx.data(COLUMN_SPAN_ROLE).toInt();
        int colSpanTo   = colSpanFrom+colSpanCnt-1;
        if (orientation() == Qt::Horizontal)
        {
            *beginSection = colSpanFrom;
            *endSection   = colSpanTo;
            index = colSpanIdx;
            return colSpanCnt;
        }
        else
        {
            // check up  if the column span index has row span
            QVariant subRowSpanData = colSpanIdx.data(ROW_SPAN_ROLE);
            if (subRowSpanData.isValid())
            {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                *beginSection = subRowSpanFrom;
                *endSection   = subRowSpanTo;
                index = colSpanIdx;
                return subRowSpanCnt;
            }
        }
    }

    if (rowSpanIdx.isValid())
    {
        int rowSpanFrom = rowSpanIdx.row();
        int rowSpanCnt  = rowSpanIdx.data(ROW_SPAN_ROLE).toInt();
        int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
        if (orientation() == Qt::Vertical)
        {
            *beginSection = rowSpanFrom;
            *endSection   = rowSpanTo;
            index = rowSpanIdx;
            return rowSpanCnt;
        }
        else
        {
            // check up if the row span index has column span
            QVariant subColSpanData = rowSpanIdx.data(COLUMN_SPAN_ROLE);
            if (subColSpanData.isValid())
            {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                *beginSection = subColSpanFrom;
                *endSection   = subColSpanTo;
                index = rowSpanIdx;
                return subColSpanCnt;
            }
        }
    }

    return 0;
}


void RbTableHeaderView::onSectionResized(int logicalIndex,int oldSize,int newSize)
{
    RbTableHeaderModel* tblModel = qobject_cast<RbTableHeaderModel*>(this->model());
    const int OTN = orientation();
    const int LEVEL_CNT = (OTN == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
    int pos = sectionViewportPosition(logicalIndex);
    int xx  = (OTN == Qt::Horizontal)?pos:0;
    int yy  = (OTN == Qt::Horizontal)?0:pos;
    QRect sectionRect(xx,yy,0,0);
    for (int i=0;i<LEVEL_CNT;++i)
    {
        QModelIndex cellIndex = (OTN == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QSize cellSize=cellIndex.data(Qt::SizeHintRole).toSize();
        // set position of cell
        if (OTN == Qt::Horizontal)
        {
            sectionRect.setTop(rowSpanSize(logicalIndex,0,i));
            cellSize.setWidth(newSize);
        }
        else
        {
            sectionRect.setLeft(columnSpanSize(logicalIndex,0,i));
            cellSize.setHeight(newSize);
        }
        tblModel->setData(cellIndex,cellSize,Qt::SizeHintRole);

        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);

        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            if (OTN == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else
            {
                sectionRect.setLeft(columnSpanSize(logicalIndex,0,colSpanFrom));
            }

        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            if (OTN == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else
                sectionRect.setTop(rowSpanSize(logicalIndex,0,rowSpanFrom));
        }
        QRect rToUpdate(sectionRect);
        rToUpdate.setWidth(viewport()->width()-sectionRect.left());
        rToUpdate.setHeight(viewport()->height()-sectionRect.top());
        viewport()->update(rToUpdate.normalized());
    }
}

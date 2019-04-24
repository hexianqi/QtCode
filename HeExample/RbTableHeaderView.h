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

#ifndef RBTABLEHEADERVIEW_H_
#define RBTABLEHEADERVIEW_H_
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QHash>
#include <QPair>

enum eRbHeaderRole
{
    COLUMN_SPAN_ROLE = Qt::UserRole+1,
    ROW_SPAN_ROLE
};

class RbTableHeaderItem
{
public:
    RbTableHeaderItem(RbTableHeaderItem* parent=0);
    RbTableHeaderItem(int arow, int acolumn, RbTableHeaderItem* parent=0);
    ~RbTableHeaderItem();

    // interface
    RbTableHeaderItem* insertChild(int row, int col);
    const RbTableHeaderItem* child(int row,int col) const;
    RbTableHeaderItem* child(int row,int col);
    void setData(const QVariant& data, int role);
    QVariant data(int role=Qt::UserRole+1) const;
    inline int column() const { return column_prop;}
    inline int row() const { return row_prop;}
    RbTableHeaderItem* parent() { return parent_item;}
    void setText(const QString& text);
    void clear();

private:
    // properties
    int row_prop;
    int column_prop;
    // inherent features
    RbTableHeaderItem* parent_item;
    QHash<QPair<int,int>,RbTableHeaderItem*> child_items;
    QHash<int,QVariant> role_datas;
};

class RbTableHeaderModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    RbTableHeaderModel(int rows,int cols,QObject* parent=0);
    virtual ~RbTableHeaderModel();

public:
    // override
    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const { Q_UNUSED(parent); return row_count_prop; }
    virtual int columnCount(const QModelIndex &parent=QModelIndex()) const { Q_UNUSED(parent); return column_count_prop;}
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    //	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    // properties
    int row_count_prop;
    int column_count_prop;
    // inherent features
    RbTableHeaderItem* root_item;
};


class RbTableHeaderView: public QHeaderView
{
    Q_OBJECT
public:
    RbTableHeaderView(Qt::Orientation orientation, int rows, int columns, QWidget* parent = 0);
    virtual ~RbTableHeaderView();

    void setRowHeight(int row, int rowHeight);
    void setColumnWidth(int col, int colWidth);
    void setSpan(int row, int column, int rowSpanCount, int columnSpanCount);
    void setCellBackgroundColor(const QModelIndex& index, const QColor&);
    void setCellForegroundColor(const QModelIndex& index, const QColor&);

protected:
    // override
    virtual void mousePressEvent(QMouseEvent* event);
    virtual QModelIndex indexAt(const QPoint&);
    virtual void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    // inherent features
    QModelIndex columnSpanIndex(const QModelIndex& currentIndex) const;
    QModelIndex rowSpanIndex(const QModelIndex& currentIndex) const;
    int columnSpanSize(int row, int from, int spanCount) const;
    int rowSpanSize(int column, int from, int spanCount) const;
    int getSectionRange(QModelIndex& index, int* beginSection, int* endSection) const;

protected Q_SLOTS:
    void onSectionResized(int logicalIdx,int oldSize,int newSize);

Q_SIGNALS:
    void sectionPressed(int from, int to);
};

#endif /* RBTABLEHEADERVIEW_H_ */

/***************************************************************************************************
**      2019-05-31  HRbTableHeaderView 多标题视图
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QHeaderView>

HE_BEGIN_NAMESPACE

class HRbTableHeaderViewPrivate;

class HRbTableHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    explicit HRbTableHeaderView(Qt::Orientation orientation, int rows, int columns, QWidget *parent = nullptr);
    ~HRbTableHeaderView() override;

signals:
    void sectionPressed(int from, int to);

public:
    QSize sizeHint() const override;

public:
    void setRowHeight(int row, int height);
    void setColumnWidth(int column, int width);
    void setSpan(int row, int column, int rowSpanCount, int columnSpanCount);
    void setCellBackgroundColor(const QModelIndex &, const QColor&);
    void setCellForegroundColor(const QModelIndex &, const QColor&);

protected:
    HRbTableHeaderView(HRbTableHeaderViewPrivate &p, Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
    QSize sectionSizeFromContents(int logicalIndex) const override;

protected:
    QModelIndex indexAt(const QPoint &) const override;
    QModelIndex index(int row, int column) const;
    QModelIndex columnSpanIndex(const QModelIndex &) const;
    QModelIndex rowSpanIndex(const QModelIndex &) const;
    int rowCount() const;
    int columnCount() const;
    int columnSpanSize(int row, int from, int count) const;
    int rowSpanSize(int column, int from, int count) const;
    int getSectionRange(QModelIndex &index, int *beginSection, int *endSection) const;

protected:
    QScopedPointer<HRbTableHeaderViewPrivate> d_ptr;

private:
    void init();
    void handleSectionResized(int logicalIndex, int oldSize, int newSize);
};

HE_END_NAMESPACE

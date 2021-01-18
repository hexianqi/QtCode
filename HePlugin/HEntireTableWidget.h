/***************************************************************************************************
**      2019-03-22  HEntireTableWidget 可以整行整列添加数据的表格类。
***************************************************************************************************/

#ifndef HENTIRETABLEWIDGET_H
#define HENTIRETABLEWIDGET_H

#include "HTableWidget.h"

class HEntireTableWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HEntireTableWidget : public HTableWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HEntireTableWidget)

public:
    explicit HEntireTableWidget(QWidget *parent = nullptr);
    ~HEntireTableWidget() override;

public:
    void setHorizontalHeaderLabels(const QStringList &);
    void setVerticalHeaderLabels(const QStringList &);
    void setRow(int row, const QStringList &value);
    void setRow(int row, int column, const QStringList &value);
    void setColumn(int column, const QStringList &value);
    void setColumn(int row, int column, const QStringList &value);
    void insertRow(int row, const QStringList &value = QStringList());

protected:
    HEntireTableWidget(HEntireTableWidgetPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

#endif // HENTIRETABLEWIDGET_H

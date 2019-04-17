/***************************************************************************************************
**      2019-03-21  HTableWidget 带复制粘贴上下文菜单的表格类。
***************************************************************************************************/

#ifndef HTABLEWIDGET_H
#define HTABLEWIDGET_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QTableWidget>

class HTableWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit HTableWidget(QWidget *parent = nullptr);
    ~HTableWidget() override;

public slots:
    void removeRows(int row, int count);

public:
    void setEditTriggers(EditTriggers triggers);
    QTableWidgetItem *item(int row, int column);

protected:
    HTableWidget(HTableWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HTableWidgetPrivate> d_ptr;

private:
    void init();
};

#endif // HTABLEWIDGET_H

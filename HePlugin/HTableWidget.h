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

signals:
    void contentChanged();

public:
    QTableWidgetItem *item(int row, int column);

public:
    void setEditTriggers(EditTriggers triggers);
    void setExportImport(bool b);

public slots:
    void removeRows(int row, int count);
    void copy();
    void paste();
    void exportExcel();
    void importExcel();

protected:
    HTableWidget(HTableWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HTableWidgetPrivate> d_ptr;

private:
    void init();
};

#endif // HTABLEWIDGET_H

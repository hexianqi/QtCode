/***************************************************************************************************
**      2019-03-21  HTableWidget 带复制粘贴上下文菜单的表格类。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QTableWidget>

class HTableWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    enum ActionContain
    {
        ActionCopy      = 0x01,
        ActionPaste     = 0x02,
        ActionExport    = 0x04,
        ActionImport    = 0x08,
        ActionAll       = 0xffffffff
    };
    Q_DECLARE_FLAGS(ActionContains, ActionContain)

public:
    explicit HTableWidget(QWidget *parent = nullptr);
    ~HTableWidget() override;

signals:
    void contentChanged();

public:
    QTableWidgetItem *item(int row, int column);

public:
    void setEditTriggers(EditTriggers triggers);
    void setActionContain(quint32);

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

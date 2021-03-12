/***************************************************************************************************
**      2019-05-08  HTableView 带复制粘贴上下文菜单的表格类。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QTableView>

class HTableViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTableView : public QTableView
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
    explicit HTableView(QWidget *parent = nullptr);
    ~HTableView() override;

signals:
    void contentChanged();

public:
    void setEditTriggers(EditTriggers triggers);
    void setActionContain(quint32);

public slots:
    void copy();
    void paste();
    void exportExcel();
    void importExcel();

protected:
    HTableView(HTableViewPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HTableViewPrivate> d_ptr;

private:
    void init();
};

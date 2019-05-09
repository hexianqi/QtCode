/***************************************************************************************************
**      2019-05-08  HTableView 带复制粘贴上下文菜单的表格类。
***************************************************************************************************/

#ifndef HTABLEVIEW_H
#define HTABLEVIEW_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QTableView>

class HTableViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTableView : public QTableView
{
    Q_OBJECT

public:
    explicit HTableView(QWidget *parent = nullptr);
    ~HTableView() override;

public:
    void setEditTriggers(EditTriggers triggers);

protected:
    HTableView(HTableViewPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HTableViewPrivate> d_ptr;

private:
    void init();
};

#endif // HTABLEVIEW_H

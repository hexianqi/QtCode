/***************************************************************************************************
**      2019-04-10  HTypeOptionalDialog 类型选择对话框。
***************************************************************************************************/

#ifndef HTYPEOPTIONALDIALOG_H
#define HTYPEOPTIONALDIALOG_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QDialog>

namespace Ui {
class HTypeOptionalDialog;
}

class HTypeOptionalDialogPrivate;

class QDESIGNER_WIDGET_EXPORT HTypeOptionalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HTypeOptionalDialog(QStringList selected, QStringList optional, QWidget *parent = nullptr);
    ~HTypeOptionalDialog() override;

public:
    QStringList selected();

protected:
    void done(int result) override;
    void showData();
    void saveData();

protected slots:
    void on_toolButton_1_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();

private:
    QScopedPointer<HTypeOptionalDialogPrivate> d_ptr;
    Ui::HTypeOptionalDialog *ui;
};

#endif // HTYPEOPTIONALDIALOG_H

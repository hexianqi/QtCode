#ifndef HADJUSTEDITDIALOG_H
#define HADJUSTEDITDIALOG_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HAdjustEditDialog;
}

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class IAdjust;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestSetWidget;
class HAdjustEditDialogPrivate;

class HAdjustEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HAdjustEditDialog(QWidget *parent = nullptr);
    ~HAdjustEditDialog();

public:
    void setData(IAdjust *);
    void setTestSetWidget(ITestSetWidget *);

protected:
    void done(int result) override;
    void handleAction(HActionType action);
    void initSelected();
    void showData();
    void saveData();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

protected:
    QScopedPointer<HAdjustEditDialogPrivate> d_ptr;

private:
    void init();

private:
    Ui::HAdjustEditDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITDIALOG_H

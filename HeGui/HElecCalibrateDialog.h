#ifndef HELECCALIBRATEDIALOG_H
#define HELECCALIBRATEDIALOG_H

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HElecCalibrateDialog;
}

class QTreeWidgetItem;

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateDialogPrivate;

class HElecCalibrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HElecCalibrateDialog(QWidget *parent = nullptr);
    ~HElecCalibrateDialog() override;

protected:
    QTreeWidgetItem *createItem(QString text, int value, QTreeWidgetItem *parent);

private:
    void init();

private:
    QScopedPointer<HElecCalibrateDialogPrivate> d_ptr;
    Ui::HElecCalibrateDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEDIALOG_H

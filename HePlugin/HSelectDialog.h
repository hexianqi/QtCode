/***************************************************************************************************
**      2019-04-25  HSelectDialog 选择对话框。
***************************************************************************************************/

#ifndef HSELECTDIALOG_H
#define HSELECTDIALOG_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QDialog>

namespace Ui {
class HSelectDialog;
}

class QDESIGNER_WIDGET_EXPORT HSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSelectDialog(QWidget *parent = nullptr);
    ~HSelectDialog();

public:
    void setLabelText(QString value);
    void setOptionals(QStringList value);
    void setSelected(QString value);

public:
    QString selected();

private:
    Ui::HSelectDialog *ui;
};

#endif // HSELECTDIALOG_H

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
    QString currentText() const;
    QVariant currentData() const;

public:
    void setLabelText(const QString &);
    void setOptionals(const QStringList &);
    void setOptionals(const QVariantMap &);
    void setCurrentText(const QString &);
    void setCurrentIndex(int index);

private:
    Ui::HSelectDialog *ui;
};

#endif // HSELECTDIALOG_H

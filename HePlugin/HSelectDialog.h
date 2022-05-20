/***************************************************************************************************
**      2019-04-25  HSelectDialog 选择对话框。
***************************************************************************************************/

#pragma once

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
    ~HSelectDialog() override;

public:
    QString currentText() const;
    QVariant currentData() const;

public:
    void setLabelText(const QString &);
    void setOptional(const QStringList &);
    void setOptional(const QVariantMap &);
    void setCurrentText(const QString &);
    void setCurrentIndex(int index);

private:
    Ui::HSelectDialog *ui;
};

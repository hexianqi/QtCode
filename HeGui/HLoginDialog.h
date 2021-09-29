#pragma once

#include "HGuiGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HLoginDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HLoginDialog(QWidget *parent = nullptr);
    ~HLoginDialog();

protected slots:
    void on_pushButton_03_clicked();

protected:
    void done(int result) override;

protected:
    void readSettings();
    void writeSettings();

private:
    Ui::HLoginDialog *ui;
    QString _user;
    QString _password;
};

HE_GUI_END_NAMESPACE


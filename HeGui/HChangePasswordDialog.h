#pragma once

#include "HGuiGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HChangePasswordDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HChangePasswordDialog(QString password, QWidget *parent = nullptr);
    ~HChangePasswordDialog();

public:
    QString password();

protected:
    void done(int result) override;

private:
    Ui::HChangePasswordDialog *ui;
    QString _password;
};

HE_GUI_END_NAMESPACE


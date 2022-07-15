#pragma once

#include <QtWidgets/QDialog>

namespace Ui {
class HDBLoginDialog;
}

class HDBLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HDBLoginDialog(QWidget *parent = nullptr);
    ~HDBLoginDialog();

protected:
    void done(int result) override;

private:
    Ui::HDBLoginDialog *ui;
};


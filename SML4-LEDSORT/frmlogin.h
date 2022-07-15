//登录窗口
#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QDialog>

namespace Ui {
class frmlogin;
}

class frmlogin : public QDialog
{
    Q_OBJECT

public:
    explicit frmlogin(QWidget *parent = nullptr);
    ~frmlogin();

private slots:


    void on_btnok_clicked();

    void on_btnno_clicked();

private:
    Ui::frmlogin *ui;
};

#endif // FRMLOGIN_H

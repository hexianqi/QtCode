#ifndef FRMABOUT_H
#define FRMABOUT_H
//关于，注册信息
#include <QDialog>

namespace Ui {
class Frmabout;
}

class Frmabout : public QDialog
{
    Q_OBJECT

public:
    explicit Frmabout(QWidget *parent = nullptr);
    ~Frmabout();

private slots:
    void on_toolButton_2_clicked();

    void on_btnreg_clicked();

private:
    Ui::Frmabout *ui;
};

#endif // FRMABOUT_H

#ifndef FRMEDTKEY_H
#define FRMEDTKEY_H
//修改密码
#include <QDialog>

namespace Ui {
class Frmedtkey;
}

class Frmedtkey : public QDialog
{
    Q_OBJECT

public:
    explicit Frmedtkey(QWidget *parent = nullptr);
    ~Frmedtkey();

private slots:
    void on_btnno_clicked();

    void on_btnok_clicked();

private:
    Ui::Frmedtkey *ui;
};

#endif // FRMEDTKEY_H

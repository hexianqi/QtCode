#ifndef HPNGAMEND_H
#define HPNGAMEND_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HPngAmend;
}

HE_CONTROL_BEGIN_NAMESPACE

class HPngAmendPrivate;

class HPngAmend : public QWidget
{
    Q_OBJECT

public:
    explicit HPngAmend(QWidget *parent = nullptr);
    ~HPngAmend() override;

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void init();

private:
    Ui::HPngAmend *ui;
    QScopedPointer<HPngAmendPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HPNGAMEND_H

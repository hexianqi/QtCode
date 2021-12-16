/***************************************************************************************************
**      2020-03-18  HPngAmend PNG警告去除工具
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HPngAmend;
}

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE

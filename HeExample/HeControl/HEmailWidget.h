#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HEmailWidget;
}

HE_BEGIN_NAMESPACE

class HEmailWidgetPrivate;

class HEmailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HEmailWidget(QWidget *parent = nullptr);
    ~HEmailWidget();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void init();
    bool check();

private:
    Ui::HEmailWidget *ui;
    QScopedPointer<HEmailWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

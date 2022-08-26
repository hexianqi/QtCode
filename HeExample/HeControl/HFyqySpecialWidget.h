#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HFyqySpecialWidget;
}

HE_BEGIN_NAMESPACE

class HFyqySpecialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HFyqySpecialWidget(QWidget *parent = nullptr);
    ~HFyqySpecialWidget();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::HFyqySpecialWidget *ui;
    QWidget *_framelessWidget = nullptr;
};

HE_END_NAMESPACE


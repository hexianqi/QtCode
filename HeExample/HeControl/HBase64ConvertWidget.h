#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HBase64ConvertWidget;
}

HE_BEGIN_NAMESPACE

class HBase64ConvertWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HBase64ConvertWidget(QWidget *parent = nullptr);
    ~HBase64ConvertWidget() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::HBase64ConvertWidget *ui;
};

HE_END_NAMESPACE

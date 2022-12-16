#pragma once

#include "HNamespace.h"
#include <QtCore/QMap>
#include <QtWidgets/QWidget>

namespace Ui {
class HYsaSpecialWidget;
}

HE_BEGIN_NAMESPACE

class HYsaSpecialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HYsaSpecialWidget(QWidget *parent = nullptr);
    ~HYsaSpecialWidget();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::HYsaSpecialWidget *ui;
    QMap<QString, QWidget *> _widgets;
};

HE_END_NAMESPACE

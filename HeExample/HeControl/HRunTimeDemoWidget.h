#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HRunTimeDemoWidget;
}

HE_BEGIN_NAMESPACE

class HRunTimeService;

class HRunTimeDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HRunTimeDemoWidget(QWidget *parent = nullptr);
    ~HRunTimeDemoWidget();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_checkBox_clicked(bool);
    void refresh();

private:
    void init();

private:
    Ui::HRunTimeDemoWidget *ui;
    HRunTimeService *service;
};

HE_END_NAMESPACE


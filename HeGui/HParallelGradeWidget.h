/***************************************************************************************************
**      2020-10-22  HParallelGradeWidget 并行分级。
***************************************************************************************************/

#pragma once

#include "HAbstractGradeWidget.h"

namespace Ui {
class HParallelGradeWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HParallelGradeWidgetPrivate;

class HParallelGradeWidget : public HAbstractGradeWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HParallelGradeWidget)

public:
    explicit HParallelGradeWidget(QWidget *parent = nullptr);
    ~HParallelGradeWidget();

public:
    void clearData() override;
    bool saveData() override;
    bool showData() override;

protected:
    void showConfig();
    void showPreview();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    void init();

private:
    Ui::HParallelGradeWidget *ui;
};

HE_GUI_END_NAMESPACE


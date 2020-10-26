/***************************************************************************************************
**      2020-10-22  HSequentialGradeWidget 连续分级。
***************************************************************************************************/

#pragma once

#include "HAbstractGradeWidget.h"

namespace Ui {
class HSequentialGradeWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HSequentialGradeWidgetPrivate;

class HSequentialGradeWidget : public HAbstractGradeWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSequentialGradeWidget)

public:
    explicit HSequentialGradeWidget(QWidget *parent = nullptr);
    ~HSequentialGradeWidget();

public:
    void clearData() override;
    bool saveData() override;
    bool showData() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void exportExcel();
    void importExcel();
    void setModified();

private:
    void init();

private:
    Ui::HSequentialGradeWidget *ui;
};

HE_GUI_END_NAMESPACE

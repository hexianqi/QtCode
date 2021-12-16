/***************************************************************************************************
**      2019-04-23  HGradeItemDialog 分级数据编辑对话框。
***************************************************************************************************/

#pragma once

#include "HAbstractGradeItemDialog.h"

namespace Ui {
class HGradeItemDialog;
}

HE_BEGIN_NAMESPACE

class HGradeItemDialogPrivate;

class HGradeItemDialog : public HAbstractGradeItemDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeItemDialog)

public:
    explicit HGradeItemDialog(QWidget *parent = nullptr);
    ~HGradeItemDialog();

protected slots:
    void on_spinBox_02_valueChanged(int value);
    void on_checkBox_01_clicked(bool b);
    void on_pushButton_01_clicked();

protected:
    bool setAverageMode(bool b) override;
    void averageLevels() override;
    void showData() override;
    void saveData() override;

private:
    void init();

private:
    Ui::HGradeItemDialog *ui;
};

HE_END_NAMESPACE

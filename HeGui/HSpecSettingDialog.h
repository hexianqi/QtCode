/***************************************************************************************************
**      2019-03-22  HSpecSettingDialog 光谱配置对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HSpecSettingDialog;
}

HE_BEGIN_NAMESPACE

class HSpecSetting;

class HSpecSettingDialogPrivate;

class HSpecSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSpecSettingDialog(QWidget *parent = nullptr);
    ~HSpecSettingDialog() override;

public:
    void setData(HSpecSetting *);

protected slots:
    void on_pushButton_1_clicked();

protected:
    void done(int result) override;
    void showData();
    void saveData();

private:
    void init();

protected:
    QScopedPointer<HSpecSettingDialogPrivate> d_ptr;

private:
    Ui::HSpecSettingDialog *ui;
};

HE_END_NAMESPACE

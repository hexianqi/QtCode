/***************************************************************************************************
**      2019-03-22  HSpecSettingDialog 光谱配置对话框。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

HE_DATA_BEGIN_NAMESPACE
class HSpecSetting;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

namespace Ui {
class HSpecSettingDialog;
}

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE

/***************************************************************************************************
**      2019-03-22  HSpecSettingDialog 光谱配置对话框。
***************************************************************************************************/

#ifndef HSPECSETTINGDIALOG_H
#define HSPECSETTINGDIALOG_H

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QDialog>

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
    explicit HSpecSettingDialog(HSpecSetting *data, QWidget *parent = nullptr);
    ~HSpecSettingDialog() override;

protected:
    void done(int result) override;
    void showData();
    void saveData();

private:
    void init();

private:
    Ui::HSpecSettingDialog *ui;
    QScopedPointer<HSpecSettingDialogPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSETTINGDIALOG_H

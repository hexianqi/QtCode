/***************************************************************************************************
**      2019-04-11  HSpecCalibrateDialog 光谱校准对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class HSpecCalibrateDialogPrivate;

class HSpecCalibrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSpecCalibrateDialog(QWidget *parent = nullptr);
    ~HSpecCalibrateDialog() override;

protected:
    void done(int result) override;

protected:
    QScopedPointer<HSpecCalibrateDialogPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE

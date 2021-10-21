#pragma once

#include "HAbstractTestDataEditDialog.h"

namespace Ui {
class HTestDataEditDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HTestDataEditDialogPrivate;

class HE_GUI_EXPORT HTestDataEditDialog : public HAbstractTestDataEditDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestDataEditDialog)

public:
    explicit HTestDataEditDialog(QWidget *parent = nullptr);
    ~HTestDataEditDialog() override;

public:
    QString typeName() override;

protected:
    void showData() override;
    void saveData() override;

private:
    void init();

private:
    Ui::HTestDataEditDialog *ui;
};

HE_GUI_END_NAMESPACE
